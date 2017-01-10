// Copyright 2016 Daniel Parker
// Distributed under Boost license

#include <catch.hpp>
#include <unicode_traits.hpp>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <type_traits>

using namespace unicons;

TEST_CASE("sequence_at") 
{
    SECTION("utf-8") 
    {
        std::string source = "Hi \xf0\x9f\x99\x82"; // U+1F642

        auto seq3 = sequence_at(source.begin(),source.end(),3);
        REQUIRE(seq3.second == 4);
    }
    SECTION("utf-16") 
    {
        std::u16string source = u"Hi \xD83D\xDE42"; // U+1F642

        auto seq3 = sequence_at(source.begin(),source.end(),3);
        REQUIRE(seq3.second == 2);
    }
    SECTION("utf-32") 
    {
        std::u32string source = U"Hi \x1F642"; // U+1F642

        auto seq3 = sequence_at(source.begin(),source.end(),3);
        REQUIRE(seq3.second == 1);
    }
}

