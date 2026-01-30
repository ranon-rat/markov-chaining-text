#ifndef TOKENIZER_TOKEN_PARSER_HPP
#define TOKENIZER_TOKEN_PARSER_HPP
//
#include <string>
#include <vector>
namespace Tokenizer {
std::vector<std::string> clean_information(std::vector<std::string> &input);

std::vector<std::string> parse_information(std::string &input,
                                           bool parse_words = false);

} // namespace Tokenizer

#endif