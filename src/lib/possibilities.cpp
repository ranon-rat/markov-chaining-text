#include "possibilities.h++"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

std::unique_ptr<Possibilities::TokenRepetition> &
Possibilities::get_or_initialize(std::string key, PossibilitiesMap &token_map) {
  std::unique_ptr<TokenRepetition> &info = token_map[key];
  if (!info)
    info = std::make_unique<TokenRepetition>(TokenRepetition{
        .Token = key,
        .repeated = 0,
        .internal_possibilities = std::unordered_map<std::string, int>(),
    });

  return info;
}

Possibilities::PossibilitiesMap Possibilities::get_possibilities(std::vector<std::string> &input) {
  PossibilitiesMap output;
  std::string before = "";
  for (const auto &part : input) {
    if (before == "") {
      before = part;
      continue;
    }
    std::unique_ptr<TokenRepetition> &token_info_before =
        get_or_initialize(before, output);
    token_info_before->repeated++;
    token_info_before->internal_possibilities[part]++;
    before = part;
  }
  std::unique_ptr<TokenRepetition> &token_info_before =
      get_or_initialize(before, output);

  token_info_before->repeated++;
  return output;
}