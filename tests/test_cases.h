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

#include "ostream.h"
#include "types.h"
#include <ostream>
#include <string>
#include <vector>

struct TestCase
{
  std::string term{};
  std::string source{};
  RuleType rule{};
  std::vector<std::string> reasons{};
};

inline auto& operator<<(std::ostream& os, TestCase const& test_case)
{
  os << "{.term=" << test_case.term //
     << ", .source=" << test_case.source //
     << ", .rule=" << test_case.rule //
     << ", .reasons=" << test_case.reasons //
     << "}";
  return os;
}

struct TestGroup
{
  bool valid{};
  std::vector<TestCase> tests{};
};

std::vector<TestGroup> test_groups();
