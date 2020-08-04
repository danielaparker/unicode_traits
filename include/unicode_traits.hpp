// Copyright 2016-2020 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/unicode_traits for latest version

/*
 * Includes code derived from Unicode, Inc decomposition code in ConvertUTF.h and ConvertUTF.c 
 * http://www.unicode.org/  
 *  
 * "Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard."
*/

#ifndef UNICONS_UNICODE_TRAITS_HPP
#define UNICONS_UNICODE_TRAITS_HPP

#include <string>
#include <iterator>
#include <type_traits>
#include <system_error>
#include <cstdint>
    
#define UNICONS_VERSION_MAJOR 0
#define UNICONS_VERSION_MINOR 5
#define UNICONS_VERSION_PATCH 0

#if defined(__clang__) 
#  define UNICONS_FALLTHROUGH [[clang::fallthrough]]
#elif defined(__GNUC__) && ((__GNUC__ >= 7))
#  define UNICONS_FALLTHROUGH __attribute__((fallthrough))
#elif defined (__GNUC__)
#  define UNICONS_FALLTHROUGH // FALLTHRU
#else
#  define UNICONS_FALLTHROUGH
#endif

// allow to disable exceptions
#if !defined(UNICONS_NO_EXCEPTIONS)
    #define UNICONS_THROW(exception) throw exception
#else
    #define UNICONS_THROW(exception) std::terminate()
#endif

namespace unicons {

    class unicode_error : public std::system_error
    {
    public:
        unicode_error(std::error_code ec)
            : std::system_error(ec)
        {
        }

        const char* what() const noexcept override
        {
            return std::system_error::what();
        }
    };

    // follows https://en.cppreference.com/w/cpp/types/void_t
    template<typename... Ts> struct make_void { typedef void type;};
    template<typename... Ts> using void_t = typename make_void<Ts...>::type;

    // is_char8
    template <typename CharT, typename Enable=void>
    struct is_char8 : std::false_type {};

    template <typename CharT>
    struct is_char8<CharT, typename std::enable_if<std::is_integral<CharT>::value &&
                                                   !std::is_same<CharT,bool>::value &&
                                                   sizeof(uint8_t) == sizeof(CharT)>::type> : std::true_type {};

    // is_char16
    template <typename CharT, typename Enable=void>
    struct is_char16 : std::false_type {};

    template <typename CharT>
    struct is_char16<CharT, typename std::enable_if<std::is_integral<CharT>::value &&
                                                   !std::is_same<CharT,bool>::value &&
                                                   std::is_same<CharT,char16_t>::value || sizeof(uint16_t) == sizeof(CharT)>::type> : std::true_type {};

    // is_char32
    template <typename CharT, typename Enable=void>
    struct is_char32 : std::false_type {};

    template <typename CharT>
    struct is_char32<CharT, typename std::enable_if<std::is_integral<CharT>::value &&
                                                   !std::is_same<CharT,bool>::value &&
                                                   std::is_same<CharT,char32_t>::value || (!std::is_same<CharT,char16_t>::value && sizeof(uint32_t) == sizeof(CharT))>::type> : std::true_type {};

    // is_character
    template <typename CharT, typename Enable=void>
    struct is_character : std::false_type {};

    template <typename CharT>
    struct is_character<CharT, typename std::enable_if<is_char8<CharT>::value || 
                                                       is_char16<CharT>::value ||
                                                       is_char32<CharT>::value>::type> : std::true_type {};

    /*
     * Magic values subtracted from a buffer value during UTF8 conversion.
     * This table contains as many values as there might be trailing bytes
     * in a UTF-8 sequence. Source: ConvertUTF.c
     */
    constexpr uint32_t offsets_from_utf8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL, 
                  0x03C82080UL, 0xFA082080UL, 0x82082080UL };

    /*
     * Once the bits are split out into bytes of UTF-8, this is a mask OR-ed
     * into the first byte, depending on how many bytes follow.  There are
     * as many entries in this table as there are UTF-8 sequence types.
     * (I.e., one byte sequence, two byte... etc.). Remember that sequencs
     * for *legal* UTF-8 will be 4 or fewer bytes total. Source: ConvertUTF.c
     */
    constexpr uint8_t first_byte_mark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

    /*
     * Index into the table below with the first byte of a UTF-8 sequence to
     * get the number of trailing bytes that are supposed to follow it.
     * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
     * left as-is for anyone who may want to do such conversion, which was
     * allowed in earlier algorithms. Source: ConvertUTF.c
     */
    constexpr uint8_t trailing_bytes_for_utf8[256] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
    };

    // Some fundamental constants.  Source: ConvertUTF.h 
    constexpr uint32_t replacement_char = 0x0000FFFD;
    constexpr uint32_t max_bmp = 0x0000FFFF;
    constexpr uint32_t max_utf16 = 0x0010FFFF;
    constexpr uint32_t max_utf32 = 0x7FFFFFFF;
    constexpr uint32_t max_legal_utf32 = 0x0010FFFF;

    constexpr int half_shift  = 10; // used for shifting by 10 bits
    constexpr uint32_t half_base = 0x0010000UL;
    constexpr uint32_t half_mask = 0x3FFUL;

    constexpr uint16_t sur_high_start = 0xD800;
    constexpr uint16_t sur_high_end = 0xDBFF;
    constexpr uint16_t sur_low_start = 0xDC00;
    constexpr uint16_t sur_low_end = 0xDFFF;

    inline
    static bool is_continuation_byte(uint8_t ch)
    {
        return (ch & 0xC0) == 0x80;
    }

    inline
    bool is_high_surrogate(uint32_t ch) noexcept
    {
        return (ch >= sur_high_start && ch <= sur_high_end);
    }

    inline
    bool is_low_surrogate(uint32_t ch) noexcept
    {
        return (ch >= sur_low_start && ch <= sur_low_end);
    }

    inline
    bool is_surrogate(uint32_t ch) noexcept
    {
        return (ch >= sur_high_start && ch <= sur_low_end);
    }

    enum class conv_flags 
    {
        strict = 0,
        lenient
    };

    // conv_errc

    enum class conv_errc 
    {
        success = 0,
        over_long_utf8_sequence = 1, // over long utf8 sequence
        expected_continuation_byte,  // expected continuation byte    
        unpaired_high_surrogate,     // unpaired high surrogate UTF-16
        illegal_surrogate_value,     // UTF-16 surrogate values are illegal in UTF-32
        source_exhausted,            // partial character in source, but hit end
        source_illegal               // source sequence is illegal/malformed
    };

    class Unicode_traits_error_category_impl_
       : public std::error_category
    {
    public:
        virtual const char* name() const noexcept
        {
            return "unicons conversion error";
        }
        virtual std::string message(int ev) const
        {
            switch (static_cast<conv_errc>(ev))
            {
            case conv_errc::over_long_utf8_sequence:
                return "Over long utf8 sequence";
            case conv_errc::expected_continuation_byte:
                return "Expected continuation byte";
            case conv_errc::unpaired_high_surrogate:
                return "Unpaired high surrogate UTF-16";
            case conv_errc::illegal_surrogate_value:
                return "UTF-16 surrogate values are illegal in UTF-32";
            case conv_errc::source_exhausted:
                return "Partial character in source, but hit end";
            case conv_errc::source_illegal:
                return "Source sequence is illegal/malformed";
            default:
                return "";
                break;
            }
        }
    };

    inline
    const std::error_category& unicode_traits_error_category()
    {
      static Unicode_traits_error_category_impl_ instance;
      return instance;
    }

    inline 
    std::error_code make_error_code(conv_errc result)
    {
        return std::error_code(static_cast<int>(result),unicode_traits_error_category());
    }

} // namespace unicons

