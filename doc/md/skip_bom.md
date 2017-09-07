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
skip_bom_result<InputIt> skip_bom(InputIt first, InputIt last) noexcept;

template <class Iterator>
struct skip_bom_result
{
    Iterator it;
    encoding_errc ec;
};

```

Attempts to validate that the encoding type matches the character width, and skips past a bom if present in the range defined by [first, last). 

Parameter   |Description
------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters to validate. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 

### Return value

On success, returns a value of type `skip_bom_result` with `it` pointing to the bom if present, otherwise to `first`, and a value initialized [encoding_errc](encoding_errc).

On error, returns a value of type `skip_bom_result` with `it` pointing to the location in the range [first,last] where validation stopped, and a [encoding_errc](encoding_errc) error code. 

