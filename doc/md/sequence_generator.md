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
`sequence_type`|A [std::pair](http://en.cppreference.com/w/cpp/utility/pair) that contains first, an iterator pointing to the first character of the sequence, and second, the length of the sequence. 

### Constructors

    sequence_generator(Iterator first, Iterator last, 
                       conv_flags flags = conv_flags::strict)
Constructs a `sequence_generator` over the characters [first,last).

### Member functions

    bool done() const
Returns `true` when there are no more sequences to be read from [first,last), `false` otherwise

    uni_errc status() const
Returns the status of the generator

    std::pair<Iterator,size_t> get() const 
Returns a [std::pair](http://en.cppreference.com/w/cpp/utility/pair) that contains first, an iterator pointing to the first character of the sequence, and second, the length of the sequence. 

    uint32_t get_codepoint() const
Returns the codepoint corresponding to the sequence

    void next()
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
    uint32_t cp = g.get_codepoint();    
}
```

H
i

&#128578;

