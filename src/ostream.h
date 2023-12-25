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
