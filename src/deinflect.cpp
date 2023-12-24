#include "rule_sets.h"
#include "types.h"
#include <array>
#include <iostream>
#include <string_view>
#include <vector>

template<typename Stored>
auto copy_and_prepend(std::vector<Stored> const& first, Stored&& value) -> std::vector<Stored>
{
  std::vector<Stored> joined = { value };
  joined.insert(joined.cend(), first.cbegin(), first.cend());
  return joined;
}

auto rule_applies(Deinflection const& result, Reason const& rule) -> bool
{
  if (result.rules != RuleType::none and (rule.rules_in & result.rules) == RuleType::none) {
    return false;
  }
  if (not result.term.ends_with(rule.kana_in)) {
    return false;
  }
  if (result.term.size() + rule.kana_out.size() <= rule.kana_in.size()) {
    return false;
  }
  return true;
}

auto deinflect(std::string_view const source) -> std::vector<Deinflection>
{
  std::vector<Deinflection> results{
    Deinflection{
      .term = std::string{ source },
      .rules = RuleType::none,
      .reasons = {},
    },

  };

  for (size_t idx = 0; idx < results.size(); ++idx) {
    for (RuleSet const& ruleset: rulesets) {
      for (Reason const& rule: ruleset.rules) {
        if (rule.empty()) {
          // reached the end of ruleset
          break;
        }
        if (Deinflection const& result = results.at(idx); rule_applies(result, rule)) {
          results.push_back(Deinflection{
            .term = (result.term.substr(0, result.term.size() - rule.kana_in.size()).append(rule.kana_out)),
            .rules = rule.rules_out,
            .reasons = copy_and_prepend(result.reasons, std::string(ruleset.name)),
          });
        }
      }
    }
  }

  return results;
}
