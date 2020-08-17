/**
 *  @file   NavigatorTest.cpp
 *  @brief  Navigatorクラスのテストファイル
 *  @author sugaken0528
 */

#include "Navigator.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {
  TEST(Navigator, Navigator_init)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 90;
    // Leftコースである場合True
    bool isLeftCourse = true;
    // カラーセンサーの目標値
    int targetBrightnessExpected = 90;
    Navigator Navigator(controller, isLeftCourse, targetBrightness);
    ASSERT_TRUE(Navigator.getIsLeftCourse());
    ASSERT_EQ(targetBrightnessExpected, Navigator.getTargetBrightness());
  }

  //エッジの切替メソッドのテスト
  TEST(Navigator, setIsLeftCourse)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 100;
    // Leftコースである場合True
    bool isLeftCourse = false;
    Navigator Navigator(controller, isLeftCourse, targetBrightness);
    Navigator.setIsLeftCourse(true);
    ASSERT_TRUE(Navigator.getIsLeftCourse());
  }

  // セットしたエッジを返すゲッター
  TEST(Navigator, getIsLeftCourse)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 100;
    // Leftコースである場合True
    bool isLeftCourse = false;
    Navigator Navigator(controller, isLeftCourse, targetBrightness);
    ASSERT_FALSE(Navigator.getIsLeftCourse());
  }

  // セットした目標のカラーセンサ値を返すゲッター
  TEST(Navigator, getTargetBrightness)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 600;
    // Leftコースである場合True
    bool isLeftCourse = true;
    // 期待される出力
    int expected = 600;
    Navigator Navigator(controller, isLeftCourse, targetBrightness);
    ASSERT_EQ(expected, Navigator.getTargetBrightness());
  }
}  // namespace etrobocon2020_test
