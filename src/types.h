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

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace ajt::rdricpp {

enum RuleType : uint32_t {
  none = 0U,
  v1 = 1U, // Verb ichidan
  v5 = 2U, // Verb godan
  vs = 4U, // Verb suru
  vk = 8U, // Verb  kuru
  vz = 16U, // Verb zuru
  adj_i = 32U, // Adjective i
  iru = 64U // Intermediate -iru endings for progressive or  perfect tense
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

struct Deinflection
{
  std::string term{};
  RuleType rules{};
  std::vector<std::string> reasons{};
};

} // namespace ajt::rdricpp
