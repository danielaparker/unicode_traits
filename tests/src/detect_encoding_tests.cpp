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

TEST_CASE("detect bom utf-8") 
{
    SECTION("")
    {
        std::string input = "\xEF\xBB\xBF[1,2,3]";
        auto result = unicons::detect_encoding(input.begin(),input.end());
        REQUIRE(result.ec == encoding::u8);
        CHECK(result.pos == (input.begin()+3));
    }

    SECTION("")
    {
        std::string input = "\xEF\xBB\xBF[1,2,3]";
        auto result = unicons::skip_bom(input.begin(),input.end());
        REQUIRE(result.ec == encoding_errc());
        CHECK(result.pos == (input.begin()+3));
    }

    SECTION("")
    {
        std::string input = "";
        auto result = unicons::skip_bom(input.begin(),input.end());
        REQUIRE(result.ec == encoding_errc());
        CHECK(result.pos == input.begin());
    }
    
    SECTION("")
    {
        std::string input = "\xEF\xBB\xBF";
        auto result = unicons::skip_bom(input.begin(),input.end());
        REQUIRE(result.ec == encoding_errc());
        CHECK(result.pos == (input.begin()+3));
    }
}

TEST_CASE("detect bom utf-16") 
{
    std::u16string input = u"\xFEFF[1,2,3]";

    SECTION("")
    {
        auto result = unicons::skip_bom(input.begin(),input.end());
        REQUIRE(result.ec == unicons::encoding_errc());
        CHECK(result.pos == (input.begin()+1));
    }
}

TEST_CASE("detect bom utf-32") 
{
    std::u32string input = U"\xFEFF0000[1,2,3]";

    SECTION("")
    {
        auto result = unicons::skip_bom(input.begin(),input.end());
        REQUIRE(result.ec == unicons::encoding_errc());
        CHECK(result.pos == (input.begin()+1));
    }
}


