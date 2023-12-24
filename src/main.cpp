#include "deinflect.h"
#include "ostream.h"
#include <iostream>

int main(int const argc, char const* const* const argv)
{
  for (int idx = 1; idx < argc; ++idx) {
    std::cout << deinflect(*std::next(argv, idx));
  }
  return 0;
}
