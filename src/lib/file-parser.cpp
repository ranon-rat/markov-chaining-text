#include "file-parser.h++"
#include "possibilities.h++"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

void FileManagement::write_to_file(
    std::string filename, Possibilities::PossibilitiesMap &possibilities) {
  std::ofstream file(filename);
  for (auto &[a, b] : possibilities) {
    file << a << VALUE_SEPARATOR << b->repeated << OBJECT_SEPARATOR;
    for (auto &[k, v] : b->internal_possibilities) {
      file << k << VALUE_SEPARATOR << v << OBJECT_SEPARATOR;
    }
    file << LINE_SEPARATOR;
  }
}

std::vector<std::string> FileManagement::split(const std::string &line,
                                               char delim) {
  std::vector<std::string> partes;
  std::stringstream ss(line);
  std::string parte;
  while (std::getline(ss, parte, delim)) {
    if (parte.empty())
      continue;
    partes.push_back(parte);
  }
  return partes;
}

std::vector<std::pair<std::string, size_t>>
FileManagement::parse_line(std::string &line) {
  std::vector<std::pair<std::string, size_t>> output;
  std::vector<std::string> objects = split(line, OBJECT_SEPARATOR);
  for (auto &object : objects) {
    auto pair = split(object, VALUE_SEPARATOR);
    if (pair.size() != 2) {
      continue;
    }
    std::string val = pair[0];
    if (val.empty()) {
      continue;
    }
    size_t repetition = 0;
    try {
      repetition = std::stoi(pair[1]);
    } catch (...) {
      continue;
    }
    output.emplace_back(std::pair{val, repetition});
  }
  return output;
}

Possibilities::PossibilitiesMap
FileManagement::parse_file(std::string filename) {
  Possibilities::PossibilitiesMap output;

  std::ifstream information_tokens(filename);
  if (!information_tokens.is_open()) {
    std::cout << "there was an error\n";
    return output;
  }
  std::string scan_line = "";
  while (std::getline(information_tokens, scan_line, LINE_SEPARATOR)) {
    auto objects = parse_line(scan_line);
    if (objects.size() == 0) {
      continue;
    }
    auto [origin, repetition] = objects[0];

    std::unique_ptr<Possibilities::TokenRepetition> &possibilities =
        output[origin];
    possibilities = std::make_unique<Possibilities::TokenRepetition>(
        Possibilities::TokenRepetition{
            .Token = origin,
            .repeated = repetition,
            .internal_possibilities = std::unordered_map<std::string, int>(),
        });
    for (auto v = objects.begin() + 1; v != objects.end(); v++) {
      auto [key, value] = *v;
      possibilities->internal_possibilities[key] = value;
    }
  }
  return output;
}