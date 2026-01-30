#include "file-parser.h++"
#include "possibilities.h++"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

#define MAX_PREVIOUS_TOKENS 10
#define USE_WORDS

struct UsedToken {
  double weight{0};
  std::string token{""};
  std::vector<std::string> internal_tokens;
  std::vector<double> weights;
};
typedef std::deque<UsedToken> PreviousTokens;

void apply_temperature(std::vector<double> &w, double T) {
  double sum = 0.0;
  for (auto &x : w) {
    x = std::exp(std::log(x + 1e-12) / T);
    sum += x;
  }
  for (auto &x : w)
    x /= sum;
}

void mix_uniform(std::vector<double> &w, double epsilon) {
  double u = 1.0 / w.size();
  for (auto &x : w)
    x = (1.0 - epsilon) * x + epsilon * u;
}

std::pair<std::vector<std::string>, std::vector<double>>
get_weights(const std::unique_ptr<Possibilities::TokenRepetition> &line) {
  std::vector<double> weights;
  std::vector<std::string> selection;
  double max_value{0};
  for (auto &[val, rep] : line->internal_possibilities) {
    // i wanted to do this to avoid any real problem in the future
    weights.emplace_back((double)rep / (double)line->repeated);
    selection.emplace_back(val);
    if (rep > max_value)
      max_value = rep;
  }
  for (auto &rep : weights)
    rep /= max_value;
  mix_uniform(weights, 0.01);

  return {selection, weights};
}

// the max selection part i shold have something that i could use to avoid any
// real problem with this i wonder how i can generate it?
std::pair<std::string, double>
select_next_token(std::vector<std::string> &selector,
                  std::vector<double> &weights, std::mt19937 &rng) {
  std::discrete_distribution<size_t> dist(weights.begin(), weights.end());
  size_t idx = dist(rng);
  return {selector[idx], weights[idx]};
}

void add_new_weights(PreviousTokens &prev_tokens, UsedToken &token) {
  if (prev_tokens.size() > MAX_PREVIOUS_TOKENS)
    prev_tokens.pop_front();

  for (auto &prev_token : prev_tokens) {
    // with this we know that we have
    if (token.token == prev_token.token)
      return;
  }
  prev_tokens.emplace_back(token);
}
std::pair<std::string, double>
get_token_until_iteration(const Possibilities::PossibilitiesMap &possibilities,
                          UsedToken &token, std::mt19937 &rng, size_t steps) {
  std::string first_token = token.token;
  std::string current = token.token;
  double acc_weight = 1.0;
  for (auto i{0uz}; i < steps; i++) {
    auto it = possibilities.find(current);
    if (it == possibilities.end())
      break;
    auto [tokens, weights] = get_weights(it->second);
    if (tokens.empty())
      break;
    // 0-1
    auto [next_token, weight] = select_next_token(tokens, weights, rng);
    current = next_token;
    acc_weight *= weight;
  }

  return {current, acc_weight};
}

std::pair<std::string, double>
select_on_previous_tokens(const Possibilities::PossibilitiesMap &possibilities,
                          PreviousTokens &prev_tokens, std::mt19937 &rng) {
  std::vector<std::string> selected_tokens;
  std::vector<double> selected_weights;
  size_t divider = prev_tokens.size();
  for (auto &token_info : prev_tokens) {

    auto [token, weight] =
        get_token_until_iteration(possibilities, token_info, rng, divider);
    divider--;

    // std::cout << "weight" << weight << "\n";
    selected_tokens.emplace_back(token);
    selected_weights.emplace_back(weight / std::exp(divider / 5));
  }

  for (size_t i = 0; i < selected_tokens.size(); i++) {
    int count = 0;
    for (size_t j = 0; j < selected_tokens.size(); j++) {
      if (i != j && selected_tokens[i] == selected_tokens[j]) {
        count++;
      }
    }
    if (count > 0) {
      selected_weights[i] *= std::pow(0.97, count);
    }
  }
  mix_uniform(selected_weights, 0.1);
  std::discrete_distribution<size_t> dist(selected_weights.begin(),
                                          selected_weights.end());

  size_t idx = dist(rng);
  return {selected_tokens[idx], selected_weights[idx]};
}
// i should store the previously stored information, but i have to think in how
// a i know how
int main() {
#ifdef USE_WORDS
  bool writting_words = true;
  const Possibilities::PossibilitiesMap possibilities =
      FileManagement::parse_file("data/xenosystems-words.tokens");
#else
  bool writting_words = false;
  const Possibilities::PossibilitiesMap possibilities =
      FileManagement::parse_file("data/xenosystems.tokens");
#endif

  // bool writting_words = true;
  srand(time(0));
  std::mt19937 rng(std::random_device{}());
  if (possibilities.size() == 0) {
    return 1;
  }
  std::cout << "starting...\n";
  // i need to use this to select the first word

  PreviousTokens prev_tokens;
  const std::string first_token = "a";
  std::string next_token = first_token;
  double previous_weight = 0;
  for (auto i{0uz}; i < 1000; i++) {
    auto it2 = possibilities.find(next_token);
    if (it2 == possibilities.end()) {
      next_token = first_token;
      continue;
    }
    auto &value = it2->second;
    auto [tokens, weights] = get_weights(value);
    if (weights.size() == 0) {
      next_token = first_token;
      continue;
    }
    UsedToken used_token = UsedToken{.weight = previous_weight,
                                     .token = next_token,
                                     .internal_tokens = tokens,
                                     .weights = weights};
    //--------//
    add_new_weights(prev_tokens, used_token);
    auto [next_token_new, weight] =
        select_on_previous_tokens(possibilities, prev_tokens, rng);
    if (next_token_new == next_token) {
      i--;
      continue;
    }

    next_token = next_token_new;
    previous_weight = weight;
    std::cout << next_token;
    if (writting_words)
      std::cout << " ";
  }

  return 0;
}