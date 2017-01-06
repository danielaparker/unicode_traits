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
std::pair<uni_errc,InputIt> validate(InputIt first, InputIt last, 
                                     conv_flags flags = conv_flags::strict) 
```
Validates the characters in the range, defined by [first, last).

Parameter|Description
------------------------------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters to convert. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 
flags       | Manages whether validation is `strict` or `lenient`.

### Return value

An [std::pair](http://en.cppreference.com/w/cpp/utility/pair) that contains a [uni_errc](uni_errc) error code and an iterator that points to the location in the range [first,last] where validation stopped. 
