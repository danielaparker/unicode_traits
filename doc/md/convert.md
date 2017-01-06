```c++
unicons::convert
```

### Header
```c++
#include <unicode_traits.hpp>

template <class InputIt,class OutputIt>
std::pair<uni_errc,InputIt> convert(InputIt first, InputIt last, OutputIt d_first, 
                                    conv_flags flags = conv_flags::strict) 
```
Converts the characters in the range, defined by [first, last), to another range beginning at d_first.

### Parameters

------------------------------------|------------------------------
```first, last``` | - the range of characters to copy


