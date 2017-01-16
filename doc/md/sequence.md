```c++
template <class Iterator>
unicons::sequence
```
A `sequence` represents a unicode character sequence.

### Header
```c++
#include <unicode_traits.hpp>
```

### Member types

### Constructors

    sequence(Iterator first, size_t length) noexcept
Constructs a `sequence` of `length` characters representing a single codepoint.

### Member functions

    Iterator begin() const noexcept
Returns an iterator pointing to the first character of the sequence

    size_t length() const noexcept
Returns the length of the sequence.

    uint32_t codepoint() const noexcept
Returns the codepoint corresponding to the sequence, or the replacement character `0x0000FFFD` if the sequence is malformed.

- [sequence_generator](sequence_generator)
- [sequence_at](sequence_at)

