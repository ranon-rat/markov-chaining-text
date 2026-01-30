#include "token-parser.h++"
#include <iostream>
#include <string>
#include <vector>

int main() {
  // okay here i should be using a simple set of possibilities
  // i need to parse this depending on each possibility of what comes next
  // i coul dbe using this as a simple parser, i wonder how much information i
  // can extract
  std::string set = R"(
  Hello 
  world
  the world
  is small
  and so little things
  are filled
  with joy
  )";
  // i need to first divide it into pieces
  std::vector<std::string> parts = Tokenizer::parse_information(set);
  parts = Tokenizer::clean_information(parts);

  // now i need to parse it
  for (const auto &part : parts) {
    std::cout << part << ",\n";
  }
  return 0;
}