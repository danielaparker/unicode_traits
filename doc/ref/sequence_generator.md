```c++
template <class Iterator>
unicons::sequence_generator
```
A `sequence_generator` generates unicode character sequences.

### Header
```c++
#include <unicode_traits.hpp>
```

### Member types

Member type                         |Definition
------------------------------------|------------------------------
`sequence_type`|typedef sequence<Iterator> sequence_type

### Constructors

    sequence_generator(Iterator first, Iterator last, 
                       conv_flags flags = conv_flags::strict) noexcept
Constructs a `sequence_generator` over the characters [first,last). The user's intention for source encoding scheme is deduced from the character width, UTF-8 from 8 bit characters, UTF-16 from 16 bit characters, and UTF-32 from 32 bit characters. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32.

### Member functions

    bool done() const noexcept
Returns `true` when there are no more sequences to be read from [first,last), `false` otherwise

    conv_errc status() const noexcept
Returns the status of the generator

    sequence_type get() const noexcept
Returns a [sequence](sequence) representing one codepoint.

    void next() noexcept
Moves to the next sequence

## Examples

### Reading UTF-16 sequences

```c++
std::u16string source = u"Hi \xD83D\xDE42"; // U+1F642

sequence_generator<std::u16string::iterator> g(source.begin(),
                                               source.end());

while (!g.done())
{
    auto sequence = g.get();
    uint32_t cp = sequence.codepoint();    
}
```

H   
i   

&#128578;

### See also

[sequence](sequence)

[make_sequence_generator](make_sequence_generator)

