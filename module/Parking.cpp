/**
 *  @file   Parking.cpp
 *  @brief  ガレージ駐車クラス
 *  @author Takahiro55555, mutotaka0426
 **/

#include "Parking.h"

Parking::Parking(bool isLeftCourse_, Controller& controller_, int targetBrightness_)
  : isLeftCourse(isLeftCourse_), controller(controller_), targetBrightness(targetBrightness_)
{
}

void Parking::parkInGarage()
{
  MoveStraight movestraight(controller);
  Rotation rotation(controller);
  LineTracer linetracer(controller, targetBrightness, isLeftCourse);
  movestraight.moveTo(Color::black, 30);
  rotation.rotate(90, isLeftCourse);
  controller.resetMotorCount();
  linetracer.runToColor(20, 0.15, 0.0, 0.005, 0.0);
  linetracer.runToSpecifiedColor(Color::black, 20, 0.15, 0.0, 0.005, 0.0);
  linetracer.runToSpecifiedColor(Color::white, 20, 0.15, 0.0, 0.005, 0.0);
  movestraight.moveTo(300);
}
