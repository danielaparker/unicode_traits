```c++
unicons::conv_errc
```
### Header

```c++
#include <unicode_traits.hpp>
```
Constant                   |Description
---------------------------|------------------------------
ok                         | conversion successful
over_long_utf8_sequence    | over long utf8 sequence
expected_continuation_byte | expected continuation byte    
unpaired_high_surrogate    | unpaired high surrogate UTF-16
illegal_surrogate_value    | UTF-16 surrogate values are illegal in UTF-32
source_exhausted           | partial character in source, but hit end
source_illegal             | source sequence is illegal/malformed


