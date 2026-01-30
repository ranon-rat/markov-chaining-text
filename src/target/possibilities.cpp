#include "possibilities.h++"
#include "token-parser.h++"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main() {

  // possibilities, i would need to order it based in possibilities, i would
  // need to add this in a list of possibilities, but lets now think of
  // something simple
  // okay so, now i think ghtat i should add something just in case
  // lets now think of a way of storing this information
  // hmmm what if
  // 28, como separador de linea
  // 29 para buscar en el grupo
  // 30 para que pueda escribir en el archivo las posibilidades
  // v30r29v130 y asi puedo seguir, sheesh, esto va a estar buenardo
  std::cout << "test\n";
  std::string input = R"(
  Hello 
  world
  the world
  is small
  and so little things
  are filled
  with joy
  )";

  auto parts = Tokenizer::parse_information(input);
  parts = Tokenizer::clean_information(parts);
  auto tokens_possibilities = Possibilities::get_possibilities(parts);
  for (auto &[a, b] : tokens_possibilities) {
    std::cout << a << " " << b->repeated << "\n";
    std::cout << '\t';
    for (auto &[k, v] : b->internal_possibilities) {
      std::cout << k << ": " << v << ",";
    }
    std::cout << "\n";
  }
  return 0;
}