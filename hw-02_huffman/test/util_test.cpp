#include "doctest.h"
#include "util.h"

TEST_CASE("convert_to_char tests")
{
    SUBCASE("String's length is less than 8") {
        CHECK_EQ(convert_to_char("0101"), 'P');
        CHECK_EQ(convert_to_char("011011"), 'l');
        CHECK_EQ(convert_to_char("010"), '@');
    }
    SUBCASE("String's length is equal to 8") {
        CHECK_EQ(convert_to_char("00101010"), '*');
        CHECK_EQ(convert_to_char("01101101"), 'm');
        CHECK_EQ(convert_to_char("01111011"), '{');
    }
}