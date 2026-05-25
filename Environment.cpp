#include "Environment.h"
#include <iostream>

void Environment::setvar(const std::string& name, int value) {
    variables.emplace(name, value);
}

void Environment::setfact(const std::string& name) {
    facts.emplace(name, true);
}

void Environment::setfact(const std::string &name, bool active) {
    facts.emplace(name, active);
}

int Environment::getvar(const std::string& name) {
        if (variables.find(name) != variables.end()) {
            return variables[name];
        }
    std::cerr <<"\033[31m" << "Error: unable to find " << name << " on the variables hash table\033[0m\nPress enter to close.";
        std::cin.get();
        exit(1);
    }

    bool Environment::getfact(const std::string& name) {
        if (facts.find(name) != facts.end()) {
            return facts[name];
        }
        return false;
    }

const std::vector<std::string>& Environment::getshown() {
    return this->shown;
}

const std::vector<std::string>& Environment::getunactive() {
    return this->unactive;
}

void Environment::setshown(const std::string& s, bool add) {
    if (!shown.empty()){
        for (int i = 0; i < shown.size(); i++) {
            if (s == shown[i]) {
                if (add) {
                    return;
                }
                shown.erase(shown.begin()+i);
            }
        }
        shown.push_back(s);
    }
}

void Environment::setunactive(std::string s, bool add) {
    if (!unactive.empty()){
        for (int i = 0; i < unactive.size(); i++) {
            if (s == unactive[i]) {
                if (add) {
                    return;
                }
                unactive.erase(unactive.begin()+i);
            }
        }
        unactive.push_back(s);
    }
}

void Environment::printstate() const {
    std::cout << "Variables:\n";
    if (!variables.empty())
    {
        for (const auto&[fst, snd] : variables) {
        std::cout << '\t' << fst << " = " << snd << '\n';
        }
    }

    std::cout << "Facts:\n";
    if (!facts.empty())
    {
        for (const auto&[fst, snd] : facts) {
            std::cout << std::boolalpha;
            std::cout << '\t' << fst << " = " << snd << '\n';
        }
    }
}
