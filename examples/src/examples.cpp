#include "unicode_traits.hpp"
#include <iostream>

void validate_utf8()
{
    std::string source = "\xE6\x97\xA5\xD1\x88\xFA";
    auto result = unicons::validate(source.begin(),source.end());

    if (result.ec)
    {
        std::cout << make_error_code(result.ec).message() << std::endl;
    }
}

void validate_utf16()
{
    std::u16string source = u"\xD888\x1234";
    auto result = unicons::validate(source.begin(),source.end());

    if (result.ec)
    {
        std::cout << make_error_code(result.ec).message() << std::endl;
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

void access_codepoints()
{
    std::u16string source = u"Hi \xD83D\xDE42"; // U+1F642

    std::error_code ec;
    auto it = make_codepoint_iterator(source.begin(),source.end(),ec);
    auto last = end(it);

    while (!ec && it != end)
    {
        uint32_t cp = *it;
        it.increment(ec);    
    }
}

void access_nth_codepoint()
{
    std::u16string source = u"Hi \xD83D\xDE42"; // U+1F642

    std::error_code ec;
    auto it = make_codepoint_iterator(source.begin(),source.end(),ec);

    unicons::advance(it, 3, ec);

    if (!ec)
    {
        std::cout << *it << "\n";
    }
}

int main()
{
    validate_utf8();
    validate_utf16();
    append_codepoint_to_string();
    access_codepoints();
    access_nth_codepoint();
}