namespace std {
    template<>
    struct is_error_code_enum<unicons::conv_errc> : public true_type
    {
    };
}

namespace unicons {

    // encoding_errc

    enum class encoding_errc
    {
        success = 0,
        expected_u8_found_u16 = 1,
        expected_u8_found_u32,
        expected_u16_found_fffe,
        expected_u32_found_fffe
    };

    class Encoding_errc_impl_
       : public std::error_category
    {
    public:
        virtual const char* name() const noexcept
        {
            return "unicons encoding error";
        }
        virtual std::string message(int ev) const
        {
            switch (static_cast<encoding_errc>(ev))
            {
            case encoding_errc::expected_u8_found_u16:
                return "Expected UTF-8, found UTF-16";
            case encoding_errc::expected_u8_found_u32:
                return "Expected UTF-8, found UTF-32";
            case encoding_errc::expected_u16_found_fffe:
                return "Expected UTF-16, found non character";
            case encoding_errc::expected_u32_found_fffe:
                return "Expected UTF-32, found non character";
            default:
                return "";
                break;
            }
        }
    };

    inline
    const std::error_category& encoding_error_category()
    {
        static Encoding_errc_impl_ instance;
        return instance;
    }

    inline 
    std::error_code make_error_code(encoding_errc result)
    {
        return std::error_code(static_cast<int>(result),encoding_error_category());
    }

    // utf8

    template <typename Iterator>
    typename std::enable_if<is_char8<typename std::iterator_traits<Iterator>::value_type>::value, 
                                  conv_errc >::type
    is_legal_utf8(Iterator first, std::size_t length) 
    {
        uint8_t a;
        Iterator srcptr = first+length;
        switch (length) {
        default:
            return conv_errc::over_long_utf8_sequence;
        case 4:
            if (((a = (*--srcptr))& 0xC0) != 0x80)
                return conv_errc::expected_continuation_byte;
            UNICONS_FALLTHROUGH;
        case 3:
            if (((a = (*--srcptr))& 0xC0) != 0x80)
                return conv_errc::expected_continuation_byte;
            UNICONS_FALLTHROUGH;
        case 2:
            if (((a = (*--srcptr))& 0xC0) != 0x80)
                return conv_errc::expected_continuation_byte;

            switch (static_cast<uint8_t>(*first)) 
            {
                /* no fall-through in this inner switch */
                case 0xE0: if (a < 0xA0) return conv_errc::source_illegal; break;
                case 0xED: if (a > 0x9F) return conv_errc::source_illegal; break;
                case 0xF0: if (a < 0x90) return conv_errc::source_illegal; break;
                case 0xF4: if (a > 0x8F) return conv_errc::source_illegal; break;
                default:   if (a < 0x80) return conv_errc::source_illegal;
            }

            UNICONS_FALLTHROUGH;
        case 1:
            if (static_cast<uint8_t>(*first) >= 0x80 && static_cast<uint8_t>(*first) < 0xC2)
                return conv_errc::source_illegal;
            break;
        }
        if (static_cast<uint8_t>(*first) > 0xF4) 
            return conv_errc::source_illegal;

        return conv_errc();
    }

    template <typename, typename, typename = void>
    struct is_output_iterator : std::false_type {};

    template <typename I, typename E>
    struct is_output_iterator<I, E, void_t<
        typename std::iterator_traits<I>::iterator_category,
        decltype(*std::declval<I>() = std::declval<E>())>> : std::true_type {};

    // is_same_size fixes issue with vs2013

    // primary template
    template<class T1, typename T2, typename Enable = void>
    struct is_same_size : std::false_type 
    {
    };
     
    // specialization for non void types
    template<class T1, typename T2>
    struct is_same_size<T1, T2, typename std::enable_if<!std::is_void<T1>::value && !std::is_void<T2>::value>::type>
    {
        static constexpr bool value = (sizeof(T1) == sizeof(T2));
    }; 

    template<class OutputIt, typename CharT, typename Enable = void>
    struct is_compatible_output_iterator : std::false_type {};

    template<class OutputIt, typename CharT>
    struct is_compatible_output_iterator<OutputIt,CharT,
        typename std::enable_if<is_output_iterator<OutputIt,CharT>::value
                                && std::is_void<typename std::iterator_traits<OutputIt>::value_type>::value
                                && is_character<typename OutputIt::container_type::value_type>::value 
                                && !std::is_void<typename OutputIt::container_type::value_type>::value
                                && is_same_size<typename OutputIt::container_type::value_type,CharT>::value>::type
    > : std::true_type {};

    template<class OutputIt, typename CharT>
    struct is_compatible_output_iterator<OutputIt,CharT,
        typename std::enable_if<is_output_iterator<OutputIt,CharT>::value
                                && is_character<typename std::iterator_traits<OutputIt>::value_type>::value 
                                && is_same_size<typename std::iterator_traits<OutputIt>::value_type,CharT>::value>::type
    > : std::true_type {};

    template<class OutputIt, typename CharT>
    struct is_compatible_output_iterator<OutputIt,CharT,
        typename std::enable_if<is_output_iterator<OutputIt,CharT>::value
                                && std::is_void<typename std::iterator_traits<OutputIt>::value_type>::value
                                && is_same_size<typename OutputIt::char_type,CharT>::value>::type
    > : std::true_type {};

    // convert

    template <typename Iterator>
    struct convert_result
    {
        Iterator it;
        conv_errc ec;
    };

    template <typename InputIt,class OutputIt>
    typename std::enable_if<is_char8<typename std::iterator_traits<InputIt>::value_type>::value
                            && is_compatible_output_iterator<OutputIt,uint8_t>::value,convert_result<InputIt>>::type 
    convert(InputIt first, InputIt last, OutputIt target, conv_flags flags=conv_flags::strict) 
    {
        (void)flags;

        conv_errc  result = conv_errc();
        while (first != last) 
        {
            std::size_t length = trailing_bytes_for_utf8[static_cast<uint8_t>(*first)] + 1;
            if (length > (std::size_t)(last - first))
            {
                return convert_result<InputIt>{first, conv_errc::source_exhausted};
            }
            if ((result=is_legal_utf8(first, length)) != conv_errc())
            {
                return convert_result<InputIt>{first,result};
            }

            switch (length) {
                case 4: *target++ = (static_cast<uint8_t>(*first++));
                    UNICONS_FALLTHROUGH;
                case 3: *target++ = (static_cast<uint8_t>(*first++));
                    UNICONS_FALLTHROUGH;
                case 2: *target++ = (static_cast<uint8_t>(*first++));
                    UNICONS_FALLTHROUGH;
                case 1: *target++ = (static_cast<uint8_t>(*first++));
            }
        }
        return convert_result<InputIt>{first,result} ;
    }

