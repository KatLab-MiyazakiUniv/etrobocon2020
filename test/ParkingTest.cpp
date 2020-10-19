/**
 *  @file   ParkingTest.cpp
 *  @brief  ガレージ駐車クラスの単体テストコード
 *  @author Takahiro55555
 */
#include "Controller.h"
#include "Parking.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {
  TEST(Parking, parkInGarage)
  {
    constexpr bool isLeftCourse = true;
    constexpr int targetBrightness = (255 - 0) / 2;
    Controller controller;

    // インスタンス生成
    Parking parking(isLeftCourse, controller, targetBrightness);

    // 駐車
    // NOTE: Linetracer.runTo???() や Movestraight.moveTo() などをモックの Controller
    //      使用して呼び出すとき、 Controler.tslpTsk() から std::exti(1) が実行される。
    //      したがって、Linetracer.runTo???() や Movestraight.moveTo() が
    //      呼ばれた部分以降のコードは実行されない。
    //      そのため、Parking.parkInGarage()のカバレッジは 100% にならない点に注意すること。
    ASSERT_EXIT(parking.parkInGarage(), ::testing::ExitedWithCode(1), "");
  }
}  // namespace etrobocon2020_test
