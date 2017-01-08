#include "unicode_traits.hpp"
#include <iostream>

void validate_utf8()
{
    std::string source = "\xE6\x97\xA5\xD1\x88\xFA";
    auto result = unicons::validate(source.begin(),source.end());

    if (result.first != unicons::uni_errc::ok)
    {
        std::cout << make_error_code(result.first).message() << std::endl;
    }
}

void validate_utf16()
{
    std::u16string source = u"\xD888\x1234";
    auto result = unicons::validate(source.begin(),source.end());

    if (result.first != unicons::uni_errc::ok)
    {
        std::cout << make_error_code(result.first).message() << std::endl;
    }
}

void append_codepoint_to_string()
{
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
}

int main()
{
    validate_utf8();
    validate_utf16();
    append_codepoint_to_string();
}
