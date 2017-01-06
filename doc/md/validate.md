```c++
unicons::validate
```

### Header
```c++
#include <unicode_traits.hpp>
```

```
template <class InputIt>
std::pair<uni_errc,InputIt> validate(InputIt first, InputIt last, 
                                     conv_flags = conv_flags::strict) 
```

Validates the characters in the range, defined by [first, last).


