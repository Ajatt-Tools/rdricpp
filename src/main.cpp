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

#include "ostream.h"
#include "rdricpp.h"
#include <iostream>
#include <ranges>

int main(int const argc, char const* const* const argv)
{
  for (auto const idx: std::views::iota(1, argc)) {
    std::cout << ajt::rdricpp::deinflect(*std::next(argv, idx));
  }
  return 0;
}
