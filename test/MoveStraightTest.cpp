#include "MoveStraight.h"
#include "Controller.h"
#include "Distance.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {
  TEST(MoveStraight, construct)
  {
    Controller controller;
    MoveStraight gear(controller);
  }

  TEST(MoveStraight, advance)
  {
    Controller controller;
    Distance odometer;
    MoveStraight gear(controller);

    int prevPos
        = odometer.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    int presPos;

    gear.moveTo(100);

    presPos = odometer.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    // test prevPos+100 < presPos < prevPos+105
    ASSERT_LE(prevPos + 100, presPos);
    ASSERT_GE(prevPos + 105, presPos);
  }

  TEST(MoveStraight, reverse)
  {
    Controller controller;
    Distance odometer;
    MoveStraight gear(controller);

    int prevPos
        = odometer.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    int presPos;

    gear.moveTo(-100);

    presPos = odometer.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    // test prevPos-105 < presPos < prevPos-100
    ASSERT_GE(prevPos - 100, presPos);
    ASSERT_LE(prevPos - 100 - 5, presPos);
  }
}  // namespace etrobocon2020_test
