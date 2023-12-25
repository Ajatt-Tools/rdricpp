/*
 * Rikaitan Deinflector Reference Implementation
 *
 * Copyright (C) 2023 Ajatt-Tools and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, visit the http://fsf.org website.
 */

#include "rdricpp.h"
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
