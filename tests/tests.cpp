#include "deinflect.h"
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
