// create compilar sub-set of c programing language

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>

using namespace std;

enum Token{
    IF,
    ELSE,
    WHILE,
    FOR,
    SWITCH,
    CASE,
    DEFAULT,
    BREAK,
    CONTINUE,
    RETURN,
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    VOID,
    STRUCT,
    UNION,
    ENUM,
    CONST,
    STATIC,
    AUTO,
    TYPEDEF,
    EXTERN,
    REGISTER,
    GOTO,
    SIZEOF,
    SIGNED,
    UNSIGNED,
    SHORT,
    LONG,
    CONSTANT,
    IDENTIFIER,
    OPERATOR,
    COMMENT,
    STRING,




    ASSIGNMENT,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULUS,
    INCREMENT,
    DECREMENT,
    EQUALITY,
    INEQUALITY,
    LESS_THAN,
    GREATER_THAN,
    LESS_THAN_EQUAL,
    GREATER_THAN_EQUAL,
    LOGICAL_AND,
    LOGICAL_OR,
    LOGICAL_NOT,


    // EOF_TOKEN,
    // ERROR

};



std::stringstream codeStream(){
    std::fstream file;
    file.open("code.x", std::ios::in | std::ios::out);
    std::stringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss;
}
void clean(std::stringstream &ss){
    std::string s = ss.str();
    // remove comments /* */
    std::regex comment("/\\*(.|\\n)*?\\*/");
    s = std::regex_replace(s, comment, "");
    // remove comments //
    std::regex comment2("//.*");
    s = std::regex_replace(s, comment2, "");
    // "==" -> " == ", "!=" -> " != ", ">" -> " > ", "<" -> " < ", ">=" -> " >= ", "<=" -> " <= ", "&&" -> " && ", "||" -> " || ", "!" -> " ! ", "=" -> " = ", "+" -> " + ", "-" -> " - ", "*" -> " * ", "/" -> " / ", "%" -> " % ", "++" -> " ++ ", "--" -> " -- ", "(" -> " ( ", ")" -> " ) ", "{" -> " { ", "}" -> " } ", "[" -> " [ ", "]" -> " ] ", ";" -> " ; "
    std::regex operators("(==|!=|>|<|>=|<=|&&|\\|\\||!|=|\\+|\\-|\\*|\\/|%)");
    s = std::regex_replace(s, operators, " $1 ");
    // remove spaces, tabs, newlinesm, multiple spaces
    std::regex spaces("[ \t\n]+");
    s = std::regex_replace(s, spaces, "\n");
    ss.str(s);
}
std::vector<std::string> ss_to_str_vector(std::stringstream &ss){
    std::vector<std::string> v;
    std::string s;
    while(ss >> s){
        v.push_back(s);
    }
    return v;
}
std::vector<Token> str_vector_to_tokens_vector(std::vector<std::string> v){
    // map string to token
    std::map<std::string, Token> tokenMap = {
        {"if", Token::IF},
        {"else", Token::ELSE},
        {"while", Token::WHILE},
        {"for", Token::FOR},
        {"switch", Token::SWITCH},
        {"case", Token::CASE},
        {"default", Token::DEFAULT},
        {"break", Token::BREAK},
        {"continue", Token::CONTINUE},
        {"return", Token::RETURN},
        {"int", Token::INT},
        {"char", Token::CHAR},
        {"float", Token::FLOAT},
        {"double", Token::DOUBLE},
        {"void", Token::VOID},
        {"struct", Token::STRUCT},
        {"union", Token::UNION},
        {"enum", Token::ENUM},
        {"const", Token::CONST},
        {"static", Token::STATIC},
        {"auto", Token::AUTO},
        {"typedef", Token::TYPEDEF},
        {"extern", Token::EXTERN},
        {"register", Token::REGISTER},
        {"goto", Token::GOTO},
        {"sizeof", Token::SIZEOF},
        {"signed", Token::SIGNED},
        {"unsigned", Token::UNSIGNED},
        {"short", Token::SHORT},
        {"long", Token::LONG},
        {"constant", Token::CONSTANT},
        {"identifier", Token::IDENTIFIER},
        {"operator", Token::OPERATOR},
        {"comment", Token::COMMENT},
        {"string", Token::STRING},

        {"=", Token::ASSIGNMENT},
        {"+", Token::ADDITION},
        {"-", Token::SUBTRACTION},
        {"*", Token::MULTIPLICATION},
        {"/", Token::DIVISION},
        {"%", Token::MODULUS},
        {"++", Token::INCREMENT},
        {"--", Token::DECREMENT},
        {"==", Token::EQUALITY},
        {"!=", Token::INEQUALITY},
        {">", Token::GREATER_THAN},
        {"<", Token::LESS_THAN},
        {">=", Token::GREATER_THAN_EQUAL},
        {"<=", Token::LESS_THAN_EQUAL},
        {"&&", Token::LOGICAL_AND},
        {"||", Token::LOGICAL_OR},
        {"!", Token::LOGICAL_NOT},
    };
    std::vector<Token> tokens;
    for(auto s : v){
        if(tokenMap.find(s) != tokenMap.end()){
            tokens.push_back(tokenMap[s]);
        }
        else{
            tokens.push_back(Token::IDENTIFIER);
        }
    }
    return tokens;
}


int main()
{
    std::stringstream ss = codeStream();
    clean(ss);
    std::vector<std::string> v = ss_to_str_vector(ss);
    for(auto x : v){
        std::cout << x << std::endl;
    }



    // std::vector<Token> tokens = str_vector_to_tokens_vector(v);
    // todo: validate grammar of tokens
        
    






    return 0;
}