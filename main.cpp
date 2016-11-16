#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "main.h"
#include <dirent.h>
using namespace std;

vector<string> flashes::search_dir ()
{
    string extension="txt";
    std::string curr_directory = "/home/dpluth/Source/flash_cards/cards/";
    DIR* dir_point = opendir(curr_directory.c_str());
    dirent* entry = readdir(dir_point);
    vector<string> results;
    while (entry){
        if (entry->d_type == DT_REG){
            std::string fname = entry->d_name;
            if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos)
            {
                if (fname != "memorized.txt" ) results.push_back(curr_directory+fname);
            }
        }
        entry = readdir(dir_point);
    }
    return results;
}

void flashes::card_init ()
{
    total=0;
    biglist_glob.clear();
    biglist.clear();
    auto word_lists = search_dir();

    for (unsigned int list_index=0; list_index < word_lists.size(); list_index++)
    {
        list_obj NewWordList;
        std::vector<word_obj> list;
        read_files(list,word_lists[list_index],total);
        NewWordList.list=list;
        NewWordList.identifier=word_lists[list_index];
        biglist.push_back(NewWordList);
    }
    biglist_glob=biglist;
    srand (time(NULL));
}

void flashes::get_next_flash(string& question, vector<string>& vect_resp)
{
    if ( total > 0 )
    {
        int random_word_index=rand() % total;

        int count = 0;
        isType = 99;
        index_val=99;
        for (unsigned int x=0; x < biglist.size(); x++)
        {
            for (unsigned int y=0; y < biglist[x].list.size(); y++)
            {
                if (random_word_index >= count )
                {
                    if ( random_word_index < count+biglist[x].list[y].number )
                    {
                        answer=biglist[x].list[y];
                        index_val=y;
                        isType=x;
                    }
                }
                count=count+biglist[x].list[y].number;
            }
        }

        responses.clear();
        responses.push_back(answer.def);
        get_answers(biglist_glob[isType].list, responses);

        std::sort(responses.begin(), responses.end());
        question=answer.word;
        vect_resp=responses;
    }
    else
    {
        responses.clear();
        vect_resp=responses;
        return;

    }
}

int flashes::check_answers(int user_answer)
{
    if ( responses[user_answer] == answer.def )
    {
        return user_answer;
    }
    else
    {
        for (unsigned int y=0; y<responses.size(); y++)
        {
            if ( responses[y] == answer.def )
            {
                return y;
            }
        }
    }
    return -9;
}

void flashes::process_response(int user_answer)
{
    total=total-answer.number;
    if (user_answer == 999) return;
    if ( responses[user_answer] == answer.def )
    {
        biglist[isType].list.erase(biglist[isType].list.begin() + index_val);
        iterate_number(biglist_glob[isType].list,answer.word,true);
    }
    else
    {
        cout << "The answer is '" << answer.def << "'" <<  endl;
        biglist[isType].list.erase(biglist[isType].list.begin() + index_val);
        iterate_number(biglist_glob[isType].list,answer.word,false);
    }
}

void flashes::exit_program()
{
    for (unsigned int x=0; x < biglist.size(); x++)
    {
        if (biglist_glob[x].list.size() !=0) write_files(biglist_glob[x].list, biglist_glob[x].identifier); //fix this...biglist needs to carry the type of data it is
    }
    if (completed.size() != 0 ) write_files(completed, "memorized");
}

void flashes::write_files(vector<word_obj> container, string file)
{
    ofstream myfile;
    myfile.open (file);
    for (unsigned int x=0; x< container.size(); x++)
    {
        myfile << container[x].word << " -- " << container[x].def << " -- " << container[x].number << "\n";
    }
    myfile.close();
}

void flashes::read_files(vector<word_obj>& container, string filename, int& total)
{
    ifstream file (filename);
    string line;
    /* check if file exists */
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            string delimiter = " -- ";
            string word = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            string def = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            int number = stoi(line.substr(0, line.find(delimiter)));

            word_obj newword = {word, def, number};
            if ( number != 0 )
            {
                total=total+number;
                container.push_back(newword);
            }
            else
            {
                completed.push_back(newword);
            }
        }
    }
        file.close();
}

void flashes::iterate_number(vector<word_obj>& container, std::string correct_word, bool down)
{
    vector<word_obj>::iterator it;
    it = std::find_if(container.begin(), container.end(), find_word(correct_word));
    auto pos = std::distance(container.begin(), it);
    if (down) container[pos].number=container[pos].number-1;
    else container[pos].number=container[pos].number+1;
}

int flashes::get_input ()
{
    int x=999;
    std::string s;
    while(x==999)
    {
        if ( cin >> s )
        {
            if ( s == "q" || s == "Q" || s == "QUIT" || s == "quit" ) exit_program();
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

void flashes::get_answers(vector<word_obj> container, vector<string>& responses)
{
    int choices = 3;
    if ( container.size() < 4 )
    {
        choices = container.size()-1;
    }

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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
