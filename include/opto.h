#ifndef OPTO_CXX
#define OPTO_CXX

#include <libconfig.h++>
#include <string>
#include <vector>

using namespace libconfig;

class options
{
    public:
        /* bool check_file (std::string config_file="example.cfg"); */
        bool check_config ();
        void read_opts ();
        void write_opts ();
        void save_config ();
        void retrieve_enabled_lists ();

        std::string settings_directory;
        std::string card_directory;
        std::vector<std::string> activated_cards;
        std::vector<std::string> enabled_lists;
        std::vector<std::string> all_lists;

    private:
        Config cfg;
        std::string config_file;
        bool find_file ();
        std::vector<std::string> user_lists;
        bool search_dir ();

};
#endif
