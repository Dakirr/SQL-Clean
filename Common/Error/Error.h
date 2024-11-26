#ifndef ERROR_H
#define ERROR_H

#include <string> 
bool error(std::string explanation, std::string error_type = "", bool fatal = 1);

class Message {
    public:
    std::string text;

    Message (std::string text) {
        this->text = text;
    }
};
#endif