//  Zeyu Zhao
//  Assignment_4
//  Xcode on Mac
//
//  Created by zhaozeyu on 01/02/2018.
//  Copyright © 2018 zhaozeyu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void print(string*, int);
void insertSort(string [], int);
int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream fin;
    ofstream fout;
    fout.open("Outputfile.txt");
    string* data;
    int count = 0;
    int countcpp = 0;
    int countline = 0;
    int keysfound = 0;
    char linecpy[100];
    char* words;
    fin.open("unsorted_keywords.txt");
    if(!fin.is_open()){
        cout<<"Can not open the file"<<endl;
        exit(1);
    }
    string a;
    while(fin>>a){
        count++;
    }
    fin.close();
    fin.open("unsorted_keywords.txt");
    if(!fin.is_open()){
        cout<<"Can not open the file"<<endl;
        exit(2);
    }
     data = new string[count];
    for(int i = 0; i < count; i++){
        fin>>data[i];
    }
    insertSort(data, count);
    char holddata[100];
    ifstream InputFile;
    InputFile.open("oldass3.cpp");
    if(!InputFile.is_open()){
        cout<<"Can not open the oldasse file";
        exit(3);
    }
    while(InputFile.getline(holddata, sizeof(holddata))){
        countcpp++;
    }
    InputFile.close();
    InputFile.open("oldass3.cpp");
    if(!InputFile.is_open()){
        cout<<"Can not open the oldasse file";
        exit(4);
    }
    char* charposition;
    char* Commentfind;
    int linebool = 0;
    //what is blow is theloop for each lines
    do{
        countline++;
        InputFile.getline(holddata, sizeof(holddata));
        Commentfind = strstr(holddata, "//");
        if(Commentfind != NULL){
            *Commentfind = '\0';
        }
        strcpy(linecpy, holddata);
        words = strtok(linecpy, " ,=+-*/!><""[]()#{}'';\r");
        while (words != NULL)
        {
            for(int i = 0; i < count; i++){
                if(data[i] == words){
                    keysfound++;
                    charposition = strstr(holddata, words);
                    if(linebool == 0){
                        fout<<"Line "<<countline<<": ";
                        linebool++;
                    }
                    fout<<data[i]<<"("<<charposition-holddata<<")"<<" ";
                }
            }
            words = strtok (NULL, " ,=+-.*/!>""<[#](){''};\r");
        }
        if(linebool != 0){
            fout<<endl;
        }
        linebool = 0;
    }while(countline<181);
    fout<<"Number of keywords found = "<<keysfound;
    InputFile.close();
    fin.close();
    fout.close();
    delete []data;
    return 0;
}

void print(string data[], int a){
    for(int i = 0; i < a; i++){
        cout<<data[i]<<" ";
    }
}

void insertSort(string a[], int length)
{
    int i, j;
    string value;
    
    for(i = 1 ; i < length ; i++)
    {
        value = a[i];
        for (j = i - 1; j >= 0 && a[j] > value; j--)
            a[j + 1] = a[j];
        a[j + 1] = value;
    }
}
