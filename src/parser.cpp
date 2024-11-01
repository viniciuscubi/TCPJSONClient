#include "../include/parser.hpp"

Parser::Parser(const std::string &s){
    str = s;
}

bool Parser::parse(){
    document.Parse(str.c_str());

    if(document.HasParseError()){
        parseError = document.GetParseError();

        return false;
    }

    return true;
}

int Parser::getError() {
    return parseError;
}


rapidjson::Value& Parser::getData() {
    return document;
}
