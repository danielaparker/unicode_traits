# unicode_traits for C++

The C++ unicode_traits class template makes using unicode easier. 

All you need to do is download one header file, [unicode_traits.hpp](https://raw.githubusercontent.com/danielaparker/unicode_traits/master/src/unicode_traits.hpp), and drop it somewhere in your include path.

## Examples

### Convert UTF8 to UTF16
```c++
std::string source = "Hello world \xf0\x9f\x99\x82"; // 

std::u16string target;
auto result = convert(source.begin(),source.end(),
                      std::back_insert_iterator<std::u16string>(target), 
                      conv_flags::strict);
```
&#128578;

## Resources

- [The Unicode Consortium](http://unicode.org/)
- [UTF-8 encoding table and Unicode characters](http://www.utf8-chartable.de/unicode-utf8-table.pl)
- [Unicode code converter](https://r12a.github.io/apps/conversion/)






