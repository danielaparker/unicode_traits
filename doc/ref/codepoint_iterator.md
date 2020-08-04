```c++
template <class Iter>
unicons::codepoint_iterator
```
A `codepoint_iterator` generates unicode character sequences.

### Header
```c++
#include <unicode_traits.hpp>
```

### Member types

Member type         |Definition
--------------------|------------------------------
`iterator_type`     | Iter
`value_type`        | uint32_t;
`difference_type    | std::ptrdiff_t;
`pointer`           | value_type*;
`reference`         | const value_type&;
`iterator_category` | std::input_iterator_tag;


### Constructors

    codepoint_iterator() noexcept;                             (1)

    codepoint_iterator(Iter first, Iter last, 
                       conv_flags flags = conv_flags::strict); (2)

    codepoint_iterator(Iter first, Iter last, 
                       std::error_code& ec) noexcept;          (3)

    codepoint_iterator(Iter first, Iter last, 
                       conv_flags flags, 
                       std::error_code& ec) noexcept;          (4)

    codepoint_iterator( const codepoint_iterator& ) = default; (5)

    codepoint_iterator( codepoint_iterator&& ) = default;      (6)

Constructs a `codepoint_iterator` over the characters [first,last). 
The user's intention for source encoding scheme is deduced from the 
character width, UTF-8 from 8 bit characters, UTF-16 from 16 bit 
characters, and UTF-32 from 32 bit characters. 
The character type may be any integral type, signed or unsigned, 
with size in bits of 8, 16 or 32.

1) Constructs the end iterator.

#### Exceptions

2-6) The overload that does not take a `std::error_code&` parameter throws 
[unicode_error](unicode_error.md) with a [conv_errc](conv_errc.md) error code. 
The overload taking a std::error_code& parameter sets it to a [conv_errc](conv_errc.md) error code 
if a unicode error.

### Member functions

    codepoint_iterator& operator=(const codepoint_iterator&) = default;

    codepoint_iterator& operator=(codepoint_iterator&&) = default;

    const codepoint_iterator& operator*() const noexcept;
Accesses the current codepoint

    codepoint_iterator& operator++();
    codepoint_iterator& increment(std::error_code& ec) noexcept;
Moves to the next codepoint.

   constexpr iterator_type base() const noexcept;
Returns the underlying base iterator.

## Examples

### Reading UTF-16 codepoints (non-throwing)

```c++
std::u16string source = u"Hi \xD83D\xDE42"; // U+1F642

std::error_code ec;
auto it = make_codepoint_iterator(source.begin(),source.end(),ec);
auto last = end(it);

while (!ec && it != end)
{
    uint32_t cp = *it;
    it.increment(ec);    
}
```

H   
i   

&#128578;

### Reading UTF-8 codepoints (potentially throwing)

```c++
std::string source = "Hi \xf0\x9f\x99\x82"; // U+1F642

try
{
    auto it = make_codepoint_iterator(source.begin(),source.end());
    for (uint32_t cp : it)
    {
    }
}
catch (const unicons::unicode_error& e)
{
   std::cerr << e.what() << "\n"; 
}
```

H   
i   

&#128578;


