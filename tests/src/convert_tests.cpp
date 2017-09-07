// Copyright 2016 Daniel Parker
// Distributed under Boost license

#include <catch.hpp>
#include <unicode_traits.hpp>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <type_traits>

using namespace unicons;

TEST_CASE("utf8") 
{
    std::string source = "Hello world \xf0\x9f\x99\x82"; // U+1F642

    SECTION("append to utf8 string")
    {
        std::string target;
        auto result = convert(source.begin(),source.end(),std::back_inserter(target), 
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(source == target);
    }

    SECTION("append to utf16 string")
    {
        std::u16string target;
        auto result = convert(source.begin(),source.end(),
                              std::back_inserter(target), 
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(u"Hello world \xD83D\xDE42" == target);
    }

    SECTION("append to utf32 string")
    {
        std::u32string target;
        auto result = convert(source.begin(),source.end(),
                              std::back_inserter(target),
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(U"Hello world \x1F642" == target);
    }
}

TEST_CASE( "utf16") 
{
    std::u16string source = u"Hello world";

    SECTION("append to utf8 string")
    {
        std::string target;
        auto result = convert(source.begin(),source.end(),
                              std::back_inserter(target),
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK("Hello world" == target);
    }

    SECTION("append to utf16 string")
    {
        std::u16string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(u"Hello world" == target);
    }

    SECTION("append to utf32 string")
    {
        std::u32string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(U"Hello world" == target);
    }
}

TEST_CASE( "utf32") 
{
    std::u32string source = U"Hello world";

    SECTION("append to utf8 string")
    {
        std::string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK("Hello world" == target);
    }

    SECTION("append to utf16 string")
    {
        std::u16string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(u"Hello world" == target);
    }

    SECTION("append to utf32 string")
    {
        std::u32string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(U"Hello world" == target);
    }
}

TEST_CASE("utf8 tests") 
{
    std::string source = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                         "\xc2\x80"
                         "\xc3\xbf"
                         "\xcf\xbf"
                         "\xdb\xbf"         // U+06FF
                         "\xe0\xa7\xbf"     // U+09FF
                         "\xf0\x9f\xad\xbf" // U+1FB7F
                         ;

    SECTION("append to utf8 string")
    {
        std::string target;
        auto result = convert(source.begin(),source.end(),std::back_inserter(target), 
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(source == target);
    }

    SECTION("append to utf16 string")
    {
        std::u16string expected = u"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                                  u"\x80"
                                  u"\xff"
                                  u"\x03ff"
                                  u"\x06ff"
                                  u"\x09FF" // U+09FF
                                  u"\xD83E\xDF7F";

        std::u16string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(expected == target);
    }

    SECTION("append to utf32 string")
    {
        std::u32string expected = U"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                                  U"\x80"
                                  U"\xff"
                                  U"\x03ff"
                                  U"\x06ff"
                                  U"\x09ff"
                                  U"\x1FB7F"
                                  ;

        std::u32string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(expected == target);
    }
}

TEST_CASE("utf16 tests") 
{
    std::u16string source = u"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                              u"\x80"
                              u"\xff"
                              u"\x03ff";

    SECTION("append to utf8 string")
    {
        std::string expected = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                             "\xc2\x80"
                             "\xc3\xbf"
                             "\xcf\xbf";

        std::string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(expected == target);
    }

    SECTION("append to utf16 string")
    {

        std::u16string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(source == target);
    }

    SECTION("append to utf32 string")
    {
        std::u32string expected = U"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                                  U"\x80"
                                  U"\xff"
                                  U"\x03ff";

        std::u32string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(expected == target);
    }
}

TEST_CASE("utf32 tests") 
{
    std::u32string source = U"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                            U"\x80"
                            U"\xff"
                            U"\x03ff";

    SECTION("append to utf8 string")
    {
        std::string expected = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                             "\xc2\x80"
                             "\xc3\xbf"
                             "\xcf\xbf";

        std::string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(expected == target);
    }

    SECTION("append to utf16 string")
    {
        std::u16string expected = u"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                                  u"\x80"
                                  u"\xff"
                                  u"\x03ff";

        std::u16string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(expected == target);
    }

    SECTION("append to utf32 string")
    {

        std::u32string target;
        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(source == target);
    }
}

TEST_CASE("utf32 to utf8") 
{
    std::string expected = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                         "\xc2\x80"
                         "\xc3\xbf"
                         "\xcf\xbf";

    std::string target;

    SECTION("char32_t")
    {
        std::u32string source = U"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                                U"\x80"
                                U"\xff"
                                U"\x03ff";

        auto result = convert(source.begin(),source.end(),
                                       std::back_inserter(target),
                                       conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(expected == target);
    }

    SECTION("uint32_t")
    {
        uint32_t data[] = {U'\x01',U'\x02',U'\x03',U'\x04',U'\x05',U'\x06',U'\x07',U'\x08',U'\x09',U'\x0a',U'\x0b',U'\x0c',U'\x0d',U'\x0e',U'\x0f',
            U'\x80',
            U'\xff',
            U'\x03ff'};
        std::basic_string<uint32_t> source(data,sizeof(data)/sizeof(uint32_t));

        auto result = convert(source.begin(),source.end(),
                              std::back_inserter(target),
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(expected == target);
    }

    SECTION("int32_t")
    {
        int32_t data[] = { U'\x01',U'\x02',U'\x03',U'\x04',U'\x05',U'\x06',U'\x07',U'\x08',U'\x09',U'\x0a',U'\x0b',U'\x0c',U'\x0d',U'\x0e',U'\x0f',
            U'\x80',
            U'\xff',
            U'\x03ff' };
        std::basic_string<int32_t> source(data, sizeof(data) / sizeof(int32_t));

        auto result = convert(source.begin(), source.end(),
                              std::back_inserter(target),
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == source.end());
        CHECK(expected == target);
    }
}

TEST_CASE("append codepoint to string") 
{
    uint32_t cp = 0x1f642;

    SECTION("string")
    {
        std::string target;
        std::string expected = "\xf0\x9f\x99\x82";

        auto result = convert(&cp,&cp + 1,
                              std::back_inserter(target),
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == &cp + 1);
        CHECK(expected == target);
    }

    SECTION("u16string")
    {
        std::u16string target;
        std::u16string expected = u"\xD83D\xDE42";

        auto result = convert(&cp,&cp + 1,
                              std::back_inserter(target),
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == &cp + 1);
        CHECK(expected == target);
    }

    SECTION("u32string")
    {
        std::u32string target;
        std::u32string expected = U"\x1F642";

        auto result = convert(&cp,&cp + 1,
                              std::back_inserter(target),
                              conv_flags::strict);
        REQUIRE(result.ec == conv_errc());
        CHECK(result.it == &cp + 1);
        CHECK(expected == target);
    }
}

TEST_CASE("surrogate pair") 
{
}
