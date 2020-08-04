```c++
unicons::is_surrogate
```

### Header

```c++
#include <unicode_traits.hpp>
```

### Synopsis
```c++
template <class InputIt>
bool is_surrogate(InputIt first, InputIt last) noexcept
```

Checks if the character is a UTF-16 surrogate value in the range 0xDC00 to 0xDFFF inclusive.

Parameter   |Description
------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 

The source encoding scheme is assumed to be one-to-one with the character width, UTF-8 with 8 bit characters, UTF-16 with 16 bit characters, and UTF-32 with 32 bit characters. If the source contains characters that are illegal in that encoding scheme, an error code will be returned.

### Return value

`true` if the character is a UTF-16 surrogate value, false otherwise.