    template <typename InputIt,class OutputIt>
    typename std::enable_if<is_char8<typename std::iterator_traits<InputIt>::value_type>::value
                                   && is_compatible_output_iterator<OutputIt,uint16_t>::value,convert_result<InputIt>>::type 
    convert(InputIt first, InputIt last, 
            OutputIt target, 
            conv_flags flags = conv_flags::strict) 
    {
        conv_errc  result = conv_errc();

        while (first != last) 
        {
            uint32_t ch = 0;
            unsigned short extra_bytes_to_read = trailing_bytes_for_utf8[static_cast<uint8_t>(*first)];
            if (extra_bytes_to_read >= last - first) 
            {
                result = conv_errc::source_exhausted; 
                break;
            }
            /* Do this check whether lenient or strict */
            if ((result=is_legal_utf8(first, extra_bytes_to_read+1)) != conv_errc())
            {
                break;
            }
            /*
             * The cases all fall through. See "Note A" below.
             */
            switch (extra_bytes_to_read) {
                case 5: ch += static_cast<uint8_t>(*first++); ch <<= 6; UNICONS_FALLTHROUGH; /* remember, illegal UTF-8 */
                case 4: ch += static_cast<uint8_t>(*first++); ch <<= 6; UNICONS_FALLTHROUGH; /* remember, illegal UTF-8 */
                case 3: ch += static_cast<uint8_t>(*first++); ch <<= 6; UNICONS_FALLTHROUGH;
                case 2: ch += static_cast<uint8_t>(*first++); ch <<= 6; UNICONS_FALLTHROUGH;
                case 1: ch += static_cast<uint8_t>(*first++); ch <<= 6; UNICONS_FALLTHROUGH;
                case 0: ch += static_cast<uint8_t>(*first++); break;
            }
            ch -= offsets_from_utf8[extra_bytes_to_read];

            if (ch <= max_bmp) { /* Target is a character <= 0xFFFF */
                /* UTF-16 surrogate values are illegal in UTF-32 */
                if (is_surrogate(ch) ) {
                    if (flags == conv_flags::strict) {
                        first -= (extra_bytes_to_read+1); /* return to the illegal value itself */
                        result = conv_errc::source_illegal;
                        break;
                    } else {
                        *target++ = (replacement_char);
                    }
                } else {
                    *target++ = ((uint16_t)ch); /* normal case */
                }
            } else if (ch > max_utf16) {
                if (flags == conv_flags::strict) {
                    result = conv_errc::source_illegal;
                    first -= (extra_bytes_to_read+1); /* return to the start */
                    break; /* Bail out; shouldn't continue */
                } else {
                    *target++ = (replacement_char);
                }
            } else {
                /* target is a character in range 0xFFFF - 0x10FFFF. */
                ch -= half_base;
                *target++ = ((uint16_t)((ch >> half_shift) + sur_high_start));
                *target++ = ((uint16_t)((ch & half_mask) + sur_low_start));
            }
        }
        return convert_result<InputIt>{first,result} ;
    }

    template <typename InputIt,class OutputIt>
    typename std::enable_if<is_char8<typename std::iterator_traits<InputIt>::value_type>::value
                                   && is_compatible_output_iterator<OutputIt,uint32_t>::value,convert_result<InputIt>>::type 
    convert(InputIt first, InputIt last, 
                     OutputIt target, 
                     conv_flags flags = conv_flags::strict) 
    {
        conv_errc  result = conv_errc();

        while (first < last) 
        {
            uint32_t ch = 0;
            unsigned short extra_bytes_to_read = trailing_bytes_for_utf8[static_cast<uint8_t>(*first)];
            if (extra_bytes_to_read >= last - first) 
            {
                result = conv_errc::source_exhausted; 
                break;
            }
            /* Do this check whether lenient or strict */
            if ((result=is_legal_utf8(first, extra_bytes_to_read+1)) != conv_errc()) {
                break;
            }
            /*
             * The cases all fall through. See "Note A" below.
             */
            switch (extra_bytes_to_read) 
            {
                case 5: 
                    ch += static_cast<uint8_t>(*first++); 
                    ch <<= 6;
                    UNICONS_FALLTHROUGH;
                case 4: 
                    ch += static_cast<uint8_t>(*first++); 
                    ch <<= 6;
                    UNICONS_FALLTHROUGH;
                case 3: 
                    ch += static_cast<uint8_t>(*first++); 
                    ch <<= 6;
                    UNICONS_FALLTHROUGH;
                case 2: 
                    ch += static_cast<uint8_t>(*first++); 
                    ch <<= 6;
                    UNICONS_FALLTHROUGH;
                case 1: 
                    ch += static_cast<uint8_t>(*first++); 
                    ch <<= 6;
                    UNICONS_FALLTHROUGH;
                case 0: 
                    ch += static_cast<uint8_t>(*first++);
                    break;
            }
            ch -= offsets_from_utf8[extra_bytes_to_read];

            if (ch <= max_legal_utf32) {
                /*
                 * UTF-16 surrogate values are illegal in UTF-32, and anything
                 * over Plane 17 (> 0x10FFFF) is illegal.
                 */
                if (is_surrogate(ch) ) {
                    if (flags == conv_flags::strict) {
                        first -= (extra_bytes_to_read+1); /* return to the illegal value itself */
                        result = conv_errc::source_illegal;
                        break;
                    } else {
                        *target++ = (replacement_char);
                    }
                } else {
                    *target++ = (ch);
                }
            } else { /* i.e., ch > max_legal_utf32 */
                result = conv_errc::source_illegal;
                *target++ = (replacement_char);
            }
        }
        return convert_result<InputIt>{first,result} ;
    }

    // utf16

    template <typename InputIt,class OutputIt>
    typename std::enable_if<is_char16<typename std::iterator_traits<InputIt>::value_type>::value
                                   && is_compatible_output_iterator<OutputIt,uint8_t>::value,convert_result<InputIt>>::type 
    convert(InputIt first, InputIt last, 
                     OutputIt target, 
                     conv_flags flags = conv_flags::strict) {
        conv_errc  result = conv_errc();
        while (first < last) {
            unsigned short bytes_to_write = 0;
            const uint32_t byteMask = 0xBF;
            const uint32_t byteMark = 0x80; 
            uint32_t ch = *first++;
            /* If we have a surrogate pair, convert to uint32_t first. */
            if (is_high_surrogate(ch)) {
                /* If the 16 bits following the high surrogate are in the first buffer... */
                if (first < last) {
                    uint32_t ch2 = *first;
                    /* If it's a low surrogate, convert to uint32_t. */
                    if (ch2 >= sur_low_start && ch2 <= sur_low_end) {
                        ch = ((ch - sur_high_start) << half_shift)
                            + (ch2 - sur_low_start) + half_base;
                        ++first;
                    } else if (flags == conv_flags::strict) { /* it's an unpaired high surrogate */
                        --first; /* return to the illegal value itself */
                        result = conv_errc::unpaired_high_surrogate;
                        break;
                    }
                } else { /* We don't have the 16 bits following the high surrogate. */
                    --first; /* return to the high surrogate */
                    result = conv_errc::source_exhausted;
                    break;
                }
            } else if (flags == conv_flags::strict) {
                /* UTF-16 surrogate values are illegal in UTF-32 */
                if (is_low_surrogate(ch)) {
                    --first; /* return to the illegal value itself */
                    result = conv_errc::source_illegal;
                    break;
                }
            }
            /* Figure out how many bytes the result will require */
            if (ch < (uint32_t)0x80) {      
                bytes_to_write = 1;
            } else if (ch < (uint32_t)0x800) {     
                bytes_to_write = 2;
            } else if (ch < (uint32_t)0x10000) {   
                bytes_to_write = 3;
            } else if (ch < (uint32_t)0x110000) {  
                bytes_to_write = 4;
            } else {                            
                bytes_to_write = 3;
                ch = replacement_char;
            }
            
            uint8_t byte1 = 0;
            uint8_t byte2 = 0;
            uint8_t byte3 = 0;
            uint8_t byte4 = 0;

            switch (bytes_to_write) { // note: everything falls through
                case 4: byte4 = (uint8_t)((ch | byteMark) & byteMask); ch >>= 6;UNICONS_FALLTHROUGH;
                case 3: byte3 = (uint8_t)((ch | byteMark) & byteMask); ch >>= 6;UNICONS_FALLTHROUGH;
                case 2: byte2 = (uint8_t)((ch | byteMark) & byteMask); ch >>= 6;UNICONS_FALLTHROUGH;
                case 1: byte1 = (uint8_t)(ch | first_byte_mark[bytes_to_write]);break;
            }
            switch (bytes_to_write) 
            {
            case 4: 
                *target++ = (byte1);
                *target++ = (byte2);
                *target++ = (byte3);
                *target++ = (byte4);
                break;
            case 3: 
                *target++ = (byte1);
                *target++ = (byte2);
                *target++ = (byte3);
                break;
            case 2: 
                *target++ = (byte1);
                *target++ = (byte2);
                break;
            case 1: 
                *target++ = (byte1);
                break;
            }
        }
        return convert_result<InputIt>{first,result} ;
    }

