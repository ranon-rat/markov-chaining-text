#ifndef POSSIBILITIES_HPP
#define POSSIBILITIES_HPP
//
#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Possibilities {
struct TokenRepetition {
  std::string Token{""};
  size_t repeated{0};
  std::unordered_map<std::string, int> internal_possibilities;
};
typedef std::unordered_map<std::string, std::unique_ptr<TokenRepetition>>
    PossibilitiesMap;
// this is just for internal usage, you better ignore it
std::unique_ptr<TokenRepetition> &
get_or_initialize(std::string key, PossibilitiesMap &token_map);
// this will get you which words have been the most repeated
PossibilitiesMap get_possibilities(std::vector<std::string> &input);

} // namespace Possibilities

#endif