#include "unicode_traits.hpp"
#include <iostream>

using namespace unicons;

void validate_example1()
{
    std::string source = "\xE6\x97\xA5\xD1\x88\xFA";
    auto result = unicons::validate(source.begin(),source.end(),conv_flags::strict);

    if (result.first != unicons::uni_errc::ok)
    {
        std::cout << make_error_code(result.first).message() << std::endl;
    }
}

void validate_example2()
{
    std::u16string source = u"\xD888\x1234";
    auto result = validate(source.begin(),source.end(),conv_flags::strict);

    if (result.first != unicons::uni_errc::ok)
    {
        std::cout << make_error_code(result.first).message() << std::endl;
    }
}

int main()
{
    validate_example1();
    validate_example2();
}
