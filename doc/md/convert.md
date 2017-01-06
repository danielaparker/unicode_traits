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
first, last | the range of characters to copy.
target     | the beginning of the destination range.
flags       | manages whether validation is `strict` or `lenient`.

