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
detect_encoding_result<InputIt> detect_encoding(InputIt first, InputIt last) noexcept;

template <class Iterator>
struct detect_encoding_result
{
    Iterator pos;
    encoding ec;
};
```

Attempts to detect the character encoding from the first four bytes of the text.

Parameter   |Description
------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of bytes. The byte type may be any integral type, signed or unsigned, with size in bits of 8. 

### Return value

Returns a value of type `detect_encoding_result` with `pos` pointing to one past the bom if present, otherwise to `first`, and a [code](encoding) that indicates the encoding.

