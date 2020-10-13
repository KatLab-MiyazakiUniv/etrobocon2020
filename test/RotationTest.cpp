/**
 *  @file   RotationTest.cpp
 *  @brief  Rotationクラスのテストファイル
 *  @author mutotaka0426
 */
#include "Rotation.h"
#include "Controller.h"
#include <gtest/gtest.h>

using namespace std;

namespace etrobocon2020_test {
  TEST(Rotation, rotate)
  {
    constexpr double Radius = 45.0;
    constexpr double Tread = 140.0;
    const double transform = 2.0 * Radius / Tread;

    Controller controller;
    Rotation rotation(controller);
    double expected, actual;
    double motorAngle;
    bool clockwise;

    // 45度右回頭の回頭誤差が１度未満かテスト
    expected = 45;
    clockwise = true;
    rotation.rotate(expected, clockwise);
    motorAngle = (abs(controller.getLeftMotorCount()) + abs(controller.getRightMotorCount())) / 2;
    actual = transform * motorAngle;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 1.0, actual);

    // 45度左回頭の回頭誤差が１度未満かテスト
    expected = 45;
    clockwise = false;
    rotation.rotate(expected, clockwise);
    motorAngle = (abs(controller.getLeftMotorCount()) + abs(controller.getRightMotorCount())) / 2;
    actual = transform * motorAngle;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 1.0, actual);

    // 90度右回頭の回頭誤差が１度未満かテスト
    expected = 90;
    clockwise = true;
    rotation.rotate(expected, clockwise);
    motorAngle = (abs(controller.getLeftMotorCount()) + abs(controller.getRightMotorCount())) / 2;
    actual = transform * motorAngle;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 1.0, actual);

    // 90度左回頭の回頭誤差が１度未満かテスト
    expected = 90;
    clockwise = false;
    rotation.rotate(expected, clockwise);
    motorAngle = (abs(controller.getLeftMotorCount()) + abs(controller.getRightMotorCount())) / 2;
    actual = transform * motorAngle;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 1.0, actual);

    // // 180度右回頭の回頭誤差が１度未満かテスト
    expected = 180;
    clockwise = true;
    rotation.rotate(expected, clockwise);
    motorAngle = (abs(controller.getLeftMotorCount()) + abs(controller.getRightMotorCount())) / 2;
    actual = transform * motorAngle;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 1.0, actual);

    // 180度左回頭の回頭誤差が１度未満かテスト
    expected = 180;
    clockwise = false;
    rotation.rotate(expected, clockwise);
    motorAngle = (abs(controller.getLeftMotorCount()) + abs(controller.getRightMotorCount())) / 2;
    actual = transform * motorAngle;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 1.0, actual);
  }

}  // namespace etrobocon2020_test