    template <typename InputIt,class OutputIt>
    typename std::enable_if<is_char16<typename std::iterator_traits<InputIt>::value_type>::value
                                   && is_compatible_output_iterator<OutputIt,uint16_t>::value,convert_result<InputIt>>::type 
    convert(InputIt first, InputIt last, 
            OutputIt target, 
            conv_flags flags = conv_flags::strict) 
    {
        conv_errc  result = conv_errc();

        while (first != last) 
        {
            uint32_t ch = *first++;
            /* If we have a surrogate pair, convert to uint32_t first. */
            if (is_high_surrogate(ch)) 
            {
                /* If the 16 bits following the high surrogate are in the first buffer... */
                if (first < last) {
                    uint32_t ch2 = *first;
                    /* If it's a low surrogate, */
                    if (ch2 >= sur_low_start && ch2 <= sur_low_end) {
                        *target++ = ((uint16_t)ch);
                        *target++ = ((uint16_t)ch2);
                        ++first;
                    } else if (flags == conv_flags::strict) { /* it's an unpaired high surrogate */
                        --first; /* return to the illegal value itself */
                        result = conv_errc::unpaired_high_surrogate;
                        break;
                    }
                } else { /* We don't have the 16 bits following the high surrogate. */
                    --first; /* return to the high surrogate */
                    result = conv_errc::source_exhausted;
                    break;
                }
            } else if (is_low_surrogate(ch)) 
            {
                // illegal leading low surrogate
                if (flags == conv_flags::strict) {
                    --first; /* return to the illegal value itself */
                    result = conv_errc::source_illegal;
                    break;
                }
                else
                {
                    *target++ = ((uint16_t)ch);
                }
            }
            else
            {
                *target++ = ((uint16_t)ch);
            }
        }
        return convert_result<InputIt>{first,result} ;
    }

    template <typename InputIt,class OutputIt>
    typename std::enable_if<is_char16<typename std::iterator_traits<InputIt>::value_type>::value
                                   && is_compatible_output_iterator<OutputIt,uint32_t>::value,convert_result<InputIt>>::type 
    convert(InputIt first, InputIt last, 
            OutputIt target, 
            conv_flags flags = conv_flags::strict) 
    {
        conv_errc  result = conv_errc();

        while (first != last) 
        {
            uint32_t ch = *first++;
            /* If we have a surrogate pair, convert to UTF32 first. */
            if (is_high_surrogate(ch)) {
                /* If the 16 bits following the high surrogate are in the first buffer... */
                if (first < last) {
                    uint32_t ch2 = *first;
                    /* If it's a low surrogate, convert to UTF32. */
                    if (ch2 >= sur_low_start && ch2 <= sur_low_end ) {
                        ch = ((ch - sur_high_start) << half_shift)
                            + (ch2 - sur_low_start) + half_base;
                        ++first;
                    } else if (flags == conv_flags::strict) { /* it's an unpaired high surrogate */
                        --first; /* return to the illegal value itself */
                        result = conv_errc::source_illegal;
                        break;
                    }
                } else { /* We don't have the 16 bits following the high surrogate. */
                    --first; /* return to the high surrogate */
                    result = conv_errc::source_exhausted;
                    break;
                }
            } else if (flags == conv_flags::strict) {
                /* UTF-16 surrogate values are illegal in UTF-32 */
                if (is_low_surrogate(ch) ) {
                    --first; /* return to the illegal value itself */
                    result = conv_errc::source_illegal;
                    break;
                }
            }
            *target++ = (ch);
        }
        return convert_result<InputIt>{first,result} ;
    }

    // utf32

    template <typename InputIt,class OutputIt>
    typename std::enable_if<is_char32<typename std::iterator_traits<InputIt>::value_type>::value
                                   && is_compatible_output_iterator<OutputIt,uint8_t>::value,convert_result<InputIt>>::type 
    convert(InputIt first, InputIt last, 
            OutputIt target, 
            conv_flags flags = conv_flags::strict) 
    {
        conv_errc  result = conv_errc();
        while (first < last) {
            unsigned short bytes_to_write = 0;
            const uint32_t byteMask = 0xBF;
            const uint32_t byteMark = 0x80; 
            uint32_t ch = *first++;
            if (flags == conv_flags::strict ) {
                /* UTF-16 surrogate values are illegal in UTF-32 */
                if (is_surrogate(ch)) {
                    --first; /* return to the illegal value itself */
                    result = conv_errc::illegal_surrogate_value;
                    break;
                }
            }
            /*
             * Figure out how many bytes the result will require. Turn any
             * illegally large UTF32 things (> Plane 17) into replacement chars.
             */
            if (ch < (uint32_t)0x80) {      bytes_to_write = 1;
            } else if (ch < (uint32_t)0x800) {     bytes_to_write = 2;
            } else if (ch < (uint32_t)0x10000) {   bytes_to_write = 3;
            } else if (ch <= max_legal_utf32) {  bytes_to_write = 4;
            } else {                            
                bytes_to_write = 3;
                ch = replacement_char;
                result = conv_errc::source_illegal;
            }

            uint8_t byte1 = 0;
            uint8_t byte2 = 0;
            uint8_t byte3 = 0;
            uint8_t byte4 = 0;

            switch (bytes_to_write) {
            case 4:
                byte4 = (uint8_t)((ch | byteMark) & byteMask); ch >>= 6;
                UNICONS_FALLTHROUGH;
            case 3:
                byte3 = (uint8_t)((ch | byteMark) & byteMask); ch >>= 6;
                UNICONS_FALLTHROUGH;
            case 2:
                byte2 = (uint8_t)((ch | byteMark) & byteMask); ch >>= 6;
                UNICONS_FALLTHROUGH;
            case 1:
                byte1 = (uint8_t) (ch | first_byte_mark[bytes_to_write]);
            }

            switch (bytes_to_write) 
            {
            case 4: 
                *target++ = (byte1);
                *target++ = (byte2);
                *target++ = (byte3);
                *target++ = (byte4);
                break;
            case 3: 
                *target++ = (byte1);
                *target++ = (byte2);
                *target++ = (byte3);
                break;
            case 2: 
                *target++ = (byte1);
                *target++ = (byte2);
                break;
            case 1: 
                *target++ = (byte1);
                break;
            }
        }
        return convert_result<InputIt>{first,result} ;
    }

