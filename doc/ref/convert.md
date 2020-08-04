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
convert_result<InputIt> convert(InputIt first, InputIt last, OutputIt target, 
                                conv_flags flags = conv_flags::strict) 

template <class Iterator>
struct convert_result
{
    Iterator pos;
    conv_errc ec;
};

```
Converts the characters in the range, defined by [first, last), to another range beginning at `target`.

Parameter|Description
------------------------------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters to convert. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 
target     | [Output iterator](http://en.cppreference.com/w/cpp/concept/OutputIterator) to the beginning of the target range. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 
flags       | Manages whether validation is `strict` or `lenient`.

The user's intentions for source and target encoding schemes are deduced from the character width, UTF-8 from 8 bit characters, UTF-16 from 16 bit characters, and UTF-32 from 32 bit characters. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32.

### Return value

On success, returns a value of type `convert_result` with `pos` pointing to `last` in the range [first,last], and a value initialized [conv_errc](conv_errc).

On error, returns a value of type `convert_result` with `pos` pointing to the location in the range [first,last] where validation stopped, and a [conv_errc](conv_errc) error code. The target is useable if the iterator points to `last`, which will always be the case if the error code is `conv_errc()`. If the error code is not `conv_errc()`, but the iterator points to `last`, the illegal parts of the source sequence will have been replaced with the replacement character `0x0000FFFD`.  

### Exceptions

`convert` itself does not throw. If writing to the output iterator results in failure to allocate memory, however, expect that `std::bad_alloc` will be thrown.
