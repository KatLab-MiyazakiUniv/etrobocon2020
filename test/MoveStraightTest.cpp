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

    ASSERT_LE(prevPos + 100, presPos);
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

    ASSERT_GE(prevPos - 100, presPos);
  }
}  // namespace etrobocon2020_test
