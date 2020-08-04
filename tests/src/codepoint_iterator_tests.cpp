// Copyright 2016 Daniel Parker
// Distributed under Boost license

#include <catch/catch.hpp>
#include <unicode_traits.hpp>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <type_traits>

using namespace unicons;

TEST_CASE("codepoint_iterator without exceptions tests") 
{
    SECTION("utf-8") 
    {
        std::string source = "Hi \xf0\x9f\x99\x82"; // U+1F642

        std::error_code ec;
        auto it = make_codepoint_iterator(source.begin(),source.end(),ec);
        REQUIRE(ec == conv_errc());

        auto last = end(it);
        REQUIRE((it != last));

        CHECK(*it == 'H');
        it.increment(ec);
        REQUIRE(!ec);
        REQUIRE(it != last);
        CHECK(*it == 'i');
        it.increment(ec);
        REQUIRE(!ec);
        REQUIRE(it != last);
        CHECK(*it == ' ');
        it.increment(ec);
        REQUIRE(!ec);
        REQUIRE(it != last);
        CHECK(*it == 0x1f642);
        it.increment(ec);
        CHECK(it == last);
    }
    SECTION("utf-16") 
    {
        std::u16string source = u"Hi \xD83D\xDE42"; // U+1F642

        std::error_code ec;
        auto it = make_codepoint_iterator(source.begin(),source.end(),ec);
        REQUIRE(!ec);

        auto last = end(it);
        REQUIRE(it != last);

        CHECK(*it == 'H');
        it.increment(ec);
        REQUIRE(!ec);
        REQUIRE(it != last);
        CHECK(*it == 'i');
        it.increment(ec);
        REQUIRE(!ec);
        REQUIRE(it != last);
        CHECK(*it == ' ');
        it.increment(ec);
        REQUIRE(!ec);
        REQUIRE(it != last);
        CHECK(*it == 0x1f642);
        it.increment(ec);
        CHECK(it == last);
    }
    SECTION("utf-32") 
    {
        std::u32string source = U"Hi \x1F642"; // U+1F642

        std::error_code ec;
        auto it = make_codepoint_iterator(source.begin(),source.end(),ec);
        REQUIRE(!ec);

        auto last = end(it);
        REQUIRE(it != last);
        CHECK(*it == 'H');
        it.increment(ec);
        REQUIRE(!ec);
        REQUIRE(it != last);
        CHECK(*it == 'i');
        it.increment(ec);
        REQUIRE(!ec);
        REQUIRE(it != last);
        CHECK(*it == ' ');
        it.increment(ec);
        REQUIRE(!ec);
        REQUIRE(it != last);
        CHECK(*it == 0x1f642);
        it.increment(ec);
        CHECK(it == last);

    }
}

TEST_CASE("codepoint_iterator for loop tests") 
{
    SECTION("utf-8") 
    {
        std::string source = "Hi \xf0\x9f\x99\x82"; // U+1F642

        auto it = make_codepoint_iterator(source.begin(),source.end());

        std::vector<uint32_t> codepoints;
        for (auto cp : it)
        {
            codepoints.push_back(cp);
        }
        REQUIRE(codepoints.size() == 4);
        CHECK(codepoints[0] == uint32_t('H'));
        CHECK(codepoints[1] == uint32_t('i'));
        CHECK(codepoints[2] == uint32_t(' '));
        CHECK(codepoints[3] == uint32_t(0x1f642));
    }
    SECTION("utf-16") 
    {
        std::u16string source = u"Hi \xD83D\xDE42"; // U+1F642

        auto it = make_codepoint_iterator(source.begin(),source.end());

        std::vector<uint32_t> codepoints;
        for (auto cp : it)
        {
            codepoints.push_back(cp);
        }
        REQUIRE(codepoints.size() == 4);
        CHECK(codepoints[0] == uint32_t('H'));
        CHECK(codepoints[1] == uint32_t('i'));
        CHECK(codepoints[2] == uint32_t(' '));
        CHECK(codepoints[3] == uint32_t(0x1f642));
    }
    SECTION("utf-32") 
    {
        std::u32string source = U"Hi \x1F642"; // U+1F642

        auto it = make_codepoint_iterator(source.begin(),source.end());

        std::vector<uint32_t> codepoints;
        for (auto cp : it)
        {
            codepoints.push_back(cp);
        }
        REQUIRE(codepoints.size() == 4);
        CHECK(codepoints[0] == uint32_t('H'));
        CHECK(codepoints[1] == uint32_t('i'));
        CHECK(codepoints[2] == uint32_t(' '));
        CHECK(codepoints[3] == uint32_t(0x1f642));
    }
}

