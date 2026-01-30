
#include "token-parser.h++"
#include <cctype>
#include <string>
#include <vector>

std::vector<std::string>
Tokenizer::clean_information(std::vector<std::string> &input) {
  std::vector<std::string> output;
  bool coming_from_space = false;
  bool coming_from_end_line = false;
  for (auto &info : input) {
    if (info == " ") {
      if (!coming_from_space) {
        output.push_back(info);
      }
      coming_from_space = true;
      continue;
    }
    if (info == "\n") {
      if (!coming_from_end_line) {
        output.push_back(info);
      }
      coming_from_end_line = true;
      continue;
    }
    coming_from_space = false;
    coming_from_end_line = false;
    output.push_back(info);
  }
  return output;
}

std::vector<std::string> Tokenizer::parse_information(std::string &input,
                                                      bool parse_words) {
  std::vector<std::string> parts;
  std::string carrier = "";
  // i need a splitter
  bool last_vocal = false;
  for (auto c : input) {
    c = std::tolower(c);
    if (c == '\0')
      continue;

    if (parse_words) {
      if (c == ' ' || c == '\n' || c == '\t' || c == '.' || c == ',' ||
          c == '(' || c == ')') {
        if (!carrier.empty())
          parts.push_back(carrier);
        carrier = "";
        continue;
      }
      if (c == '?' || c == '!' || c == '-') {
        if (!carrier.empty())
          parts.push_back(carrier);
        parts.push_back(std::string{c});
        carrier = "";
        continue;
      }
      carrier += (c);
      continue;
    }
    if (c == 'A' || c == 'a' || c == 'e' || c == 'E' || c == 'i' || c == 'I' ||
        c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'w' || c == 'W' ||
        c == 'y' || c == 'Y') {
      // then we can continue
      last_vocal = true;
    } else if (c != ' ' && c != '\n' && c != '\t' && c != '.' && c != ',' &&
               c != '(' && c != ')' && c != '-') {
      if (last_vocal || (c >= '0' && c <= '9')) {
        parts.push_back(carrier);
        carrier = "";
      }
      last_vocal = false;
    } else {
      parts.push_back(carrier);
      parts.push_back(std::string{' '});
      carrier = "";
      continue;
    }
    carrier += (c);
  }
  if (carrier != "") {
    parts.push_back(carrier);
  }
  return clean_information(parts);
}