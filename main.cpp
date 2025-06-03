#include <Engine.h>
#include <iostream>

int main() {
  Engine &app = Engine::getInstance();

  /* Subtask I - Programatic representation of the following CFG:
  Programmatic representation of the following CFG:
    S -> a S b | Epsilon / Lambda
    CFG = (V, Σ, R, S)
    - V - Non-terminals: { S }
    - Σ - Terminals: { a, b }
    - R - Production rules: { S -> a S b,
                              S -> '' (Lambda) }
    - S - Start symbol: S
  */
  std::cout << std::endl << "Subtask I - Programatic representation of the default CFG" << std::endl;
  app.createCFG(CFGTypes::Default);
  app.displayCurrentCFG();

  /* Subtask II - Generate substrings which belongs to the current CFG
  Limitation:
    - At least 10 strings
    - At most 10 characters / each symbol
  */
  std::cout << std::endl << "Subtask II - Random compatible strings with the default CFG" << std::endl;
  app.generateCompatibleStrings(10, 20);

  /* Subtask III - Derivation */
  std::cout << std::endl << "Subtask III - Given a string, display its derivation" << std::endl;
  app.deriveString("aabb");
  app.deriveString("aab");

  /* Subtask IV - Membership tester */
  std::cout << std::endl << "Subtask IV - Check a given string if it belongs to the current CFG" << std::endl;
  app.testMembership({{"", "aaabbb", "aabbb", "bbaaa", "abba", "bbaa"}});
  app.testMembership();

  /* Subtask V - Recognizer for the following CFG:
  L = {a^n b^n c^n | n >= 1}
  S -> a S b | Epsilon / Lambda
    CFG = (V, Σ, R, S)
    - V - Non-terminals = {S, B}
    - Σ - Terminals = {a, b, c}
    - R - Production rules = { S -> a S b,
                               S -> a B,
                               B -> b c }
    - S - Start symbol = S
   */
  std::cout << std::endl << "Subtask V - Programatic representation of the non-CFG: L = {a^n b^n c^n | n >= 1}" << std::endl;
  app.createCFG(CFGTypes::DefaultNonCFG);
  app.displayCurrentCFG();
  app.generateCompatibleStrings(10, 20);
  app.testMembership({{"", "aaabcbcbc", "aabcbc", "bbaaacc", "aabbcccc", "abc", "aaaaaaabcbbbbbb"}});
  app.testMembership();

  std::cout << std::endl << "Subtask VI - Test a custom CFG" << std::endl;
  app.createCFG(CFGTypes::Another,
                CFG(
                    // Non-terminal
                    {"(", ")"},

                    // Terminal
                    {"a", "b", "c"},

                    // Production rules
                    {
                      {"(", {"a", "b"}},
                      {"(", {"\0"}}

                    // Start symbol
                    },
                    "("
                  )
                );

  app.displayCurrentCFG();
  app.generateCompatibleStrings(10, 20);
  app.testMembership();

  return 0;
}