// Copyright 2016 Daniel Parker
// Distributed under Boost license

#include <catch.hpp>
#include <unicode_traits.hpp>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <type_traits>

using namespace unicons;

TEST_CASE("validate utf8") 
{
    SECTION("invalid sequence") 
    {
        std::string source = "\xE6\x97\xA5\xD1\x88\xFA";
        auto result = validate(source.begin(),source.end());
        REQUIRE(result.ec != conv_errc());
        CHECK(result.ec == conv_errc::source_exhausted);
    }
}

TEST_CASE("validate utf16") 
{
    SECTION("high_surrogate") 
    {
        std::u16string source = u"\xD800";
        auto result = validate(source.begin(),source.end());
        REQUIRE(result.ec != conv_errc());
        CHECK(result.ec == conv_errc::source_exhausted);
    }
    SECTION("1st surrogate but 2nd missing") 
    {
        std::u16string source = u"\xDADA";
        auto result = validate(source.begin(),source.end());
        REQUIRE(result.ec != conv_errc());
        CHECK(result.ec == conv_errc::source_exhausted);
    }
    SECTION("1st valid surrogate but 2nd invalid") 
    {
        std::u16string source = u"\xD888\x1234";
        auto result = validate(source.begin(),source.end());
        REQUIRE(result.ec != conv_errc());
        CHECK(result.ec == conv_errc::unpaired_high_surrogate);
    }
    SECTION("high surrogate then \x01") 
    {
        std::u16string source = u"\xD800\x01";
        auto result = validate(source.begin(),source.end());
        REQUIRE(result.ec != conv_errc());
        CHECK(result.ec == conv_errc::unpaired_high_surrogate);
    }
    SECTION("hhigh_surrogate_then_1x") 
    {
        std::u16string source = u"\xD800\x1x";
        auto result = validate(source.begin(),source.end());
        REQUIRE(result.ec != conv_errc());
        CHECK(result.ec == conv_errc::unpaired_high_surrogate);
    }
}

