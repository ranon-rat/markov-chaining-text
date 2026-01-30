#ifndef FILE_PARSER_HPP
#define FILE_PARSER_HPP
//
#include "possibilities.h++"
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

//
#define VALUE_SEPARATOR ((char)30)
#define OBJECT_SEPARATOR ((char)20)
#define LINE_SEPARATOR ((char)28)

namespace FileManagement {

void write_to_file(std::string filename,
                   Possibilities::PossibilitiesMap &possibilities);
// internal process
std::vector<std::string> split(const std::string &line, char delim);
// in case you are a schitzo, but just avoid using this.
std::vector<std::pair<std::string, size_t>> parse_line(std::string &line);
Possibilities::PossibilitiesMap parse_file(std::string filename);
}; // namespace FileManagement
#endif