#ifndef PARSER_HPP
#define PARSER_HPP

#include "rapidjson/document.h"
#include <string>

class Parser{

    private:
        std::string str;
        rapidjson::Document document;
        int parseError = 0;

    public:
        Parser(const std::string &str);

        bool parse();
        int  getError();
        rapidjson::Value &getData();


};

#endif