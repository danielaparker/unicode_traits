// Copyright 2016 Daniel Parker
// Distributed under Boost license

#include <catch/catch.hpp>
#include <unicode_traits.hpp>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <type_traits>

using namespace unicons;

TEST_CASE("codepoint_iterator tests") 
{
    SECTION("utf-8") 
    {
        std::string source = "Hi \xf0\x9f\x99\x82"; // U+1F642

        std::error_code ec;
        codepoint_iterator<std::string::iterator> it(source.begin(),source.end(),ec);

        auto first = begin(it);
        auto last = end(it);

        while (it != last)
        {
            std::cout << *it << "\n";
            it.increment(ec);
        }
    }
    SECTION("utf-16") 
    {
        std::u16string source = u"Hi \xD83D\xDE42"; // U+1F642

        std::error_code ec;
        codepoint_iterator<std::u16string::iterator> it(source.begin(),source.end(),ec);

        auto first = begin(it);
        auto last = end(it);
    }
    SECTION("utf-32") 
    {
        std::u32string source = U"Hi \x1F642"; // U+1F642

        std::error_code ec;
        codepoint_iterator<std::u32string::iterator> it(source.begin(),source.end(),ec);

        auto first = begin(it);
        auto last = end(it);
    }
}

