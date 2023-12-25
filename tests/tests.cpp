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
#include "test_cases.h"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <ranges>

bool is_result_included(std::vector<Deinflection> const& results, TestCase const& test_case)
{
  return std::ranges::any_of(std::views::all(results), [&test_case](Deinflection const& result) {
    return (
      result.term == test_case.term
      and (result.rules == RuleType::none or (test_case.rule & result.rules) == test_case.rule)
      and test_case.reasons == result.reasons
    );
  });
}

TEST_CASE("Deinflect", "[deinflect]")
{
  for (TestGroup const& group: test_groups()) {
    for (TestCase const& test_case: group.tests) {
      REQUIRE(group.valid == is_result_included(deinflect(test_case.source), test_case));
    }
  }
}
