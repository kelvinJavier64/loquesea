#include <string>
#include <regex>
#include <vector>
#include "Lexer.h"

//Implementación constructor
Lexer::Lexer(const std::string &input) {
    this->input = input;
    this->it = 0;
}
//Función para dividir el string en las expresiones regulares que lo componen y almacenar su respectivo token
void Lexer::tokenize() {
    std::string::const_iterator pos = input.cbegin(); //Iterador que apunta al primer caracter del string
    const std::string::const_iterator end = input.cend(); //Último caracter
    while (pos < end) {
        std::smatch m;
        for (const auto&[name, pattern] : token_types) { //Se intenta hacer match entre el fragmento siguiente del string y cada ER
            // (inicio, fin, string, ER, flag)
            if (std::regex_search(pos, end, m, pattern, std::regex_constants::match_continuous)) {
                if (name != "WHITESPACE" && name != "BLANKLINE" && name != "TAB") { //Se guardan los tokens en el vector ignorando los espacios y líneas vacías
                    tokenVec.push_back({name, m.str(0)});
                }
                pos += m.length(0); //Se suma al iterador la longitud de la subcadena abarcada por la ER para
                break;
            }
        }
    }
    tokenVec.push_back({"EOF", "$"});
}