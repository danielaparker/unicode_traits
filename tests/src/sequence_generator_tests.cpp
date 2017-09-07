// Copyright 2016 Daniel Parker
// Distributed under Boost license

#include <catch.hpp>
#include <unicode_traits.hpp>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <type_traits>

using namespace unicons;

TEST_CASE("sequence_generator") 
{
    SECTION("utf-8") 
    {
        std::string source = "Hi \xf0\x9f\x99\x82"; // U+1F642

        sequence_generator<std::string::iterator> g(source.begin(),source.end());
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == 'H');
        g.next();
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == 'i');
        g.next();
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == ' ');
        g.next();
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == 0x1f642);
        g.next();
        CHECK(g.done());
    }
    SECTION("utf-16") 
    {
        std::u16string source = u"Hi \xD83D\xDE42"; // U+1F642

        sequence_generator<std::u16string::iterator> g(source.begin(),source.end());
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == 'H');
        g.next();
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == 'i');
        g.next();
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == ' ');
        g.next();
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == 0x1f642);
        g.next();
        CHECK(g.done());
    }
    SECTION("utf-32") 
    {
        std::u32string source = U"Hi \x1F642"; // U+1F642

        sequence_generator<std::u32string::iterator> g(source.begin(),source.end());
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == 'H');
        g.next();
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == 'i');
        g.next();
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == ' ');
        g.next();
        REQUIRE(g.status() == conv_errc());
        REQUIRE(!g.done());
        CHECK(g.get().codepoint() == 0x1f642);
        g.next();
        CHECK(g.done());
    }
}

