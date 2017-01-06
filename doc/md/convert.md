```c++
unicons::convert
```

### Header

```c++
#include <unicode_traits.hpp>
```

### Synopsis
```c++
template <class InputIt,class OutputIt>
std::pair<uni_errc,InputIt> convert(InputIt first, InputIt last, OutputIt target, 
                                    conv_flags flags = conv_flags::strict) 
```
Converts the characters in the range, defined by [first, last), to another range beginning at d_first.

Parameter|Description
------------------------------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters to convert. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 
target     | [Output iterator](http://en.cppreference.com/w/cpp/concept/OutputIterator) to the beginning of the target range. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 
flags       | Manages whether validation is `strict` or `lenient`.

### Return value

An [std::pair](http://en.cppreference.com/w/cpp/utility/pair) that contains a [uni_errc](uni_errc) error code and an iterator that points to the location in the range [first,last] where validation stopped. The target is useable if the iterator points to `last`, which will always be the case if the error code is `uni_errc::ok`. If the error code is not `uni_errc::ok`, but the iterator points to `last`, some of the characters in the target will have been replaced with the replacement character `0x0000FFFD`.  

