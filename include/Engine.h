#pragma once

#include "CFG.h"

#include "types/cfg_types.h"
#include <string>
#include <optional>
#include <memory>
#include <format>

class Engine{
private:
  std::shared_ptr<CFG> currentCFG;
  Engine() : currentCFG(std::make_shared<CFG>()) {}

public:
    static Engine &getInstance(){
        static Engine instance;
        return instance;
    }

    Engine(const Engine&) = delete;
    Engine &operator=(const Engine&) = delete;

    void createCFG(const std::optional<CFGTypes>& type = std::nullopt, const std::optional<CFG>& new_cfg = std::nullopt);

    void setCurrentCFG(const CFG& temp);

    std::shared_ptr<CFG>& getCurrentCFG();

    void displayCurrentCFG() const;

    void generateCompatibleStrings(int string_count, int max_length) const;

    void testMembership(std::optional<std::vector<std::string>> default_strings = std::nullopt) const;

    void deriveString(const std::string& target) const;

    ~Engine() = default;
};