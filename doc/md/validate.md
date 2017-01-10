```c++
unicons::validate
```

### Header

```c++
#include <unicode_traits.hpp>
```

### Synopsis
```c++
template <class InputIt>
std::pair<conv_errc,InputIt> validate(InputIt first, InputIt last) noexcept
```

Validates the characters in the range, defined by [first, last).

Parameter   |Description
------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters to validate. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 

The user's intentions for source encoding schemes are deduced from the character width, UTF-8 from 8 bit characters, UTF-16 from 16 bit characters, and UTF-32 from 32 bit characters. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32.

### Return value

An [std::pair](http://en.cppreference.com/w/cpp/utility/pair) that contains, first, a [conv_errc](conv_errc) error code and, second, an iterator that points to the location in the range [first,last] where validation stopped. If the error code is not `conv_errc::ok`, the iterator points to the first character of the sequence that is illegal.
