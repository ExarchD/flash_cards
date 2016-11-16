#ifndef MAIN_CPP
#define MAIN_CPP

#include <string>
#include <vector>

class flashes
{
    public:
        struct word_obj
        {
            std::string word;
            std::string def;
            int number;
        };
        void card_init();
        std::vector<std::string> search_dir();
        void exit_program();
        void get_next_flash(std::string &question, std::vector<std::string> &vect_resp);
        int get_input();
        int check_answers(int user_answer);
        void process_response(int user_answer);
        void get_answers(std::vector<word_obj> container, std::vector<std::string> &responses);
        void iterate_number(std::vector<word_obj> &container, std::string, bool);
        void write_files(std::vector<word_obj> container, std::string);
        void read_files(std::vector<word_obj> &container, std::string, int &total);
        struct find_word : std::unary_function<word_obj, bool> {
            std::string word;
            find_word(std::string word):word(word) { }
            bool operator()(word_obj const& m) const {
                return m.word == word;
            }
        };
        struct list_obj
        {
            std::vector<word_obj> list;
            std::string identifier;
        };
        std::vector<list_obj> biglist;
        std::vector<list_obj> biglist_glob;
        std::vector<std::string> responses;
        std::vector<word_obj> completed;
        int isType;
        int index_val;
        int total;
        word_obj answer;
};
#endif
