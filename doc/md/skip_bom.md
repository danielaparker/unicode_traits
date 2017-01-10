```c++
unicons::skip_bom
```

### Header

```c++
#include <unicode_traits.hpp>
```

### Synopsis
```c++
template <class InputIt>
std::pair<encoding_errc,InputIt> skip_bom(InputIt first, InputIt last) 
```

Attempts to validate that the encoding type matches the character width, and skips past a bom if present in the range defined by [first, last). 

Parameter   |Description
------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters to validate. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 

### Return value

An [std::pair](http://en.cppreference.com/w/cpp/utility/pair) that contains, first, a [encoding_errc](encoding_errc) error code and, second, an iterator that points to one past the bom if present, otherwise to `first`.
