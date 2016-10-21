#include <vector>
#include <algorithm> 
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
    int total=0;
    if (nounfile.is_open())
    {
        while ( getline (nounfile,line) )
        {
            string delimiter = " -- ";
            string word = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            string def = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            int number = stoi(line.substr(0, line.find(delimiter)));
            total=total+number;
            word_obj newword = {word, def, number};
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
            line.erase(0, line.find(delimiter) + delimiter.length());
            int number = stoi(line.substr(0, line.find(delimiter)));
            total=total+number;
            word_obj newword = {word, def, number};
            verbs.push_back(newword);
        }
        verbfile.close();
    }
    vector<word_obj> nouns2=nouns;
    vector<word_obj> verbs2=verbs;

    srand (time(NULL));
    while ( total > 0 )
    {
        int random_word_index=rand() % total;

        word_obj answer;
        int count = 0;
        int isType = 99;
        int index_val=99;
        for (unsigned int x=0; x < verbs.size(); x++)
        {
            if (random_word_index >= count )
            {
                if ( random_word_index < count+verbs[x].number )
                {
                    answer=verbs[x];
                    index_val=x;
                    isType=1;
                }
            }
            count=count+verbs[x].number;
        }
        if ( random_word_index >= count )
        {
            for (unsigned int x=0; x < nouns.size(); x++)
            {
                if (random_word_index >= count )
                {
                    if ( random_word_index < count+nouns[x].number )
                    {
                        answer=nouns[x];
                        index_val=x;
                        isType=2;
                    }
                }
                count=count+nouns[x].number;
            }
        }
        cout << answer.word<< ": "<< endl;

        vector<string> responses;
        responses.push_back(answer.def);
        if ( isType == 1 )
        {
            int choices = 3;
            if ( verbs2.size() < 4 )
            {
                choices = verbs2.size()-1;
            }

            /* cout << "Is a verb" << endl; */
            int z=0;
            while ( z < choices)
            {
                int randm_response=rand() % verbs2.size();
                if(std::find(responses.begin(), responses.end(), verbs2[randm_response].def) != responses.end()) 
                {
                } else {
                    responses.push_back(verbs2[randm_response].def);
                    z++;
                }
            }
        }

        if ( isType == 2 )
        {
            int choices = 3;
            if ( nouns2.size() < 4 )
            {
                choices = nouns2.size()-1;
            }
            /* cout << "Is a noun" << endl; */

            int z=0;
            while ( z < choices)
            {
                int randm_response=rand() % nouns2.size();
                if(std::find(responses.begin(), responses.end(), nouns2[randm_response].def) != responses.end()) 
                {
                } else {
                    responses.push_back(nouns2[randm_response].def);
                    z++;
                }
            }
        }

        cout << endl;
        std::sort(responses.begin(), responses.end());
        for ( int y=0; y < responses.size(); y++)
        {
            cout << y+1 << ") " << responses[y] << endl;
        }


        int user_answer;
        //need to sanitize input
        cin >> user_answer;

        if ( responses[user_answer-1] == answer.def )
        {
            total=total-answer.number;
            cout << "CORRECT!" << endl;
            if ( isType == 2 )
            {
                cout << nouns[index_val].word << endl;
                nouns.erase(nouns.begin() + index_val);
            }
            else
            {
                cout << verbs[index_val].word << endl;
                verbs.erase(verbs.begin() + index_val);
            }
        }
        cout << endl;

    }

}
