#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <string_view>

enum RuleType : uint32_t {
  none = 0U,
  v1 = 1U, // Verb ichidan
  v5 = 1U << 1U, // Verb godan
  vs = 1U << 2U, // Verb suru
  vk = 1U << 3U, // Verb  kuru
  vz = 1U << 4U, // Verb zuru
  adj_i = 1U << 5U, // Adjective i
  iru = 1U << 6U // Intermediate -iru endings for progressive or  perfect tense
};

struct Reason
{
  std::string_view kana_in{};
  std::string_view kana_out{};
  RuleType rules_in{};
  RuleType rules_out{};

  [[nodiscard]] bool empty() const noexcept
  {
    return rules_in == RuleType::none and rules_out == RuleType::none and kana_in.empty() and kana_out.empty();
  }
};

static constexpr size_t arr_max_size{ 50 };

struct RuleSet
{
  std::string_view name{};
  std::array<Reason, arr_max_size> rules{};
};
