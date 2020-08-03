// Copyright 2016 Daniel Parker
// Distributed under Boost license

#include <catch/catch.hpp>
#include <unicode_traits.hpp>
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <iterator>
#include <type_traits>
 
using namespace unicons;

TEST_CASE("u32_length") 
{
    SECTION("UTF-8")
    {
        std::string source = "Hello world \xf0\x9f\x99\x82"; // U+1F642
        size_t len = u32_length(source.begin(),source.end());
        CHECK(len == 13);
    }
    SECTION("UTF-16")
    {
        std::u16string source = u"Hello world \xD83D\xDE42"; // U+1F642
        size_t len = u32_length(source.begin(), source.end());
        CHECK(len == 13);
    }
    SECTION("UTF-32")
    {
        std::u32string source = U"Hello world \x1F642"; // U+1F642
        size_t len = u32_length(source.begin(), source.end());
        CHECK(len == 13);
    }
}
