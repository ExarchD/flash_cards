#include <iostream>
#include <dirent.h>
#include "opto.h"
using namespace std;

bool options::check_file ()
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

void options::read_opts ()
{
    cout << "read options" << endl;
    card_directory="/home/dpluth/Source/flash_cards/cards/";

    search_dir(card_directory);
    enabled_lists=all_lists;
}

void options::get_lists()
{

    cout << "get lists" << endl;

}

void options::write_file ()
{
    cfg.writeFile(config_file.c_str());
}

void options::search_dir (string word_dir)
{
    string extension="txt";
    std::string curr_directory = word_dir;
    DIR* dir_point = opendir(curr_directory.c_str());
    dirent* entry = readdir(dir_point);
    vector<string> results;
    vector<string> rawresults;
    while (entry){
        if (entry->d_type == DT_REG){
            std::string fname = entry->d_name;
            if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos)
            {
                rawresults.push_back(curr_directory+fname);
                if (fname != "memorized.txt" ) results.push_back(curr_directory+fname);
            }
        }
        entry = readdir(dir_point);
    }
    all_lists=results;
    raw_lists=rawresults;
}
