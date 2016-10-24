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
    nouns_glob=nouns;
    verbs_glob=verbs;

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
            if ( verbs_glob.size() < 4 )
            {
                choices = verbs_glob.size()-1;
            }

            /* cout << "Is a verb" << endl; */
            int z=0;
            while ( z < choices)
            {
                int randm_response=rand() % verbs_glob.size();
                if(std::find(responses.begin(), responses.end(), verbs_glob[randm_response].def) != responses.end()) 
                {
                } else {
                    responses.push_back(verbs_glob[randm_response].def);
                    z++;
                }
            }
        }

        if ( isType == 2 )
        {
            int choices = 3;
            if ( nouns_glob.size() < 4 )
            {
                choices = nouns_glob.size()-1;
            }
            /* cout << "Is a noun" << endl; */

            int z=0;
            while ( z < choices)
            {
                int randm_response=rand() % nouns_glob.size();
                if(std::find(responses.begin(), responses.end(), nouns_glob[randm_response].def) != responses.end()) 
                {
                } else {
                    responses.push_back(nouns_glob[randm_response].def);
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
        //sanitize(user_answer)

        if ( responses[user_answer-1] == answer.def )
        {
            total=total-answer.number;
            cout << "CORRECT!" << endl;
            if ( isType == 2 )
            {
                nouns.erase(nouns.begin() + index_val);
                iterate_number(nouns_glob,answer.word,true);
            }
            else
            {
                verbs.erase(verbs.begin() + index_val);
                iterate_number(verbs_glob,answer.word,true);
            }
        }
        else
        {
            cout << "WRONG!" << endl;
            if ( isType == 2 )
            {
                nouns.erase(nouns.begin() + index_val);
                iterate_number(nouns_glob,answer.word,false);
            }
            else
            {
                verbs.erase(verbs.begin() + index_val);
                iterate_number(verbs_glob,answer.word,false);
            }
        }
        cout << endl;

    }
    exit();
}

void exit() 
{
    ofstream myfile;
    myfile.open ("test.txt");
    for (int x=0; x< nouns_glob.size(); x++)
    {
        myfile << nouns_glob[x].word << "  --  " << nouns_glob[x].def << "  --  " << nouns_glob[x].number << "\n";
    }
}

void iterate_number(vector<word_obj> container, std::string correct_word, bool down)
{
                vector<word_obj>::iterator it;
                it = std::find_if(container.begin(), container.end(), find_word(correct_word));
                auto pos = std::distance(container.begin(), it);
                if (down) container[pos].number=container[pos].number-1;
                else container[pos].number=container[pos].number+1;
}
