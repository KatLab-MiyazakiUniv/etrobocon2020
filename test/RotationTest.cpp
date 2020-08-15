/**
 *  @file   RotationTest.cpp
 *  @brief  Rotationクラスのテストファイル
 *  @author mutotaka0426
 */
#include "Rotation.h"
#include "Controller.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {
  TEST(Rotation, calculate)
  {
    Controller controller;
    Rotation rotation(controller);
    const double Radius = 45.0;
    static constexpr double Tread = 140.0;
    double wheelAngle = 30;

    double expected = 2.0 * Radius * wheelAngle / Tread;

    ASSERT_DOUBLE_EQ(expected, rotation.calculate(30, -30));
    ASSERT_DOUBLE_EQ(expected, rotation.calculate(-30, 30));
  }

  TEST(Rotation, rotate)
  {
    Controller controller;
    Rotation rotation(controller);
    Filter filter;

    double expected = 90;
    bool clockwise = true;
    rotation.rotate(expected, clockwise);

    filter.rotationFilterSet(rotateFunc, clockwise);
    double actual = filter.rotationFilter(
        rotation.calculate(controller.getLeftMotorCount(), controller.getRightMotorCount()),
        expected, 50);

    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5, actual);
  }

  TEST(Rotation, pivotTurn)
  {
    Controller controller;
    Rotation rotation(controller);
    Filter filter;

    double expected = 90;
    bool clockwise = true;
    rotation.pivotTurn(expected, clockwise);

    filter.rotationFilterSet(pivotTurnFunc, clockwise);
    double actual = filter.rotationFilter(
        rotation.calculate(controller.getLeftMotorCount(), controller.getRightMotorCount()),
        expected, 50);

    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5, actual);
  }

  TEST(Rotation, pivotTurnBack)
  {
    Controller controller;
    Rotation rotation(controller);
    Filter filter;

    double expected = 90;
    bool clockwise = true;
    rotation.pivotTurnBack(expected, clockwise);

    filter.rotationFilterSet(pivotTurnBackFunc, clockwise);
    double actual = filter.rotationFilter(
        rotation.calculate(controller.getLeftMotorCount(), controller.getRightMotorCount()),
        expected, 50);

    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5, actual);
  }
}  // namespace etrobocon2020_test
