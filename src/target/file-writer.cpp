#include <fstream>
#include <sstream>
#include <string>

#include "file-parser.h++"
#include "possibilities.h++"
#include "token-parser.h++"

int main() {
  std::ifstream data_file("data/Xenosystems-Fragments.txt");
  // so i need to read the whole content
  std::ostringstream content;
  content << data_file.rdbuf();
  std::string data = content.str();

  auto parts = Tokenizer::parse_information(data);
  parts = Tokenizer::clean_information(parts);
  auto word_parts = Tokenizer::parse_information(data, true);
  word_parts = Tokenizer::clean_information(word_parts);
  //
  auto possibilities = Possibilities::get_possibilities(parts);
  auto possibilities_words = Possibilities::get_possibilities(word_parts);
  FileManagement::write_to_file("data/xenosystems.tokens", possibilities);
  FileManagement::write_to_file("data/xenosystems-words.tokens",
                                possibilities_words);

  return 0;
}