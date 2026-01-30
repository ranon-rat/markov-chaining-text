#include "possibilities.h++"
#include <file-parser.h++>
#include <iostream>
#include <memory>
#include <string>


int main() {


  std::cout << "test\n";
  Possibilities::PossibilitiesMap token_possibilities =
      FileManagement::parse_file("information-test.tokens");

  for (auto &[a, b] : token_possibilities) {
    std::cout << a << ": " << b->repeated << "\n\t";
    for (auto &[k, v] : b->internal_possibilities) {
      std::cout << k << ": " << v << " || ";
    }
    std::cout << "\n";
  }
}