    template <typename InputIt,class OutputIt>
    typename std::enable_if<is_char32<typename std::iterator_traits<InputIt>::value_type>::value
                                   && is_compatible_output_iterator<OutputIt,uint16_t>::value,convert_result<InputIt>>::type 
    convert(InputIt first, InputIt last, 
            OutputIt target, 
            conv_flags flags = conv_flags::strict) 
    {
        conv_errc  result = conv_errc();

        while (first != last) 
        {
            uint32_t ch = *first++;
            if (ch <= max_bmp) { /* Target is a character <= 0xFFFF */
                /* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
                if (is_surrogate(ch) ) {
                    if (flags == conv_flags::strict) {
                        --first; /* return to the illegal value itself */
                        result = conv_errc::source_illegal;
                        break;
                    } else {
                        *target++ = (replacement_char);
                    }
                } else {
                    *target++ = ((uint16_t)ch); /* normal case */
                }
            } else if (ch > max_legal_utf32) {
                if (flags == conv_flags::strict) {
                    result = conv_errc::source_illegal;
                } else {
                    *target++ = (replacement_char);
                }
            } else {
                /* target is a character in range 0xFFFF - 0x10FFFF. */
                ch -= half_base;
                *target++ = ((uint16_t)((ch >> half_shift) + sur_high_start));
                *target++ = ((uint16_t)((ch & half_mask) + sur_low_start));
            }
        }
        return convert_result<InputIt>{first,result} ;
    }

    template <typename InputIt,class OutputIt>
    typename std::enable_if<is_char32<typename std::iterator_traits<InputIt>::value_type>::value
                                   && is_compatible_output_iterator<OutputIt,uint32_t>::value,convert_result<InputIt>>::type 
    convert(InputIt first, InputIt last, 
            OutputIt target, 
            conv_flags flags = conv_flags::strict) 
    {
        conv_errc  result = conv_errc();

        while (first != last) 
        {
            uint32_t ch = *first++;
            if (flags == conv_flags::strict ) {
                /* UTF-16 surrogate values are illegal in UTF-32 */
                if (is_surrogate(ch)) {
                    --first; /* return to the illegal value itself */
                    result = conv_errc::illegal_surrogate_value;
                    break;
                }
            }
            if (ch <= max_legal_utf32)
            {
                *target++ = (ch);
            }
            else
            {
                *target++ = (replacement_char);
                result = conv_errc::source_illegal;
            }
        }
        return convert_result<InputIt>{first,result} ;
    }

    // validate

    template <typename InputIt>
    typename std::enable_if<is_char8<typename std::iterator_traits<InputIt>::value_type>::value
                                   ,convert_result<InputIt>>::type 
    validate(InputIt first, InputIt last) noexcept
    {
        conv_errc  result = conv_errc();
        while (first != last) 
        {
            std::size_t length = static_cast<std::size_t>(trailing_bytes_for_utf8[static_cast<uint8_t>(*first)]) + 1;
            if (length > (std::size_t)(last - first))
            {
                return convert_result<InputIt>{first, conv_errc::source_exhausted};
            }
            if ((result=is_legal_utf8(first, length)) != conv_errc())
            {
                return convert_result<InputIt>{first,result} ;
            }
            first += length;
        }
        return convert_result<InputIt>{first,result} ;
    }

    // utf16

    template <typename InputIt>
    typename std::enable_if<is_char16<typename std::iterator_traits<InputIt>::value_type>::value
                                   ,convert_result<InputIt>>::type 
    validate(InputIt first, InputIt last)  noexcept
    {
        conv_errc  result = conv_errc();

        while (first != last) 
        {
            uint32_t ch = *first++;
            /* If we have a surrogate pair, validate to uint32_t first. */
            if (is_high_surrogate(ch)) 
            {
                /* If the 16 bits following the high surrogate are in the first buffer... */
                if (first < last) {
                    uint32_t ch2 = *first;
                    /* If it's a low surrogate, */
                    if (ch2 >= sur_low_start && ch2 <= sur_low_end) {
                        ++first;
                    } else {
                        --first; /* return to the illegal value itself */
                        result = conv_errc::unpaired_high_surrogate;
                        break;
                    }
                } else { /* We don't have the 16 bits following the high surrogate. */
                    --first; /* return to the high surrogate */
                    result = conv_errc::source_exhausted;
                    break;
                }
            } else if (is_low_surrogate(ch)) 
            {
                /* UTF-16 surrogate values are illegal in UTF-32 */
                --first; /* return to the illegal value itself */
                result = conv_errc::source_illegal;
                break;
            }
        }
        return convert_result<InputIt>{first,result} ;
    }


    // utf32


    template <typename InputIt>
    typename std::enable_if<is_char32<typename std::iterator_traits<InputIt>::value_type>::value
                                   ,convert_result<InputIt>>::type 
    validate(InputIt first, InputIt last) noexcept
    {
        conv_errc  result = conv_errc();

        while (first != last) 
        {
            uint32_t ch = *first++;
            /* UTF-16 surrogate values are illegal in UTF-32 */
            if (is_surrogate(ch)) {
                --first; /* return to the illegal value itself */
                result = conv_errc::illegal_surrogate_value;
                break;
            }
            if (!(ch <= max_legal_utf32))
            {
                result = conv_errc::source_illegal;
            }
        }
        return convert_result<InputIt>{first,result} ;
    }

    // sequence 

    template <typename Iterator>
    class sequence
    {
        Iterator first_;
        std::size_t length_;
    public:
        sequence(Iterator first, std::size_t length)
            : first_(first), length_(length)
        {
        }

        Iterator begin() const
        {
            return first_;
        }

        std::size_t length() const
        {
            return length_;
        }

        template <typename CharT = typename std::iterator_traits<Iterator>::value_type>
        typename std::enable_if<is_char8<CharT>::value,uint32_t>::type 
        codepoint() const noexcept
        {
            uint32_t ch = 0;
            Iterator it = first_;
            switch (length_) 
            {
            default:
                return replacement_char;
                break;
            case 4:
                ch += static_cast<uint8_t>(*it++); ch <<= 6;
                UNICONS_FALLTHROUGH;
            case 3:
                ch += static_cast<uint8_t>(*it++); ch <<= 6;
                UNICONS_FALLTHROUGH;
            case 2:
                ch += static_cast<uint8_t>(*it++); ch <<= 6;
                UNICONS_FALLTHROUGH;
            case 1:
                ch += static_cast<uint8_t>(*it++);
                ch -= offsets_from_utf8[length_ - 1];
                break;
            }
            if (ch <= max_legal_utf32) 
            {
                if (is_surrogate(ch)) 
                {
                    ch = replacement_char;
                }
            }
            else // ch > max_legal_utf32
            {
                ch = replacement_char;
            }
            return ch;
        }

        template <typename CharT = typename std::iterator_traits<Iterator>::value_type>
        typename std::enable_if<is_char16<CharT>::value,uint32_t>::type 
        codepoint() const noexcept
        {
            if (length_ == 0)
            {
                return replacement_char;
            }
            if (length_ == 2)
            {
                uint32_t ch = *first_;
                uint32_t ch2 = *(first_+ 1);
                ch = ((ch - sur_high_start) << half_shift)
                     + (ch2 - sur_low_start) + half_base;
                return ch;
            }
            else 
            {
                return *first_;
            }
        }

        template <typename CharT = typename std::iterator_traits<Iterator>::value_type>
        typename std::enable_if<is_char32<CharT>::value,uint32_t>::type 
        codepoint() const noexcept
        {
            if (length_ == 0)
            {
                return replacement_char;
            }
            return *(first_);
        }
    };

    // sequence_generator

    template <typename Iterator>
    class sequence_generator
    {
        Iterator begin_;
        Iterator last_;
        conv_flags flags_;
        std::size_t length_;
        conv_errc err_cd_;
    public:
        using sequence_type = sequence<Iterator>;

        sequence_generator(Iterator first, Iterator last, 
                           conv_flags flags = conv_flags::strict) noexcept
            : begin_(first), last_(last), flags_(flags), 
              length_(0), err_cd_(conv_errc())
        {
            next();
        }

        bool done() const noexcept
        {
            return err_cd_ != conv_errc() || begin_ == last_;
        }

        conv_errc status() const noexcept
        {
            return err_cd_;
        }

        sequence_type get() const noexcept
        {
            return sequence<Iterator>(begin_,length_);
        }

        template <typename CharT = typename std::iterator_traits<Iterator>::value_type>
        typename std::enable_if<is_char8<CharT>::value>::type 
        next() noexcept
        {
            begin_ += length_;
            if (begin_ != last_)
            {
                std::size_t length = trailing_bytes_for_utf8[static_cast<uint8_t>(*begin_)] + 1;
                if (length > (std::size_t)(last_ - begin_))
                {
                    err_cd_ = conv_errc::source_exhausted;
                }
                else if ((err_cd_ = is_legal_utf8(begin_, length)) != conv_errc())
                {
                }
                else
                {
                    length_ = length;
                }
            }
        }

        template <typename CharT = typename std::iterator_traits<Iterator>::value_type>
        typename std::enable_if<is_char16<CharT>::value>::type 
        next() noexcept
        {
            begin_ += length_;
            if (begin_ != last_)
            {
                if (begin_ != last_)
                {

                    Iterator it = begin_;

                    uint32_t ch = *it++;
                    /* If we have a surrogate pair, validate to uint32_t it. */
                    if (is_high_surrogate(ch)) 
                    {
                        /* If the 16 bits following the high surrogate are in the it buffer... */
                        if (it < last_) {
                            uint32_t ch2 = *it;
                            /* If it's a low surrogate, */
                            if (ch2 >= sur_low_start && ch2 <= sur_low_end) 
                            {
                                ++it;
                                length_ = 2;
                            } 
                            else 
                            {
                                err_cd_ = conv_errc::unpaired_high_surrogate;
                            }
                        } 
                        else 
                        { 
                            // We don't have the 16 bits following the high surrogate.
                            err_cd_ = conv_errc::source_exhausted;
                        }
                    } 
                    else if (is_low_surrogate(ch)) 
                    {
                        /* leading low surrogate */
                        err_cd_ = conv_errc::source_illegal;
                    }
                    else
                    {
                        length_ = 1;
                    }
                }
            }
        }

        template <typename CharT = typename std::iterator_traits<Iterator>::value_type>
        typename std::enable_if<is_char32<CharT>::value>::type 
        next() noexcept
        {
            begin_ += length_;
            length_ = 1;
        }
    };

    template <typename Iterator>
    sequence_generator<Iterator> make_sequence_generator(Iterator first, Iterator last,
        conv_flags flags = conv_flags::strict)
    {
        return sequence_generator<Iterator>(first, last, flags);
    }

    template <typename InputIt>
    typename std::enable_if<(is_char8<typename std::iterator_traits<InputIt>::value_type>::value || is_char16<typename std::iterator_traits<InputIt>::value_type>::value),
                                   sequence<InputIt>>::type 
    sequence_at(InputIt first, InputIt last, std::size_t index) 
    {
        sequence_generator<InputIt> g(first, last, unicons::conv_flags::strict);

        std::size_t count = 0;
        while (!g.done() && count < index)
        {
            g.next();
            ++count;
        }
        return (!g.done() && count == index) ? g.get() : sequence<InputIt>(last,0);
    }

    template <typename InputIt>
    typename std::enable_if<is_character<typename std::iterator_traits<InputIt>::value_type>::value && is_char32<typename std::iterator_traits<InputIt>::value_type>::value,
                                   sequence<InputIt>>::type 
    sequence_at(InputIt first, InputIt last, std::size_t index) 
    {
        std::size_t size = std::distance(first,last);
        return index < size ? sequence<InputIt>(first+index,1) : sequence<InputIt>(last,0);
    }

    // codepoint_iterator

    template <typename Iter>
    class codepoint_iterator
    {
        Iter it_;
        Iter last_;
        conv_flags flags_;
        std::size_t length_;
    public:
        using iterator_type = Iter;
        using value_type = uint32_t;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = const value_type&;
        using iterator_category = std::input_iterator_tag;

        codepoint_iterator() noexcept
            : length_(0)
        {
        }

        codepoint_iterator(Iter first, Iter last, 
                           conv_flags flags = conv_flags::strict) 
            : it_(first), last_(last), flags_(flags), length_(0)
        {
            operator++();
        }

        codepoint_iterator(Iter first, Iter last, 
                           std::error_code& ec) noexcept
            : codepoint_iterator(first, last, conv_flags::strict, ec)
        {
        }

        codepoint_iterator(Iter first, Iter last, 
                           conv_flags flags, std::error_code& ec) noexcept
            : it_(first), last_(last), flags_(flags), length_(0)
        {
            increment(ec);
        }

        codepoint_iterator(const codepoint_iterator&) = default;

        codepoint_iterator(codepoint_iterator&&) = default; 

        codepoint_iterator& operator=(const codepoint_iterator&) = default;

        codepoint_iterator& operator=(codepoint_iterator&&) = default;

        constexpr iterator_type base() const noexcept
        {
            return it_;
        }

        uint32_t operator*() const noexcept
        {
            return get_codepoint();
        }

        codepoint_iterator& operator++()
        {
            std::error_code ec;
            increment(ec);
            if (ec)
            {
                UNICONS_THROW(unicode_error(ec));
            }
            return *this;
        }

        codepoint_iterator operator++(int) // postfix increment
        {
            codepoint_iterator temp(*this);
            ++(*this);
            return temp;
        }

        template <typename CharT = typename std::iterator_traits<Iter>::value_type>
        typename std::enable_if<is_char8<CharT>::value,codepoint_iterator& >::type 
        increment(std::error_code& ec) noexcept
        {
            it_ += length_;
            if (it_ != last_)
            {
                std::size_t length = trailing_bytes_for_utf8[static_cast<uint8_t>(*it_)] + 1;
                if (length > (std::size_t)(last_ - it_))
                {
                    ec = conv_errc::source_exhausted;
                }
                else
                {
                    ec = is_legal_utf8(it_, length);
                    if (!ec)
                    {
                        length_ = length;
                    }
                }
            }
            return *this;
        }

        template <typename CharT = typename std::iterator_traits<Iter>::value_type>
        typename std::enable_if<is_char16<CharT>::value,codepoint_iterator& >::type 
        increment(std::error_code& ec) noexcept
        {
            it_ += length_;
            if (it_ != last_)
            {
                if (it_ != last_)
                {

                    Iter it = it_;

                    uint32_t ch = *it++;
                    /* If we have a surrogate pair, validate to uint32_t it. */
                    if (is_high_surrogate(ch)) 
                    {
                        /* If the 16 bits following the high surrogate are in the it buffer... */
                        if (it < last_) {
                            uint32_t ch2 = *it;
                            /* If it's a low surrogate, */
                            if (ch2 >= sur_low_start && ch2 <= sur_low_end) 
                            {
                                ++it;
                                length_ = 2;
                            } 
                            else 
                            {
                                ec = conv_errc::unpaired_high_surrogate;
                            }
                        } 
                        else 
                        { 
                            // We don't have the 16 bits following the high surrogate.
                            ec = conv_errc::source_exhausted;
                        }
                    } 
                    else if (is_low_surrogate(ch)) 
                    {
                        /* leading low surrogate */
                        ec = conv_errc::source_illegal;
                    }
                    else
                    {
                        length_ = 1;
                    }
                }
            }
            return *this;
        }

        template <typename CharT = typename std::iterator_traits<Iter>::value_type>
        typename std::enable_if<is_char32<CharT>::value,codepoint_iterator& >::type 
        increment(std::error_code&) noexcept
        {
            it_ += length_;
            length_ = 1;
            return *this;
        }

        friend bool operator==(const codepoint_iterator& lhs, const codepoint_iterator& rhs) noexcept
        {
            if (rhs.is_end())
            {
                return lhs.is_end();
            }
            else
            {
                return lhs.it_ == rhs.it_;
            }
        }

        friend bool operator!=(const codepoint_iterator& lhs, const codepoint_iterator& rhs) noexcept
        {
            return !(lhs == rhs);
        }

        bool is_end() const noexcept
        {
            return length_ == 0 || it_ == last_;
        }

    private:
        template <typename CharT = typename std::iterator_traits<Iter>::value_type>
        typename std::enable_if<is_char8<CharT>::value,uint32_t>::type 
        get_codepoint() const noexcept
        {
            uint32_t ch = 0;
            Iter it = it_;
            switch (length_) 
            {
            default:
                return replacement_char;
                break;
            case 4:
                ch += static_cast<uint8_t>(*it++); ch <<= 6;
                UNICONS_FALLTHROUGH;
            case 3:
                ch += static_cast<uint8_t>(*it++); ch <<= 6;
                UNICONS_FALLTHROUGH;
            case 2:
                ch += static_cast<uint8_t>(*it++); ch <<= 6;
                UNICONS_FALLTHROUGH;
            case 1:
                ch += static_cast<uint8_t>(*it++);
                ch -= offsets_from_utf8[length_ - 1];
                break;
            }
            if (ch <= max_legal_utf32) 
            {
                if (is_surrogate(ch)) 
                {
                    ch = replacement_char;
                }
            }
            else // ch > max_legal_utf32
            {
                ch = replacement_char;
            }
            return ch;
        }

        template <typename CharT = typename std::iterator_traits<Iter>::value_type>
        typename std::enable_if<is_char16<CharT>::value,uint32_t>::type 
        get_codepoint() const noexcept
        {
            if (length_ == 0)
            {
                return replacement_char;
            }
            if (length_ == 2)
            {
                uint32_t ch = *it_;
                uint32_t ch2 = *(it_+ 1);
                ch = ((ch - sur_high_start) << half_shift)
                     + (ch2 - sur_low_start) + half_base;
                return ch;
            }
            else 
            {
                return *it_;
            }
        }

        template <typename CharT = typename std::iterator_traits<Iter>::value_type>
        typename std::enable_if<is_char32<CharT>::value,uint32_t>::type 
        get_codepoint() const noexcept
        {
            if (length_ == 0)
            {
                return replacement_char;
            }
            return *(it_);
        }

    };

    template <typename InputIt>
    inline const codepoint_iterator<InputIt>& begin(const codepoint_iterator<InputIt>& iter) noexcept { return iter; }

    template <typename InputIt>
    inline codepoint_iterator<InputIt> end(const codepoint_iterator<InputIt>&) noexcept { return codepoint_iterator<InputIt>(); }

    template <typename Iter, typename... Args>
    codepoint_iterator<Iter> make_codepoint_iterator(Iter first, Args&& ... args)
    {
        return codepoint_iterator<Iter>(first, std::forward<Args>(args)...);
    }

    template <typename Iter, typename Distance>
    void advance(codepoint_iterator<Iter>& it, Distance n, std::error_code& ec) noexcept    
    {
        for (std::size_t i = 0; !ec && i < n; ++i)
        {
            it.increment(ec);
        }
    }

    // u8_length

    template <typename InputIt>
    typename std::enable_if<is_character<typename std::iterator_traits<InputIt>::value_type>::value && is_char8<typename std::iterator_traits<InputIt>::value_type>::value,size_t>::type 
    u8_length(InputIt first, InputIt last) noexcept
    {
        return std::distance(first,last);
    }

    // utf16

    template <typename InputIt>
    typename std::enable_if<is_character<typename std::iterator_traits<InputIt>::value_type>::value && is_char16<typename std::iterator_traits<InputIt>::value_type>::value,size_t>::type 
    u8_length(InputIt first, InputIt last) noexcept
    {
        conv_flags flags = conv_flags::strict;
        std::size_t count = 0;
        for (InputIt p = first; p != last; ++p)
        {
            uint32_t ch = *p;
            if (is_high_surrogate(ch)) {
                /* If the 16 bits following the high surrogate are in the p buffer... */
                if (p < last) {
                    uint32_t ch2 = *(++p);
                    /* If it's a low surrogate, convert to uint32_t. */
                    if (ch2 >= sur_low_start && ch2 <= sur_low_end) {
                        ch = ((ch - sur_high_start) << half_shift)
                            + (ch2 - sur_low_start) + half_base;
                   
                    } else if (flags == conv_flags::strict) { /* it's an unpaired high surrogate */
                        break;
                    }
                } else { /* We don't have the 16 bits following the high surrogate. */
                    break;
                }
            } else if (flags == conv_flags::strict) {
                /* UTF-16 surrogate values are illegal in UTF-32 */
                if (is_low_surrogate(ch)) {
                    break;
                }
            }
            if (ch < (uint32_t)0x80) {      
                ++count;
            } else if (ch < (uint32_t)0x800) {     
                count += 2;
            } else if (ch < (uint32_t)0x10000) {   
                count += 3;
            } else if (ch < (uint32_t)0x110000) {  
                count += 4;
            } else {                            
                count += 3;
            }
        }
        return count;
    }


    // utf32

    template <typename InputIt>
    typename std::enable_if<is_character<typename std::iterator_traits<InputIt>::value_type>::value && is_char32<typename std::iterator_traits<InputIt>::value_type>::value,size_t>::type 
    u8_length(InputIt first, InputIt last) noexcept
    {
        std::size_t count = 0;
        for (InputIt p = first; p < last; ++p)
        {
            uint32_t ch = *p;
            if (ch < (uint32_t)0x80) {      
                ++count;
            } else if (ch < (uint32_t)0x800) {     
                count += 2;
            } else if (ch < (uint32_t)0x10000) {   
                count += 3;
            } else if (ch <= max_legal_utf32) {  
                count += 4;
            } else {                            
                count += 3;
            }
        }
        return count;
    }

    // u32_length

    template <typename InputIt>
    typename std::enable_if<(is_char8<typename std::iterator_traits<InputIt>::value_type>::value || is_char16<typename std::iterator_traits<InputIt>::value_type>::value),
                                   std::size_t>::type 
    u32_length(InputIt first, InputIt last) noexcept
    {
        sequence_generator<InputIt> g(first, last, unicons::conv_flags::strict);

        std::size_t count = 0;
        while (!g.done())
        {
            g.next();
            ++count;
        }
        return count;
    }

    template <typename InputIt>
    typename std::enable_if<is_character<typename std::iterator_traits<InputIt>::value_type>::value && is_char32<typename std::iterator_traits<InputIt>::value_type>::value,
                                   std::size_t>::type 
    u32_length(InputIt first, InputIt last) noexcept
    {
        return std::distance(first,last);
    }

    enum class encoding {u8,u16le,u16be,u32le,u32be,undetected};

    template <typename Iterator>
    struct detect_encoding_result
    {
        Iterator it;
        encoding ec;
    };

    template <typename Iterator>
    typename std::enable_if<is_character<typename std::iterator_traits<Iterator>::value_type>::value && is_char8<typename std::iterator_traits<Iterator>::value_type>::value,
                            detect_encoding_result<Iterator>>::type 
    detect_encoding(Iterator first, Iterator last) noexcept
    {
        Iterator it1 = first;
        if (std::distance(first,last) < 4)
        {
            if (std::distance(first,last) == 3)
            {
                Iterator it2 = ++first;
                Iterator it3 = ++first;
                if (static_cast<uint8_t>(*it1) == 0xEF && static_cast<uint8_t>(*it2) == 0xBB && static_cast<uint8_t>(*it3) == 0xBF)
                {
                    return detect_encoding_result<Iterator>{last,encoding::u8};
                }
            }
            return detect_encoding_result<Iterator>{it1,encoding::undetected};
        }
        else
        {
            Iterator it2 = ++first;
            Iterator it3 = ++first;
            Iterator it4 = ++first;

            uint32_t bom = static_cast<uint8_t>(*it1) | (static_cast<uint8_t>(*it2) << 8) | (static_cast<uint8_t>(*it3) << 16) | (static_cast<uint8_t>(*it4) << 24);
            if (bom == 0xFFFE0000)                  
            { 
                return detect_encoding_result<Iterator>{it4++,encoding::u32be};
            }
            else if (bom == 0x0000FEFF) 
            {
                return detect_encoding_result<Iterator>{first,encoding::u32le};
            }
            else if ((bom & 0xFFFF) == 0xFFFE)     
            {
                return detect_encoding_result<Iterator>{it3,encoding::u16be};
            }
            else if ((bom & 0xFFFF) == 0xFEFF)      
            {
                return detect_encoding_result<Iterator>{it3,encoding::u16le};
            }
            else if ((bom & 0xFFFFFF) == 0xBFBBEF)  
            {
                return detect_encoding_result<Iterator>{it4,encoding::u8};
            }
            else
            {
                uint32_t pattern = (static_cast<uint8_t>(*it1) ? 1 : 0) | (static_cast<uint8_t>(*it2) ? 2 : 0) | (static_cast<uint8_t>(*it3) ? 4 : 0) | (static_cast<uint8_t>(*it4) ? 8 : 0);
                switch (pattern) {
                case 0x08: 
                    return detect_encoding_result<Iterator>{it1,encoding::u32be};
                case 0x0A: 
                    return detect_encoding_result<Iterator>{it1,encoding::u16be};
                case 0x01: 
                    return detect_encoding_result<Iterator>{it1,encoding::u32le};
                case 0x05: 
                    return detect_encoding_result<Iterator>{it1,encoding::u16le};
                case 0x0F: 
                    return detect_encoding_result<Iterator>{it1,encoding::u8};
                default:
                    return detect_encoding_result<Iterator>{it1,encoding::undetected};
                }
            }
        }
    }

    template <typename Iterator>
    struct skip_bom_result
    {
        Iterator it;
        encoding_errc ec;
    };

    template <typename Iterator>
    typename std::enable_if<is_character<typename std::iterator_traits<Iterator>::value_type>::value && is_char8<typename std::iterator_traits<Iterator>::value_type>::value,
                                   skip_bom_result<Iterator>>::type 
    skip_bom(Iterator first, Iterator last) noexcept
    {
        auto result = unicons::detect_encoding(first,last);
        switch (result.ec)
        {
        case unicons::encoding::u8:
            return skip_bom_result<Iterator>{result.it,encoding_errc()};
            break;
        case unicons::encoding::u16le:
        case unicons::encoding::u16be:
            return skip_bom_result<Iterator>{result.it,encoding_errc::expected_u8_found_u16};
            break;
        case unicons::encoding::u32le:
        case unicons::encoding::u32be:
            return skip_bom_result<Iterator>{result.it,encoding_errc::expected_u8_found_u32};
            break;
        default:
            return skip_bom_result<Iterator>{result.it,encoding_errc()};
            break;
        }
    }

    template <typename Iterator>
    typename std::enable_if<is_character<typename std::iterator_traits<Iterator>::value_type>::value && is_char16<typename std::iterator_traits<Iterator>::value_type>::value,
                                   skip_bom_result<Iterator>>::type 
    skip_bom(Iterator first, Iterator last) noexcept
    {
        if (first == last)
        {
            return skip_bom_result<Iterator>{first,encoding_errc()};
        }
        uint16_t bom = static_cast<uint16_t>(*first);
        if (bom == 0xFEFF)                  
        {
            return skip_bom_result<Iterator>{++first,encoding_errc()};
        }
        else if (bom == 0xFFFE) 
        {
            return skip_bom_result<Iterator>{last,encoding_errc::expected_u16_found_fffe};
        }
        else
        {
            return skip_bom_result<Iterator>{first,encoding_errc()};
        }
    }

    template <typename Iterator>
    typename std::enable_if<is_character<typename std::iterator_traits<Iterator>::value_type>::value && is_char32<typename std::iterator_traits<Iterator>::value_type>::value,
                            skip_bom_result<Iterator>>::type 
    skip_bom(Iterator first, Iterator last) noexcept
    {
        if (first == last)
        {
            return skip_bom_result<Iterator>{first,encoding_errc()};
        }
        uint32_t bom = static_cast<uint32_t>(*first);
        if (bom == 0xFEFF0000)                  
        {
            return skip_bom_result<Iterator>{++first,encoding_errc()};
        }
        else if (bom == 0xFFFE0000) 
        {
            return skip_bom_result<Iterator>{last,encoding_errc::expected_u32_found_fffe};
        }
        else
        {
            return skip_bom_result<Iterator>{first,encoding_errc()};
        }
    }

} // namespace unicons

namespace std {
    template<>
    struct is_error_code_enum<unicons::encoding_errc> : public true_type
    {
    };
}

#endif

