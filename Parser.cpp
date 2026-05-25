#include <iostream>
#include <utility>
#include "Lexer.h"
#include "Parser.h"

//Ahora que tenemos el analizador lexico tenenmos que hacer el parser que verifica la gramatica LL(1), o sea esta:
//Program -> RuleList
//RuleList -> Rule blankline RuleList | ε
//Rule -> rule id : if Cond then Action
//Cond -> Atom CondPrime
//CondPrime -> AND Atom CondPrime | ε
//Atom -> id AtomPrime
//AtomPrime -> RelOp value | ε
//RelOp -> > | < | =
//Action -> id
Parser::Parser(std::vector<Token> tokens, const bool print) {
    this->tokens = std::move(tokens);
    this->print = print;
}

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = std::move(tokens);
    this->print = false;
}

Token Parser::peek() { //esto simplemente regresa el tokens en el que estoy para comenzar
        return tokens[current];
    }

void Parser::match(const std::string &expected) { //esto es importantisimo para el parser verifica que el valor si sea el esperado
        if (peek().name == expected) { //si lo es entra en el if si no sale el error
            if (print == true) {
                std::cout << "MATCH -> " << peek().name << " : " << peek().value << std::endl;
            }
            current++; //current avanza al siguiente
        } else {
            std::cout << "\nSyntax Error" << std::endl;
            std::cout << "Expected: " << expected << std::endl;
            std::cout << "Found: " << peek().name << " -> " << peek().value << "\nPress enter to close.";
            std::cin.get();
            exit(1);
        }
    }

ASTNode* Parser::Program() { //el programa como se definio en el lenguaje llama a RuleList
    ASTNode* root = new ASTNode("PROGRAM");
    RuleList(root); //nos vamos a la funcion rule RuleList
        if (peek().name == "EOF") {
            std::cout << "\nSTRING ACCEPTED" << std::endl;
        } else {std::cout<< "\nERROR: Leftover tokens" << std::endl;
            std::cout << "Found: " << peek().name << " -> " << peek().value << "\nPress enter to close.";
            std::cin.get();
            exit(1);
        }
    return root;
    }


void Parser::RuleList(ASTNode* parent) { //praticamente esperamos que el token sea rule  y como se definio en la gramatica de RuleList podemos ir Rule RuleList | ε
    if (peek().name == "RULE") {
        ASTNode* ruleNode = Rule(); //vamos a rule
        parent->addChild(ruleNode);
        RuleList(parent); //se regresa a RuleList
        }
    }

ASTNode* Parser::Rule() { //Rule -> rule id : if Cond then Action
    match("RULE");
    std::string ruleName = peek().value;
    match("ID");
    match("COLON");
    match("IF");
    ASTNode* cond = Cond();
    match("THEN");
    std::string action = peek().value;
    match("ID");

    ASTNode* ruleNode = new ASTNode("RULE", ruleName);
    ruleNode->addChild(cond);
    ruleNode->addChild(new ASTNode("ACTION", action));
    return ruleNode;
    }

ASTNode *Parser::Cond() { // Cond -> Atom CondPrime
    ASTNode* left = Atom();
    while (peek().name == "AND") {
        match("AND");
        ASTNode* right = Atom();
        ASTNode* andNode = new ASTNode("AND");
        andNode->addChild(left);
        andNode->addChild(right);
        left = andNode;
    }
    return left;
    }

    void Parser::CondPrime() { // CondPrime -> AND Atom CondPrime | epsilon

        if (peek().name == "AND") {

            match("AND"); // consume un AND
            const ASTNode* temp = Atom(); //lama a atom igual y a CondPrime
            delete temp;
            CondPrime();
        }
    }

ASTNode* Parser::Atom() {
    std::string id = peek().value;
    match("ID");
    if (peek().name == "GREATER" || peek().name == "LESS" || peek().name == "ASSIGN") {
        std::string op;
        if (peek().name == "GREATER") {
            op = ">";
            match("GREATER");
        } else if (peek().name == "LESS") {
            op = "<";
            match("LESS");
        } else {
            op = "=";
            match("ASSIGN");
        }
        std::string value = peek().value;
        match("VALUE");
        ASTNode* cond = new ASTNode("COND");
        cond->addChild(new ASTNode("ID", id));
        cond->addChild(new ASTNode("OP", op));
        cond->addChild(new ASTNode("VALUE", value));
        return cond;
    } else {
        // Solo un hecho (ID)
        ASTNode* fact = new ASTNode("FACT");
        fact->addChild(new ASTNode("ID", id));
        return fact;
    }
}
    // AtomPrime -> RelOp value | epsilon
    void Parser::AtomPrime() {
        if (
            peek().name == "GREATER" || //si consigue algunos de estos en el if entra a RelOp
            peek().name == "LESS" ||
            peek().name == "ASSIGN"
        ) {

            RelOp(); //llamamos a   RelOp
            match("VALUE"); //consume el value que se sigue a "GREATER", "LESS", "ASSIGN"
        }
    }
    // RelOp -> > | < | =
    void Parser::RelOp() { //aqui si encunetra que el token sea igual a los definidos los consume
        if (peek().name == "GREATER") {
            match("GREATER");
        }
        else if (peek().name == "LESS") {
            match("LESS");
        }
        else if (peek().name == "ASSIGN") {
            match("ASSIGN");
        }
        else {
            std::cout << "ERROR: relational operator expected\nPress Enter to close";
            std::cin.get();
            exit(1);
        }
    }
    // Action -> id
    void Parser::Action() {
        match("ID"); //consume un id solamente
    }