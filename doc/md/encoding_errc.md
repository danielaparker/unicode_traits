```c++
unicons::encoding_errc
```
### Header

```c++
#include <unicode_traits.hpp>

```
Constant                   |Description
---------------------------|------------------------------
ok                         | Success
expected_u8_found_u16      | Expected UTF-8, found UTF-16
expected_u8_found_u32      | Expected UTF-8, found UTF-32    
expected_u16_found_fffe    | Expected UTF-16, found non character
expected_u32_found_fffe    | Expected UTF-32, found non character


