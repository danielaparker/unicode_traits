# unicode_traits for C++

The C++ unicode_traits class template makes using unicode easier. 

All you need to do is download one header file, [unicode_traits.hpp](https://raw.githubusercontent.com/danielaparker/unicode_traits/master/src/unicode_traits.hpp), and drop it somewhere in your include path.

Consult the [unicode_traits reference](https://github.com/danielaparker/unicode_traits/wiki) for details.

It should work with with MS VC++ 2013, MS VC++ 2015, GCC 4.8, GCC 4.9, GCC 6.2.0 and recent versions of clang.

## Examples

In the examples below, source and target encoding schemes are deduced from the character width, UTF-8 from 8 bit characters, UTF-16 from 16 bit characters, and UTF-32 from 32 bit characters. The character type may be any integral type, signed or unsigned, with size in bits of 8, 16 or 32.

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
    std::u16string target1;
    auto result1 = unicons::convert(source.begin(),source.end(),
                                    std::back_inserter(target1), 
                                    unicons::conv_flags::strict);

    // Convert source to UTF32
    std::vector<uint32_t> target2;
    auto result2 = unicons::convert(source.begin(),source.end(),
                                    std::back_inserter(target2), 
                                    unicons::conv_flags::strict);

    // Convert source to UTF16 (if 16 bit wchar_t) or UTF32 (if 32 bit wchar_t)
    wstring target3;
    auto result3 = unicons::convert(source.begin(),source.end(),
                                    std::back_inserter(target3), 
                                    unicons::conv_flags::strict);
}
```
Hello World &#128578;

### Append codepoint to string
```c++
uint32_t cp = 0x1f642;

std::string target1 = "Hello world ";
std::u16string target2 = u"Hello world ";
std::u32string target3 = U"Hello world ";
std::wstring target4 = L"Hello world ";

auto result1 = unicons::convert(&cp,&cp + 1,std::back_inserter(target1), 
                                unicons::conv_flags::strict);
auto result2 = unicons::convert(&cp,&cp + 1,std::back_inserter(target2), 
                                unicons::conv_flags::strict);
auto result3 = unicons::convert(&cp,&cp + 1,std::back_inserter(target3), 
                                unicons::conv_flags::strict);
auto result4 = unicons::convert(&cp,&cp + 1,std::back_inserter(target4), 
                                unicons::conv_flags::strict);
```
Hello World &#128578;

### Generate sequences

```c++
std::string source = "Hi \xf0\x9f\x99\x82"; // U+1F642

auto g = unicons::make_sequence_generator(source.begin(),source.end());
while (!g.done())
{
    auto sequence = g.get();
    uint32_t codepoint = g.get_codepoint();
    g.next();
}
```

H   
i   

&#128578;

### Validate UTF-8 sequence

```c++
std::string source = "\xE6\x97\xA5\xD1\x88\xFA";
auto result = unicons::validate(source.begin(),source.end());

if (result.first != unicons::conv_errc::ok)
{
    std::cout << make_error_code(result.first).message() << std::endl;
}
```
Output:
```
Partial character in source, but hit end
```

### Validate UTF-16 sequence
```c++
std::u16string source = u"\xD888\x1234";
auto result = unicons::validate(source.begin(),source.end());

if (result.first != unicons::conv_errc::ok)
{
    std::cout << make_error_code(result.first).message() << std::endl;
}
```
Output:
```
Unpaired high surrogate UTF-16
```

## Resources

- [The Unicode Consortium](http://unicode.org/)
- [UTF-8 encoding table and Unicode characters](http://www.utf8-chartable.de/unicode-utf8-table.pl)
- [Unicode code converter](https://r12a.github.io/apps/conversion/)






