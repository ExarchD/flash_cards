#include <vector>
#include <iostream>
#include <fstream>
#include "carding.h"
using namespace std;
int main () 
{
    ifstream nounfile ("nouns.txt");
    ifstream verbfile ("verbs.txt");
    vector<word_obj> nouns;
    vector<word_obj> verbs;
    string line;
    if (nounfile.is_open())
    {
        while ( getline (nounfile,line) )
        {
            string delimiter = " -- ";
            string word = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            string def = line.substr(0, line.find(delimiter));
            word_obj newword = {word, def};
            nouns.push_back(newword);
        }
        nounfile.close();
    }

    if (verbfile.is_open())
    {
        while ( getline (verbfile,line) )
        {
            string delimiter = " -- ";
            string word = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            string def = line.substr(0, line.find(delimiter));
            word_obj newword = {word, def};
            verbs.push_back(newword);
        }
        verbfile.close();
    }

    for (int x=0; x < verbs.size(); x++)
    {
        cout << verbs[x].word << "  " << verbs[x].def << endl;
    }


}
