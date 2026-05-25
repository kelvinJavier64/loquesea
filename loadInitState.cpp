#include <iostream>
#include <fstream>
#include <sstream>
#include "loadInitState.h"

void loadInitState(const std::string& filename, Environment& env) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "\033[31m" << "Error: Couldn't load initial state from: '" << filename << "'" <<"\033[0m";
        std::cout << "\nCreating file...\n";
        if (std::ofstream outFile(filename); outFile.is_open()) {
            //Se agrega la estructura del archivo
            outFile << "[variables]\n\n";
            outFile << "[facts]\n";
            outFile.close();
            std::cout << "\nEmpty initial state file created\nPress enter to close.";
            std::cin.get();
            exit(1);
        }
        std::cerr << "\033[31m" << "Error: Unable to create initial state file, create it manually\nPress enter to close.\033[0m";
        std::cin.get();
        exit(1);
    }
    std::string line;
    std::string currentSection = "";

    while (std::getline(file, line)) {
        // Ignora líneas en blanco o con solo espacios
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }

        if (line[line.find_first_not_of(" \t")] == ';') {
            continue;
        }
        // Detecta cambio de sección
        if (line.find("[variables]") != std::string::npos) {
            currentSection = "variables";
            continue;
        } else if (line.find("[facts]") != std::string::npos) {
            currentSection = "facts";
            continue;
        }
        // Se extraen los datos
        std::stringstream ss(line);
        std::string name, equalsSign, valueStr;

        if (ss >> name >> equalsSign >> valueStr) {
            if (equalsSign == "=") {
                
                //Se procesa según la sección actual
                if (currentSection == "variables") {
                    try {
                        // string -> int
                        int finalValue = std::stoi(valueStr); 
                        env.setvar(name, finalValue);
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "\033[31m" << "Error: The value of '" << name << "' is not a valid integer.\033[0m\n";
                    }
                } 
                else if (currentSection == "facts") {
                    // Evaluar el booleano
                    if (valueStr == "true") {
                        env.setfact(name, true);
                    } else if (valueStr == "false") {
                        env.setfact(name, false);
                    } else {
                        std::cerr << "\033[31m" << "Error: Invalid value for fact: '" << name << "'. true or false expected.\033[0m\n";
                    }
                }
            } else {
                std::cerr << "\033[31m" << "Syntax error: expected '=' instead of '" << equalsSign << "'.\033[0m\n";
            }
        }
    }

    file.close();
    std::cout << "========== Initial state succesfully loaded ==========" << std::endl;
}