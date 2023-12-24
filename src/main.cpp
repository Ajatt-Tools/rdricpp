#include "rule_sets.h"
#include "types.h"
#include <array>
#include <iostream>
#include <string_view>
#include <vector>

struct Deinflection
{
  std::string term{};
  RuleType rules{};
  std::vector<std::string> reasons{};
};

template<typename Stored, size_t Size>
auto& operator<<(std::ostream& os, std::array<Stored, Size> const& array)
{
  for (auto const& item: array) { os << item << ' '; }
  os << '\n';
  return os;
}

auto& operator<<(std::ostream& os, Reason const& reason)
{
  os << "{ .kana_in=" << reason.kana_in << ", .kana_out=" << reason.kana_out << ", .rules_in=" << reason.rules_in
     << ", .rules_out=" << reason.rules_out << " }\n";
  return os;
}

auto& operator<<(std::ostream& os, RuleSet const& ruleset)
{
  os << "{ .name=\"" << ruleset.name << "\", .rules=" << ruleset.rules << " }\n";
  return os;
}

auto& operator<<(std::ostream& os, Deinflection const& deinflection)
{
  os << deinflection.term;
  return os;
}

auto& operator<<(std::ostream& os, std::vector<Deinflection> const& deinflections)
{
  for (auto const& deinflection: deinflections) {
    os << deinflection << ", ";
  }
  os << '\n';
  return os;
}

template<typename Stored>
auto concat(std::vector<Stored> const& first, std::vector<Stored> const& second) -> std::vector<Stored>
{
  std::vector<Stored> joined = first;
  joined.insert(joined.cend(), second.cbegin(), second.cend());
  return joined;
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
    Deinflection const result = results.at(idx);

    for (RuleSet const& ruleset: rulesets) {
      for (Reason const& rule: ruleset.rules) {
        if (rule.empty()) {
          // reached the end of ruleset
          break;
        }

        if (
          ((result.rules != RuleType::none) and ((rule.rules_in & result.rules) == RuleType::none))
          or not result.term.ends_with(rule.kana_in)
          or (result.term.size() - rule.kana_in.size() + rule.kana_out.size()) <= 0
        ) {
          continue;
        } else {
          results.push_back(Deinflection{
            .term = (result.term.substr(0, result.term.size() - rule.kana_in.size()).append(rule.kana_out)),
            .rules = rule.rules_out,
            .reasons = concat(
              result.reasons,
              std::vector{
                std::string(ruleset.name),
              }
            ),
          });
        }
      }
    }
  }

  return results;
}

int main()
{
  // std::cout << rulesets.front() << std::endl;
  std::cout << deinflect("食べさせられたくなかった");
   return 0;
}
