#include <gtest/gtest.h>
#include "IpV4.h"

TEST(tests_IpV4, full) {
    // Assert
    const char* str ="192.168.1.1" ;
    IpV4 ip(str);
    ASSERT_STREQ(ip.getString().c_str(), str);
    ASSERT_EQ(ip.getValue(0), 192);
    ASSERT_EQ(ip.getValue(1), 168);
    ASSERT_EQ(ip.getValue(2), 1);
    ASSERT_EQ(ip.getValue(3), 1);
    ASSERT_FALSE(IpV4::greater(IpV4{str}, IpV4{str}));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}