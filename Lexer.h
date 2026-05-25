#pragma once

#include <string>
#include <regex>
#include <vector>

struct TokenRule {
    std::string name;
    std::regex pattern;
};

struct Token {
    std::string name;
    std::string value;
};

class Lexer {
public:
    std::string input;
    std::vector<Token> tokenVec;
    int it;
    const std::vector<TokenRule> token_types{
                {"RULE", std::regex(R"(^rule)")},
                {"IF", std::regex(R"(^if)")},
                {"THEN", std::regex(R"(^then)")},
                {"AND", std::regex(R"(^AND)")},
                {"VALUE", std::regex(R"(^(0|[1-9]\d*))")},
                { "ASSIGN", std::regex(R"(=)")},
                {"COLON", std::regex(R"(:)")},
                {"GREATER", std::regex(R"(>)")},
                {"LESS", std::regex(R"(<)")},
                {"ID", std::regex(R"(^[a-z][a-z0-9_]*)")},
                {"BLANKLINE", std::regex(R"(^#endl)")},
                {"TAB", std::regex(R"(^\t)")},
                {"WHITESPACE", std::regex(R"( )")},
                {"UNKNOWN", std::regex(R"(.)")}
    };

    Lexer(const std::string &input);

    void tokenize();
};