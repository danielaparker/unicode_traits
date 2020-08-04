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
convert_result<InputIt> validate(InputIt first, InputIt last) noexcept

template <class Iterator>
struct convert_result
{
    Iterator pos;
    conv_errc ec;
};
```

Validates the characters in the range, defined by [first, last).

Parameter   |Description
------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters to validate. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 

The user's intention for source encoding scheme is deduced from the character width, UTF-8 from 8 bit characters, UTF-16 from 16 bit characters, and UTF-32 from 32 bit characters. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32.

### Return value

On success, returns a value of type `convert_result` with `pos` pointing to `last` in the range [first,last] where validation stopped, and a value initialized [conv_errc](conv_errc).

On error, returns a value of type `convert_result` with `pos` pointing to the location in the range [first,last] where validation stopped. If the error code is not `conv_errc()`, the iterator points to the first character of the sequence that is illegal.  

