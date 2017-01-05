// Copyright 2016 Daniel Parker
// Distributed under Boost license

#include <catch.hpp>
#include <unicode_traits.hpp>
#include <iostream>
#include <cstdint>

using namespace unicons;

TEST_CASE("utf8") 
{
    std::string source = "Hello world";
    const char* source_end = source.data() + source.length();

    SECTION("append to utf8 string")
    {
        const char* stop = nullptr;
        std::string target;
        auto result = unicode_traits<char>::append_to_string(source.data(),source_end,
                                               target, &stop,
                                               conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(source == target);
    }

    SECTION("append to utf16 string")
    {
        const char* stop = nullptr;
        std::u16string target;
        auto result = unicode_traits<char>::append_to_string(source.data(),source_end,
                                               target, &stop,
                                               conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(u"Hello world" == target);
    }

    SECTION("append to utf32 string")
    {
        const char* stop = nullptr;
        std::u32string target;
        auto result = unicode_traits<char>::append_to_string(source.data(),source_end,
                                               target, &stop,
                                               conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(U"Hello world" == target);
    }
}

TEST_CASE( "utf16") 
{
    std::u16string source = u"Hello world";
    const char16_t* source_end = source.data() + source.length();

    SECTION("append to utf8 string")
    {
        const char16_t* stop = nullptr;
        std::string target;
        auto result = unicode_traits<char16_t>::append_to_string(source.data(),source_end,
                                                   target, &stop,
                                                   conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK("Hello world" == target);
    }

    SECTION("append to utf16 string")
    {
        const char16_t* stop = nullptr;
        std::u16string target;
        auto result = unicode_traits<char16_t>::append_to_string(source.data(),source_end,
                                                   target, &stop,
                                                   conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(u"Hello world" == target);
    }

    SECTION("append to utf32 string")
    {
        const char16_t* stop = nullptr;
        std::u32string target;
        auto result = unicode_traits<char16_t>::append_to_string(source.data(),source_end,
                                                  target, &stop,
                                                  conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(U"Hello world" == target);
    }
}

TEST_CASE( "utf32") 
{
    std::u32string source = U"Hello world";
    const char32_t* source_end = source.data() + source.length();

    SECTION("append to utf8 string")
    {
        const char32_t* stop = nullptr;
        std::string target;
        auto result = unicode_traits<char32_t>::append_to_string(source.data(),source_end,
                                                   target, &stop,
                                                   conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK("Hello world" == target);
    }

    SECTION("append to utf16 string")
    {
        const char32_t* stop = nullptr;
        std::u16string target;
        auto result = unicode_traits<char32_t>::append_to_string(source.data(),source_end,
                                                   target, &stop,
                                                   conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(u"Hello world" == target);
    }

    SECTION("append to utf32 string")
    {
        const char32_t* stop = nullptr;
        std::u32string target;
        auto result = unicode_traits<char32_t>::append_to_string(source.data(),source_end,
                                                   target, &stop,
                                                   conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(U"Hello world" == target);
    }
}

TEST_CASE("utf8 tests") 
{
    std::string source = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                         "\xc2\x80"
                         "\xc3\xbf"
                         "\xcf\xbf";
    const char* source_end = source.data() + source.length();

    SECTION("append to utf8 string")
    {
        const char* stop = nullptr;
        std::string target;
        auto result = unicode_traits<char>::append_to_string(source.data(),source_end,
                                                             target, &stop,
                                                             conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(source == target);
    }

    SECTION("append to utf16 string")
    {
        std::u16string expected = u"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                                  u"\x80"
                                  u"\xff"
                                  u"\x03ff";

        const char* stop = nullptr;
        std::u16string target;
        auto result = unicode_traits<char>::append_to_string(source.data(),source_end,
                                                             target, &stop,
                                                             conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(expected == target);
    }

    SECTION("append to utf32 string")
    {
        std::u32string expected = U"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                                  U"\x80"
                                  U"\xff"
                                  U"\x03ff";

        const char* stop = nullptr;
        std::u32string target;
        auto result = unicode_traits<char>::append_to_string(source.data(),source_end,
                                                             target, &stop,
                                                             conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(expected == target);
    }
}

TEST_CASE("utf16 tests") 
{
    std::u16string source = u"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                              u"\x80"
                              u"\xff"
                              u"\x03ff";
    const char16_t* source_end = source.data() + source.length();

    SECTION("append to utf8 string")
    {
        std::string expected = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                             "\xc2\x80"
                             "\xc3\xbf"
                             "\xcf\xbf";

        const char16_t* stop = nullptr;
        std::string target;
        auto result = unicode_traits<char16_t>::append_to_string(source.data(),source_end,
                                                             target, &stop,
                                                             conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(expected == target);
    }

    SECTION("append to utf16 string")
    {

        const char16_t* stop = nullptr;
        std::u16string target;
        auto result = unicode_traits<char16_t>::append_to_string(source.data(),source_end,
                                                             target, &stop,
                                                             conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(source == target);
    }

    SECTION("append to utf32 string")
    {
        std::u32string expected = U"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                                  U"\x80"
                                  U"\xff"
                                  U"\x03ff";

        const char16_t* stop = nullptr;
        std::u32string target;
        auto result = unicode_traits<char16_t>::append_to_string(source.data(),source_end,
                                                             target, &stop,
                                                             conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(expected == target);
    }
}

TEST_CASE("utf32 tests") 
{
    std::u32string source = U"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                            U"\x80"
                            U"\xff"
                            U"\x03ff";
    const char32_t* source_end = source.data() + source.length();

    SECTION("append to utf8 string")
    {
        std::string expected = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                             "\xc2\x80"
                             "\xc3\xbf"
                             "\xcf\xbf";

        const char32_t* stop = nullptr;
        std::string target;
        auto result = unicode_traits<char32_t>::append_to_string(source.data(),source_end,
                                                             target, &stop,
                                                             conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(expected == target);
    }

    SECTION("append to utf16 string")
    {
        std::u16string expected = u"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
                                  u"\x80"
                                  u"\xff"
                                  u"\x03ff";

        const char32_t* stop = nullptr;
        std::u16string target;
        auto result = unicode_traits<char32_t>::append_to_string(source.data(),source_end,
                                                             target, &stop,
                                                             conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(expected == target);
    }

    SECTION("append to utf32 string")
    {

        const char32_t* stop = nullptr;
        std::u32string target;
        auto result = unicode_traits<char32_t>::append_to_string(source.data(),source_end,
                                                             target, &stop,
                                                             conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
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
        const char32_t* source_end = source.data() + source.length();
        const char32_t* stop = nullptr;

        auto result = unicode_traits<char32_t>::append_to_string(source.data(),source_end,
                                                                 target, &stop,
                                                                 conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(expected == target);
    }

    SECTION("uint32_t")
    {
        uint32_t data[] = {U'\x01',U'\x02',U'\x03',U'\x04',U'\x05',U'\x06',U'\x07',U'\x08',U'\x09',U'\x0a',U'\x0b',U'\x0c',U'\x0d',U'\x0e',U'\x0f',
            U'\x80',
            U'\xff',
            U'\x03ff'};
        std::basic_string<uint32_t> source(data,sizeof(data)/sizeof(uint32_t));
        const uint32_t* source_end = source.data() + source.length();
        const uint32_t* stop = nullptr;

        auto result = unicode_traits<uint32_t>::append_to_string(source.data(),source_end,
                                                                 target, &stop,
                                                                 conversion_flags ::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(expected == target);
    }

    SECTION("int32_t")
    {
        int32_t data[] = { U'\x01',U'\x02',U'\x03',U'\x04',U'\x05',U'\x06',U'\x07',U'\x08',U'\x09',U'\x0a',U'\x0b',U'\x0c',U'\x0d',U'\x0e',U'\x0f',
            U'\x80',
            U'\xff',
            U'\x03ff' };
        std::basic_string<int32_t> source(data, sizeof(data) / sizeof(int32_t));
        const int32_t* source_end = source.data() + source.length();
        const int32_t* stop = nullptr;

        auto result = unicode_traits<int32_t>::append_to_string(source.data(), source_end,
            target, &stop,
            conversion_flags::strict);
        REQUIRE(result == conversion_result::ok);
        CHECK(stop == source_end);
        CHECK(expected == target);
    }
}

