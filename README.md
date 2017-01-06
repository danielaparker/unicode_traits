# unicode_traits for C++

The C++ unicode_traits class template makes using unicode easier. 

All you need to do is download one header file, [unicode_traits.hpp](https://raw.githubusercontent.com/danielaparker/unicode_traits/master/src/unicode_traits.hpp), and drop it somewhere in your include path.

## Examples

### Convert UTF8 to UTF16 and UTF32

```c++
#include "unicode_traits.hpp"
#include <vector>
#include <string>
#include <iterator>

int main()
{
    std::string source = "Hello world \xf0\x9f\x99\x82";  

    // Convert source to UTF16
    std::u16string u16target;
    auto result = unicons::convert(source.begin(),source.end(),
                                   std::back_inserter(u16target), 
                                   unicons::conv_flags::strict);

    // Convert source to UTF32
    std::vector<uint32_t> u32target;
    auto result = unicons::convert(source.begin(),source.end(),
                                   std::back_inserter(u32target), 
                                   unicons::conv_flags::strict);

    // Convert source to UTF16 (16 bit wchar_t) or UTF32 (32 bit wchar_t)
    wstring wtarget;
    auto result = unicons::convert(source.begin(),source.end(),
                                   std::back_inserter(wtarget), 
                                   unicons::conv_flags::strict);
}
```
Hello World &#128578;

## Resources

- [The Unicode Consortium](http://unicode.org/)
- [UTF-8 encoding table and Unicode characters](http://www.utf8-chartable.de/unicode-utf8-table.pl)
- [Unicode code converter](https://r12a.github.io/apps/conversion/)






