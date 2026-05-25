#include <fstream>
#include "GetSC.h"


void GetSC::readT(std::string& input) {
    std::string buffer;
    std::cout << "Insert source code ($ to finish):\n\n";
    while (true) { // Se lee línea por línea el código del usuario
        std::getline(std::cin, buffer);
        if (!buffer.empty() && buffer.back() == '$') {
            buffer.pop_back();
            input += buffer;
            break;
        }
        // Añadimos la línea actual y el separador al string principal
        input += buffer + "#endl";
    }
}

bool GetSC::readF(std::string & input, const std::string &fileN) {
    std::string buffer;
    std::ifstream file(fileN);

    if (!file.is_open()) {
        std::cerr << "\033[31m" << "Error: Unable to load file '" << fileN <<"\033[0m'";
        std::cout << "\nCreating empty file...\n";
        if(std::ofstream outFile(fileN); outFile.is_open()) {
            return false;
        }
        std::cerr << "\033[31m" << "Error: Unable to create source code file, create it manually\033[0m\nPress enter to close.";
        std::cin.get();
        exit(1);
    }

    bool firstln = true;

    while (std::getline(file, buffer)) {
        if (!firstln) input += "#endl";

        input+=buffer;
        firstln = false;
    }
    return true;
}
