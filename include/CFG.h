#pragma once

#include <ranges>
#include <set>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <deque>

class CFG {
    std::set<std::string> non_terminal;
    std::set<std::string> terminal;
    std::multimap<std::string, std::vector<std::string>> productions;
    std::string start_symbol;

public:
    CFG() : non_terminal({}), terminal({}), productions({}), start_symbol("\0") {}

    CFG(const std::set<std::string>& non_terminal,
        const std::set<std::string>& terminal,
        const std::multimap<std::string, std::vector<std::string>>& productions,
        std::string  start_symbol)
        : non_terminal(non_terminal),
          terminal(terminal),
          productions(productions),
          start_symbol(std::move(start_symbol)) {}

    // Easier print
    friend std::ostream& operator<<(std::ostream& os, const CFG& cfg) {
        os << "> Non-terminal: {";
        for (auto it = cfg.non_terminal.begin(); it != cfg.non_terminal.end(); ++it) {
            if (it != cfg.non_terminal.begin()) os << ", ";
            os << *it;
        }
        os << "}" << std::endl;

        os << "> Terminals: {";
        for (auto it = cfg.terminal.begin(); it != cfg.terminal.end(); ++it) {
            if (it != cfg.terminal.begin()) os << ", ";
            os << *it;
        }
        os << "}" << std::endl;

        os << "> Productions:" << std::endl;
        for (const auto& [from, to] : cfg.productions) {
            os << "| " << from << " -> ";
            for (const std::string& loc : to) {
                os << loc << " ";
            }
            os << std::endl;
        }

        os << "> Start symbol: " << cfg.start_symbol << "\n";
        return os;
    }

    // Tests if a string belongs to referenced CFG
    [[nodiscard]] bool testMembership(const std::string& input) const;

    // Getter for start symbol
    [[nodiscard]] std::string getStartSymbol() const;

    // Generates accepted strings using values from terminals set
    std::string generate_recursive(const std::string& current, int depth, int max_depth, std::mt19937& rng);

    // Generates a string which belongs to referenced CFG
    std::string generateString(int max_depth = 10);

    bool derive(
        const std::string& current,
        const std::string& input,
        int pos,
        int& end_pos,
        std::optional<std::reference_wrapper<std::deque<std::string>>> derivation = std::nullopt,
        const std::string& current_string = ""
    ) const;

    void deriveString(const std::string& target) const;

    ~CFG() = default;
};