#include <iostream>
#include <algorithm>
#include <assert.h>
#include <dirent.h>
#include "opto.h"
using namespace std;

bool options::check_config ()
{
    config_file="example.cfg";
    try
    {
        cfg.readFile(config_file.c_str());
    }
    catch(const FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        try
        {
            cfg.writeFile(config_file.c_str());
            cerr << "Updated configuration successfully written to: " << config_file << endl;
            return false;

        }
        catch(const FileIOException &fioex)
        {
            cerr << "I/O error while writing file: " << config_file << endl;
        }
    }
    catch(const ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
            << " - " << pex.getError() << std::endl;
    }
    return true;
}

void options::write_opts ()
{
    cout << "write options" << endl;
}

void options::retrieve_enabled_lists ()
{
    read_opts();
    search_dir();
    sort(user_lists.begin(), user_lists.end());
    sort(all_lists.begin(), all_lists.end());
    set_intersection(user_lists.begin(),user_lists.end(),all_lists.begin(),all_lists.end(),back_inserter(enabled_lists));

    assert(enabled_lists.size() > 0); 
}

void options::read_opts ()
{
    card_directory="/home/dpluth/Source/flash_cards/cards/";
    user_lists.push_back(card_directory+"verbs.txt");
}

void options::save_config ()
{
    cfg.writeFile(config_file.c_str());
}

bool options::search_dir ()
{
    string extension="txt";
    DIR  *dir_point;
    if ( (dir_point = opendir(card_directory.c_str())) == NULL)
    {
        return false;
    }
    dirent* entry = readdir(dir_point);
    vector<string> results;
    while (entry){
        if (entry->d_type == DT_REG){
            std::string fname = entry->d_name;
            if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos)
            {
                results.push_back(card_directory+fname);
            }
        }
        entry = readdir(dir_point);
    }
    all_lists=results;
    return true;
}
