#pragma once

#include "types.h"
#include <array>
#include <iostream>
#include <string_view>
#include <vector>

template<typename Stored, size_t Size>
auto& operator<<(std::ostream& os, std::array<Stored, Size> const& array)
{
  for (auto const& item: array) {
    os << item << ' ';
  }
  os << '\n';
  return os;
}

template<typename Stored>
auto& operator<<(std::ostream& os, std::vector<Stored> const& array)
{
  os << "[";
  for (auto const& item: array) {
    os << item << ", ";
  }
  os << "]";
  return os;
}

inline auto& operator<<(std::ostream& os, Reason const& reason)
{
  os << "{ .kana_in=" << reason.kana_in << ", .kana_out=" << reason.kana_out << ", .rules_in=" << reason.rules_in
     << ", .rules_out=" << reason.rules_out << " }\n";
  return os;
}

inline auto& operator<<(std::ostream& os, RuleSet const& ruleset)
{
  os << "{ .name=\"" << ruleset.name << "\", .rules=" << ruleset.rules << " }\n";
  return os;
}

inline auto& operator<<(std::ostream& os, Deinflection const& deinflection)
{
  os << "{.term=" << deinflection.term //
     << ", .rules=" << deinflection.rules //
     << ", .reasons=" << deinflection.reasons //
     << "}";
  return os;
}

inline auto& operator<<(std::ostream& os, std::vector<Deinflection> const& deinflections)
{
  for (auto const& deinflection: deinflections) {
    os << deinflection << '\n';
  }
  os << '\n';
  return os;
}
