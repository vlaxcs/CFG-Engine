#pragma once

#include "Engine.h"
#include <iostream>

void Engine::setCurrentCFG(const CFG& temp) {
    currentCFG = std::make_shared<CFG>(temp);
}

std::shared_ptr<CFG>& Engine::getCurrentCFG() {
    return currentCFG;
}

void Engine::displayCurrentCFG() const {
    std::cout << *currentCFG;
}

void Engine::createCFG(const std::optional<CFGTypes>& type, const std::optional<CFG>& new_cfg) {
    if (type.has_value() && type.value() == CFGTypes::Default) {
        std::set<std::string> variables;
        std::set<std::string> terminals;
        std::multimap<std::string, std::vector<std::string>> productions;

        // Non-terminal
        variables.insert("S");

        // Terminal
        terminals.insert("a");
        terminals.insert("b");

        // Start symbol
        std::string start_symbol = "S";

        // Productions
        productions.insert({"S", {"a", "S", "b"}});
        productions.insert({"S", {}}); // Include Epsilon

        if (const CFG temp(variables, terminals, productions, start_symbol); temp.validateConfiguration()) {
            setCurrentCFG(temp);
        } else {
            std::cerr << "Configuration is invalid!" << std::endl << temp << std::endl;
        }
    } else if (type.has_value() && type.value() == CFGTypes::DefaultNonCFG) {
        std::set<std::string> variables;
        std::set<std::string> terminals;
        std::multimap<std::string, std::vector<std::string>> productions;

        // Non-terminal
        variables.insert("S");
        variables.insert("C");
        variables.insert("D");

        // Terminal
        terminals.insert("a");
        terminals.insert("b");
        terminals.insert("c");

        // Start symbol
        std::string start_symbol = "S";

        // Productions
        productions.insert({"S", {"a", "S", "b", "C"}});
        productions.insert({"C", {"c", "D"}});
        productions.insert({"S", {"\0"}}); // Include Epsilon
        productions.insert({"D", {"\0"}}); // Include Epsilon

        if (const CFG temp(variables, terminals, productions, start_symbol); temp.validateConfiguration()) {
            setCurrentCFG(temp);
        } else {
            std::cerr << "Configuration is invalid!" << std::endl << temp << std::endl;
        }
    } else if (new_cfg.has_value()) {
        if (new_cfg.value().validateConfiguration()) {
            setCurrentCFG(new_cfg.value());
        } else {
            std::cerr << "Configuration is invalid!" << std::endl << new_cfg.value() << std::endl;
        }
    }
}

void Engine::generateCompatibleStrings(const int string_count, const int max_length) const {
    std::set<std::string> used;
    for (int i = 1; i <= string_count; ++i) {
        std::string temp = currentCFG->generateString(max_length);
        int tries(0);
        while (used.contains(temp) && tries < 10) {
            temp = currentCFG->generateString(max_length);
            tries++;
        }
        if (tries == 10) {
            break;
        }

        std::cout << std::format("#{}: {}", i, temp) << std::endl;
        used.insert(temp);
    }
}

void Engine::testMembership(std::optional<std::vector<std::string>> default_strings) const {
    if (default_strings.has_value()) {
        std::cout << "> Check default strings:" << std::endl;
        for (std::string str : default_strings.value()) {
            std::cout <<
                std::format("| String '{}': {}",
                str,
                currentCFG->testMembership(str) ? "Accepted" : "Rejected")
                << std::endl;
        }
    } else {
        std::cout << "> Check user strings:" << std::endl;
        std::string temp_string;
        std::cout << "(!) Enter a string to verify [-1 to cancel]:" << std::endl;
        std::cin >> temp_string;
        while (temp_string != "-1") {
            std::cout <<
                    std::format("| String '{}': {}",
                    temp_string,
                    currentCFG->testMembership(temp_string) ? "Accepted" : "Rejected")
                    << std::endl;

            std::cout << "Enter a string to verify [-1 to cancel]:" << std::endl;
            std::cin >> temp_string;
        }
    }
}

void Engine::deriveString(const std::string& target) const {
    std::cout << std::format("| Trying to derive {} to {} from current CFG", currentCFG->getStartSymbol(), target) << std::endl;
    currentCFG->deriveString(target);
}

