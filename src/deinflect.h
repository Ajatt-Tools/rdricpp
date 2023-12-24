#pragma once

#include "types.h"
#include <string_view>
#include <vector>

auto deinflect(std::string_view const source) -> std::vector<Deinflection>;
