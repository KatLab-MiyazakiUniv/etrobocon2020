#include "../module/EtRobocon2020.h" // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2020_test
{

    class EtRobocon2020Test : public ::testing::Test
    {
        friend class EtRobocon2020;

    protected:
        virtual void SetUp() {}
        EtRobocon2020 et;
    };

    TEST_F(EtRobocon2020Test, startTest) {}
} // namespace etrobocon2020_test