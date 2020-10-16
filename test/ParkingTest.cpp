/**
 *  @file   ParkingTest.cpp
 *  @brief  ガレージ駐車クラスの単体テストコード
 *  @author Takahiro55555
 */
#include "Controller.h"
#include "Parking.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {
    TEST(Parking, construct) {
        constexpr bool isLeftCourse = true;
        constexpr int targetBrightness = (255 - 0) / 2;
        Controller controller;

        // インスタンス生成
        Parking parking(isLeftCourse, controller, targetBrightness);
    }

    TEST(Parking, parkInGarage) {
        constexpr bool isLeftCourse = true;
        constexpr int targetBrightness = (255 - 0) / 2;
        Controller controller;

        // インスタンス生成
        Parking parking(isLeftCourse, controller, targetBrightness);
        
        // 駐車
        parking.parkInGarage();
    }
}
