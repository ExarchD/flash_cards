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
        if ( isType == 1 ) get_answers(verbs_glob, responses);
        if ( isType == 2 ) get_answers(nouns_glob, responses);

        cout << endl;
        std::sort(responses.begin(), responses.end());
        for ( unsigned int y=0; y < responses.size(); y++)
        {
            cout << y+1 << ") " << responses[y] << endl;
        }

        //need to sanitize input
        int user_answer=get_input();

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
            total=total-answer.number;
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
        myfile << nouns_glob[x].word << " -- " << nouns_glob[x].def << " -- " << nouns_glob[x].number << "\n";
    }
    myfile.close();
    exit (EXIT_SUCCESS);
}

void iterate_number(vector<word_obj>& container, std::string correct_word, bool down)
{
    vector<word_obj>::iterator it;
    it = std::find_if(container.begin(), container.end(), find_word(correct_word));
    auto pos = std::distance(container.begin(), it);
    cout << container[pos].word << endl;
    if (down) container[pos].number=container[pos].number-1;
    else container[pos].number=container[pos].number+1;
}

int get_input ()
{
    int x=999;
    std::string s;
    while(x==999)
    {
        if ( cin >> s ) 
        {
            if ( s == "q" || s == "Q" || s == "QUIT" || s == "quit" ) exit();
            try 
            {
                x=stoi(s);
            }
            catch (const std::invalid_argument& ia) 
            {
                std::cerr << "Invalid argument, insert a number or q/Q \n";
            }
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
    }
    return x;
}

void get_answers(vector<word_obj> container, vector<string>& responses)
{
    int choices = 3;
    if ( container.size() < 4 )
    {
        choices = container.size()-1;
    }

    /* cout << "Is a verb" << endl; */
    int z=0;
    while ( z < choices)
    {
        int randm_response=rand() % container.size();
        if(std::find(responses.begin(), responses.end(), container[randm_response].def) != responses.end()) 
        {
        } else {
            responses.push_back(container[randm_response].def);
            z++;
        }
    }
}
