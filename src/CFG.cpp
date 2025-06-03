#include "CFG.h"

#include <iostream>

[[nodiscard]] bool CFG::testMembership(const std::string& input) const {
    int end_pos = 0;
    return derive(start_symbol, input, 0, end_pos) && end_pos == static_cast<int>(input.size());
}

[[nodiscard]] std::string CFG::getStartSymbol() const {
    return this->start_symbol;
}

bool CFG::validateConfiguration() const {
    if (!non_terminal.contains(start_symbol)) {
        return false;
    }

    for (const auto& [from, tos] : productions) {
        if (!non_terminal.contains(from)) {
            return false;
        }

        for (const auto& to : tos) {
            if (!non_terminal.contains(to) && !terminal.contains(to) && to != "\0") {
                return false;
            }
        }
    }

    return true;
};


std::string CFG::generate_recursive(const std::string& current, const int depth, const int max_depth, std::mt19937& rng) {
    // If current string is a terminal, the recursion stops
    if (terminal.contains(current)) {
        return current;
    }

    // Rules are defined by transitions from current string (multimapped)
    std::vector<std::vector<std::string>> rules;
    const auto [mmf, mme] = productions.equal_range(current);
    for (auto it = mmf; it != mme; ++it) {
        rules.push_back(it->second);
    }

    // If there are no rules left, the recursion stops
    if (rules.empty()) {
        return "";
    }

    // If the recursion depth hits the maximum level, define epsilon/terminal rules
    if (depth >= max_depth) {
        std::vector<std::vector<std::string>> terminal_rules, epsilon_rules;
        for (const auto& rule : rules) {
            if (rule.empty()) {
                epsilon_rules.push_back(rule);
            } else {
                bool all_terminal = true;
                for (const auto& to : rule) {
                    if (!terminal.contains(to)) {
                        all_terminal = false;
                        break;
                    }
                }
                if (all_terminal) {
                    terminal_rules.push_back(rule);
                }
            }
        }
        rules = !terminal_rules.empty() ? rules = terminal_rules : !epsilon_rules.empty() ? rules = epsilon_rules : rules;
    }

    // Uniform distribution for defined rules
    std::uniform_int_distribution<> dist(0, rules.size() - 1);
    const auto& chosen_rule = rules[dist(rng)];
    std::string result;
    for (const std::string& sym : chosen_rule) {
        result += generate_recursive(sym, depth + 1, max_depth, rng);
    }

    return result;
}

std::string CFG::generateString(const int max_depth) {
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    return generate_recursive(start_symbol, 0, max_depth, rng);
}

bool CFG::derive(
    const std::string& current,
    const std::string& input,
    int pos,
    int& end_pos,
    std::optional<std::reference_wrapper<std::deque<std::string>>> derivation,
    const std::string& current_string
) const {
    const auto [mmf, mme] = productions.equal_range(current);

    for (auto it = mmf; it != mme; ++it) {
        const std::vector<std::string>& rhs = it->second;
        int temp_pos = pos;
        bool match = true;

        std::string rhs_combined;
        for (const auto& sym : rhs) rhs_combined += sym;

        std::string new_string = current_string;
        if (!new_string.empty()) {
            size_t replace_pos = new_string.find(current);
            if (replace_pos != std::string::npos) {
                new_string.replace(replace_pos, current.length(), rhs_combined);
            }
        } else {
            new_string = rhs_combined;
        }

        for (const auto& symbol : rhs) {
            if (terminal.contains(symbol)) {
                if (temp_pos >= static_cast<int>(input.size()) || input[temp_pos] != symbol[0]) {
                    match = false;
                    break;
                }
                temp_pos++;
            } else if (non_terminal.contains(symbol)) {
                int next_pos;
                if (!derive(symbol, input, temp_pos, next_pos, derivation, new_string)) {
                    match = false;
                    break;
                }
                temp_pos = next_pos;
            }
        }

        if (match) {
            end_pos = temp_pos;
            if (derivation.has_value()) {
                derivation.value().get().push_back(new_string);
            }
            return true;
        }
    }

    return false;
}

void CFG::deriveString(const std::string& target) const {
    std::deque<std::string> derivation;
    derivation.push_front(start_symbol);
    int end_pos = 0;
    if (derive(start_symbol, target, 0, end_pos, derivation, start_symbol) && end_pos == static_cast<int>(target.size())) {
        std::cout << std::format("| {}", derivation.front());
        derivation.pop_front();
        while (!derivation.empty()) {
            std::cout << " -> " << derivation.back();
            derivation.pop_back();
        }
        std::cout << std::endl << std::format("|> Successfully derived from {} to {}", start_symbol, target) << std::endl;
    } else {
        std::cout << std::format("|> Failed to derive from {} to {}", start_symbol, target) << std::endl;
    }
}