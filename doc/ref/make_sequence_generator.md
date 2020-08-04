```c++
unicons::make_sequence_generator
```

### Header

```c++
#include <unicode_traits.hpp>
```

### Synopsis
```c++
template <class Iterator>
sequence_generator<Iterator> make_sequence_generator(Iterator first, Iterator last) 
```

`make_sequence_generator` is a convenience function template that constructs a [sequence_generator](sequence_generator) for the iterators `first` and `last` with the type deduced from the type of the argument.

Parameter   |Description
------------|------------------------------
first, last | [Input iterators](http://en.cppreference.com/w/cpp/concept/InputIterator) that demarcate the range of characters over which to generate sequences. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32. 

### Return value

A [sequence_generator](sequence_generator) that can be used to generate character sequences and corresponding codepoints.

## Examples

### Reading UTF-8 sequences

```c++
std::string source = "Hi \xf0\x9f\x99\x82"; // U+1F642

auto g = make_sequence_generator(source.begin(),source.end());

while (!g.done())
{
    auto sequence = g.get();
    uint32_t cp = g.get_codepoint();    
}
```

H   
i   

&#128578;

