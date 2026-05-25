#pragma once
#include "ASTNode.h"

class Parser {
private:
    std::vector<Token> tokens; //se crea un vector de tokens osea lo que el usuario quiera poner
    int current = 0; //aqui apunto al token en el punto 0

public:
    Parser(std::vector<Token> tokens, bool print);
    Parser(std::vector<Token> tokens);
    bool print;
    std::vector<Token> matches;
    Token peek();
    void match(const std::string& expected);
    ASTNode* Program();
    void RuleList(ASTNode* parent);
    ASTNode* Rule();
    ASTNode* Cond();
    void CondPrime();
    ASTNode* Atom();
    void AtomPrime();
    void RelOp();
    void Action();
};