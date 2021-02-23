#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const int DictionarySize = 23907;

void getDictionary(const string& filename,string*);
void spellCheckLine(char* line, int lineNumber, const string* dictionary);
bool wordIsInDictionary(const char* word, const string* dictionary);
void toLowerCase(char* text);
void toLowerCase(string& text);
void insertion_sort(string* list);

int main()
{
    const string wordfile = "c:/temp/unsorted_words.txt";
    const string testfile = "c:/temp/gettysburg.txt";
    char buffer[1024];
    string word;

    string* dictionary = new string[DictionarySize];
    getDictionary(wordfile, dictionary);

    // sort the dictionary
    insertion_sort(dictionary);

    int lineNumber = 0;

    // read a process file to be spell checked
    ifstream fin(testfile.c_str());
    if (!fin)
    {
        cerr << "Unable to open word file " << testfile << endl;
        exit(2);
    }

    while (!fin.eof())
    {
        lineNumber++;
        fin.getline(buffer,sizeof(buffer));
        if (fin.eof()) break;
        toLowerCase(buffer);
        spellCheckLine(buffer,lineNumber, dictionary);
    }
    delete [] dictionary;
}

void spellCheckLine(char* line, int lineNumber, const string* dictionary)
{
    char* ptr = line;

    ptr = strtok(line," ,.\r");
    while(ptr != NULL)
    {
        if(!wordIsInDictionary(ptr, dictionary))
        {
            cout << "Misspelled word, " << ptr << " on  line " << lineNumber << endl;
        }

        ptr = strtok(NULL," ,.-\r");
    }
}


void getDictionary(const string& filename, string* dictionary)
{

    ifstream fin(filename.c_str());
    if (!fin)
    {
        cerr << "Unable to open word file " << filename << endl;
        exit(1);
    }

    cout << "Reading the Dictionary File ..." << endl;

    for (int i = 0; i < DictionarySize; i++)
    {
        fin >> dictionary[i];
        toLowerCase(dictionary[i]);
    }
}

bool wordIsInDictionary(const char* word, const string* dictionary)
{
    int low, high, middle;
    string word_string(word);
    low = 0;
    high = DictionarySize - 1;
    string middleWord;
    int compare;

    while (low <= high)
    {
        middle = (low + high) / 2;
        middleWord = dictionary[middle];
        compare = strcmp(word,middleWord.c_str());
        if (compare < 0)
        {
            high = middle - 1;
        }
        else if (compare > 0)
        {
            low = middle + 1;
        }
        else
        {
            return true;
        }
    }

    // look for misspelled word with an 'ed' ending
    if (word_string.substr(word_string.size() - 2, 2) == "ed")
    {
        if (wordIsInDictionary(word_string.substr(0, word_string.size() - 2).c_str(), dictionary))
            return true;
    }

    // look for misspelled word with an 'ed' ending
    if (word_string.substr(word_string.size() - 2, 2) == "ly")
        if (wordIsInDictionary(word_string.substr(0, word_string.size() - 2).c_str(), dictionary))
            return true;

    // look for misspelled word with an 's' ending
    if (word_string.substr(word_string.size() - 1, 1) == "s")
        if (wordIsInDictionary(word_string.substr(0, word_string.size() - 1).c_str(), dictionary))
            return true;

    return false;
}


void toLowerCase(char* text)
{
    for (size_t i = 0; i < strlen(text); i++)
        text[i] = tolower(text[i]);
}

void toLowerCase(string& text)
{
    for (size_t i = 0; i < text.size(); i++)
        text[i] = tolower(text[i]);
}

void insertion_sort(string* list)
{
    int j, k;
    string temp;
    //char temp[32];
    bool found;

    cout << "Sorting the dictionary ..." << endl;

    for (int i = 1; i < DictionarySize; i++)
    {
        // The ith element will be inserted into the "sorted" list in the correct location
        found = false;
        temp = list[i]; // temp will hold the ith element in the "unsorted list
        for (k = 0, j = i - 1; j >= 0 && !found; k++)
        {
            // if temp < the jth element, move it to the j+1st position
            if (temp < list[j])
            {
                list[j + 1] = list[j];
                j--;
            }
            else     // temp is not less than any other elements in the sorted list
            {
                found = true;
            }
        }
        // insert temp into its correct position in the sorted list
        list [j + 1] = temp;
    }
}
