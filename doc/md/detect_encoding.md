```c++
unicons::detect_encoding
```

### Header

```c++
#include <unicode_traits.hpp>
```

### Synopsis
```c++
template <class InputIt>
std::pair<encoding,InputIt> detect_encoding(InputIt first, InputIt last) noexcept
```

Attempts to detect the character encoding from the first four bytes of the text.

Parameter   |Description
------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of bytes. The byte type may be any integral type, signed or unsigned, with size in bits of 8. 

### Return value

A [std::pair](http://en.cppreference.com/w/cpp/utility/pair) that contains first, a [code](encoding) that indicates the encoding, and second, an iterator that points to one past the bom if present, otherwise to `first`.
