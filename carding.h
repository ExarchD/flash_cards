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
        void exit_program();
        void get_next_flash(std::string &question, std::vector<std::string> &vect_resp);
        int get_input();
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
        std::vector<word_obj> nouns_glob;
        std::vector<word_obj> verbs_glob;
        std::vector<word_obj> nouns;
        std::vector<word_obj> verbs;
        std::vector<word_obj> completed;
        int total;
};
