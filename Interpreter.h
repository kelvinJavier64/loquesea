#pragma once
#include <set>
#include <string>
#include "Environment.h"
#include "ASTNode.h"
class Interpreter {
private:
    Environment env;
    std::set<std::string> activatedFacts;
    std::set<std::string> unactivatedFacts;
    std::vector<std::string> conflictMessages;
    std::vector<std::string> redundancyMessages;
    std::vector<std::string> inactiveRuleMessages;
public:
    Interpreter(const Environment& env);
    void interpret(const ASTNode* root);
    void executeRule(const ASTNode *ruleNode);
    bool condition(const ASTNode *condN);
    static bool cmp(const int& x, const std::string& op, const int& v);
    bool fact(std::string x);
    static bool condAND(bool x, bool y);
    void act(const std::string&);

    void static_analysis(const ASTNode *root);

    static bool compareCond(const ASTNode *n1, const ASTNode *n2);
    std::string PotentiallyInactive();
};
