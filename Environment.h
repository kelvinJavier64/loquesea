#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Environment {
private:
    std::unordered_map<std::string, int> variables;
    std::unordered_map<std::string, bool> facts;
    std::vector<std::string> shown;
    std::vector<std::string> unactive;

public:
    void setvar(const std::string& name, int value);
    void setfact(const std::string &name);
    void setfact(const std::string &name, bool);
    int getvar(const std::string &name);
    bool getfact(const std::string &name);
    void setshown(const std::string& s, bool add);
    void setunactive(std::string s, bool add);
    const std::vector<std::string>& getshown();
    const std::vector<std::string>& getunactive();
    void printstate() const;
};
