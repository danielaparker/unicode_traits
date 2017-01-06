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
first, last | the range of characters to validate.
flags       | manages whether validation is `strict` or `lenient`.

