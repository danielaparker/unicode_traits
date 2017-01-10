```c++
unicons::sequence_at
```

### Header

```c++
#include <unicode_traits.hpp>
```

### Synopsis
```c++
template <class InputIt>
std::pair<InputIt,size_t> sequence_at(InputIt first, InputIt last, size_t i) 
```

Returns the ith character sequence in the range `[first, last)`.

Parameter   |Description
------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 

The user's intention for source encoding scheme is deduced from the character width, UTF-8 from 8 bit characters, UTF-16 from 16 bit characters, and UTF-32 from 32 bit characters. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32.

### Return value

A [std::pair](http://en.cppreference.com/w/cpp/utility/pair) that contains first, an iterator pointing to the start of the sequence, and second, the number of characters in the sequence.
