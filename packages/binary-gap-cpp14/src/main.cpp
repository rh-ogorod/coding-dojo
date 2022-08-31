// Hey Emacs, this is -*- coding: utf-8 -*-

#include "main.hpp"

#include <bitset>
#include <climits>
#include <iostream>

template <typename T>
class BinaryForm {
 public:
  explicit BinaryForm(const T& v) : _bs(v) {}

 private:
  const std::bitset<sizeof(T) * CHAR_BIT> _bs;

  template <typename U>
  friend auto operator<<(std::ostream& os, const BinaryForm<U>& bf)
      -> std::ostream&;
};

template <typename T>
inline auto operator<<(std::ostream& os, const BinaryForm<T>& bf)
    -> std::ostream& {
  return os << bf._bs;
}

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << "Binary gap samples:\n"
            << BinaryForm{10} << " -> " << solution(10) << "\n"
            << BinaryForm{0b100'0000'0000'0000'0000'0000'0000'1010} << " -> "
            << solution(0b100'0000'0000'0000'0000'0000'0000'1010) << "\n";

  return 0;
}
