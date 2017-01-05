// Copyright 2016 Daniel Parker
// Distributed under Boost license

#include <catch.hpp>
#include <unicode_traits.hpp>
#include <iostream>
#include <cstdint>
#include <vector>
#include <iterator>
#include <type_traits>

using namespace unicons;

TEST_CASE("is_compatible_output_iterator") 
{
    bool result;

    SECTION("std::ostreambuf_iterator<char>")
    {
        result = is_compatible_output_iterator<std::ostreambuf_iterator<char>, char>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::ostreambuf_iterator<char>, int8_t>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::ostreambuf_iterator<char>, uint8_t>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::ostreambuf_iterator<char>, wchar_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::ostreambuf_iterator<char>, uint16_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::ostreambuf_iterator<char>, uint32_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::ostreambuf_iterator<char>, char32_t>();
        CHECK(result == false);
    }
    SECTION("std::back_insert_iterator<std::vector<char>>")
    {
        result = is_compatible_output_iterator<std::back_insert_iterator<std::vector<char>>, char>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::back_insert_iterator<std::vector<char>>, int8_t>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::back_insert_iterator<std::vector<char>>, uint8_t>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::back_insert_iterator<std::vector<char>>, wchar_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::back_insert_iterator<std::vector<char>>, uint16_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::back_insert_iterator<std::vector<char>>, uint32_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::back_insert_iterator<std::vector<char>>, char32_t>();
        CHECK(result == false);
    }
    SECTION("std::front_insert_iterator<std::vector<char>>")
    {
        result = is_compatible_output_iterator<std::front_insert_iterator<std::vector<char>>, char>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::front_insert_iterator<std::vector<char>>, int8_t>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::front_insert_iterator<std::vector<char>>, uint8_t>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::front_insert_iterator<std::vector<char>>, wchar_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::front_insert_iterator<std::vector<char>>, uint16_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::front_insert_iterator<std::vector<char>>, uint32_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::front_insert_iterator<std::vector<char>>, char32_t>();
        CHECK(result == false);
    }
    SECTION("std::insert_iterator<std::vector<char>")
    {
        result = is_compatible_output_iterator<std::insert_iterator<std::vector<char>>, char>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::insert_iterator<std::vector<char>>, int8_t>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::insert_iterator<std::vector<char>>, uint8_t>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::insert_iterator<std::vector<char>>, wchar_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::insert_iterator<std::vector<char>>, uint16_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::insert_iterator<std::vector<char>>, uint32_t>();
        CHECK(result == false);
        result = is_compatible_output_iterator<std::insert_iterator<std::vector<char>>, char32_t>();
        CHECK(result == false);
    }
    SECTION("std::vector<char>::iterator")
    {
        result = is_compatible_output_iterator<std::vector<char>::iterator, char>();
        CHECK(result == true);
        result = is_compatible_output_iterator<std::vector<char>::iterator, wchar_t>();
        CHECK(result == false);
    }
    SECTION("char*")
    {
        result = is_compatible_output_iterator<char*, char>();
        CHECK(result == true);
        result = is_compatible_output_iterator<char*, wchar_t>();
        CHECK(result == false);
    }
    SECTION("wchar_t*")
    {
        result = is_compatible_output_iterator<wchar_t*, char>();
        CHECK(result == false);
        result = is_compatible_output_iterator<wchar_t*, wchar_t>();
        CHECK(result == true);
    }
}

