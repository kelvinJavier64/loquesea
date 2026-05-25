#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Environment.h"
#include "interpreter.h"
#include "loadInitState.h"
#include "GetSC.h"

int main(){
    Environment env;
    std::string opt;
    loadInitState("initState.ini", env);

    std::string input = "";
    std::string fileName = "rules.src";
    while (true) {
        std::cout << "Read source code from " << fileName << "? (T/F)\n";
        std::getline(std::cin, opt);
        if (opt == "T" || opt == "t") {
            if (GetSC::readF(input, fileName)) {
                std::cout << "\n========== Source code succesfully loaded ==========\n";
                break;
            }
            std::cout << "\nFile successfully created\nPress enter to close";
            std::cin.get();
            return 1;
        }
        if (opt == "F" || opt == "f") {
            GetSC::readT(input);
            break;
        }
    }


    Lexer lex(input);
    lex.tokenize();

    std::cout << "\n========== TOKENS ==========\n\n";

    for (auto & i : lex.tokenVec) {
        std::cout
            << "(" << i.name << " , " << i.value << ")" << std::endl;
    }

    std::cout << "\n========== PARSER ==========\n\n";

    Parser parser(lex.tokenVec, true);

    ASTNode* root = parser.Program();

        std::cout << "\n========== AST ==========\n\n";

    root -> print();

        std::cout << "\n========== INITIAL STATE ==========\n\n";

        env.printstate();

        std::cout << "\n========== INTERPRETER ==========\n\n";

        Interpreter interpreter(env);
        interpreter.interpret(root);

        std::cout << "\nExecution finished. Press enter to close.";
        std::cin.get();
    return 0;
}
