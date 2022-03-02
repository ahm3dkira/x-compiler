// create compilar sub-set of c programing language

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>

using namespace std;

enum TokenType{
    IF = 100,
    ELSE = 101,
    WHILE = 102,
    FOR = 103,
    SWITCH = 104,
    CASE = 105,
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




    ASSIGNMENT = 200,   // =
    ADDITION = 201,     // +
    SUBTRACTION = 202,  // -
    MULTIPLICATION = 203, // *
    DIVISION = 204,     // /
    MODULUS = 205,      // %
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


    OPEN_PARENTHESIS = 300, // (
    CLOSE_PARENTHESIS = 301, // )
    OPEN_BRACKET = 302,     // [
    CLOSE_BRACKET = 303,    // ]
    OPEN_BRACE = 304,       // {
    CLOSE_BRACE = 305,      // }

    STRING_LITERAL = 800,   // "string"
    CHAR_LITERAL = 801,     // 'c'
    INT_LITERAL = 802,      // 5
    FLOAT_LITERAL = 803,    // 5.5f
    DOUBLE_LITERAL = 804,   // 5.5
    NULL_LITERAL = 805,
    TRUE_LITERAL = 806,
    FALSE_LITERAL = 807,




    // EOF_TOKEN,
    // ERROR
    UNKNOWN

};

struct Token
{
    TokenType type;
    string value;
};

std::stringstream codeStream(char* fileName){
    std::fstream file;
    file.open(fileName, std::ios::in | std::ios::out);
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
    std::map<std::string, TokenType> tokenMap = {
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"while", TokenType::WHILE},
        {"for", TokenType::FOR},
        {"switch", TokenType::SWITCH},
        {"case", TokenType::CASE},
        {"default", TokenType::DEFAULT},
        {"break", TokenType::BREAK},
        {"continue", TokenType::CONTINUE},
        {"return", TokenType::RETURN},
        {"int", TokenType::INT},
        {"char", TokenType::CHAR},
        {"float", TokenType::FLOAT},
        {"double", TokenType::DOUBLE},
        {"void", TokenType::VOID},
        {"struct", TokenType::STRUCT},
        {"union", TokenType::UNION},
        {"enum", TokenType::ENUM},
        {"const", TokenType::CONST},
        {"static", TokenType::STATIC},
        {"auto", TokenType::AUTO},
        {"typedef", TokenType::TYPEDEF},
        {"extern", TokenType::EXTERN},
        {"register", TokenType::REGISTER},
        {"goto", TokenType::GOTO},
        {"sizeof", TokenType::SIZEOF},
        {"signed", TokenType::SIGNED},
        {"unsigned", TokenType::UNSIGNED},
        {"short", TokenType::SHORT},
        {"long", TokenType::LONG},
        {"constant", TokenType::CONSTANT},
        {"operator", TokenType::OPERATOR},
        {"string", TokenType::STRING},

        {"=", TokenType::ASSIGNMENT},
        {"+", TokenType::ADDITION},
        {"-", TokenType::SUBTRACTION},
        {"*", TokenType::MULTIPLICATION},
        {"/", TokenType::DIVISION},
        {"%", TokenType::MODULUS},
        {"++", TokenType::INCREMENT},
        {"--", TokenType::DECREMENT},
        {"==", TokenType::EQUALITY},
        {"!=", TokenType::INEQUALITY},
        {">", TokenType::GREATER_THAN},
        {"<", TokenType::LESS_THAN},
        {">=", TokenType::GREATER_THAN_EQUAL},
        {"<=", TokenType::LESS_THAN_EQUAL},
        {"&&", TokenType::LOGICAL_AND},
        {"||", TokenType::LOGICAL_OR},
        {"!", TokenType::LOGICAL_NOT},

        {"(", TokenType::OPEN_PARENTHESIS},
        {")", TokenType::CLOSE_PARENTHESIS},
        {"[", TokenType::OPEN_BRACKET},
        {"]", TokenType::CLOSE_BRACKET},
        {"{", TokenType::OPEN_BRACE},
        {"}", TokenType::CLOSE_BRACE},
    };
    std::vector<Token> tokens;
    Token token;
    for(auto s : v){
        if(tokenMap.find(s) != tokenMap.end()){
            token.type = tokenMap[s];
            token.value = s;
            tokens.push_back(token);
        }
        else{
            // check if it is a number
            std::regex number("[0-9]+");
            // check if it is a double
            std::regex double_number("[0-9]+\\.[0-9]+");
            // check if it is a float
            std::regex float_number("[0-9]+\\.[0-9]+f");
            // check if it is a char
            std::regex char_literal("'.'");
            // check if it is a string a-zA-Z0-9_ 
            std::regex string_literal("\"[a-zA-Z0-9_]+\"");
            // check if it is a null
            std::regex null_literal("null");
            // check if it is a true
            std::regex true_literal("true");
            // check if it is a false
            std::regex false_literal("false");
            // check if it is a identifier
            std::regex identifier("[a-zA-Z_][a-zA-Z0-9_]*");
            
            if(std::regex_match(s, number)){
                token.type = TokenType::INT_LITERAL;
            }else if(std::regex_match(s, double_number)){
                token.type = TokenType::DOUBLE_LITERAL;
            }else if(std::regex_match(s, float_number)){
                token.type = TokenType::FLOAT_LITERAL;
            }else if(std::regex_match(s, char_literal)){
                token.type = TokenType::CHAR_LITERAL;
            }else if(std::regex_match(s, string_literal)){
                token.type = TokenType::STRING_LITERAL;
            }else if(std::regex_match(s, null_literal)){
                token.type = TokenType::NULL_LITERAL;
            }else if(std::regex_match(s, true_literal)){
                token.type = TokenType::TRUE_LITERAL;
            }else if(std::regex_match(s, false_literal)){
                token.type = TokenType::FALSE_LITERAL;
            }else if(std::regex_match(s, identifier)){
                token.type = TokenType::IDENTIFIER;
            }else{
                token.type = TokenType::UNKNOWN;
            }
           
            token.value = s;
            tokens.push_back(token);
        }
    }
    return tokens;
}


int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cout << "Usage: ./lexer <file>" << std::endl;
        return 1;
    }
    std::stringstream ss = codeStream(argv[1]);
    // step 1: lexical analysis
    clean(ss);
    std::vector<std::string> v = ss_to_str_vector(ss);
    std::vector<Token> tokens = str_vector_to_tokens_vector(v);



    // step 2: syntax analyzer








    return 0;
}