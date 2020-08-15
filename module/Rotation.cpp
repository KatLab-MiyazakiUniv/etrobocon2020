/**
 *  @file	Rotation.h
 *  @brief	走行体を回頭するクラス
 *  @author	mutotaka0426
 */

#include "Rotation.h"

Rotation::Rotation(Controller& controller_)
  : Radius(45.0), distance(), filter(), controller(controller_)
{
}

void Rotation::rotate(double angle, bool clockwise, int pwm)
{
  double left_pwm = clockwise ? pwm : -pwm;
  double right_pwm = clockwise ? -pwm : pwm;
  filter.rotationFilterSet(rotateFunc, clockwise);
  this->run(angle, left_pwm, right_pwm);
}

void Rotation::pivotTurn(double angle, bool clockwise, int pwm)
{
  int left_pwm = clockwise ? pwm : 0;
  int right_pwm = clockwise ? 0 : pwm;
  filter.rotationFilterSet(pivotTurnFunc, clockwise);
  this->run(angle, left_pwm, right_pwm);
}

void Rotation::pivotTurnBack(double angle, bool clockwise, int pwm)
{
  int left_pwm = clockwise ? 0 : -pwm;
  int right_pwm = clockwise ? -pwm : 0;
  filter.rotationFilterSet(pivotTurnBackFunc, clockwise);
  this->run(angle, left_pwm, right_pwm);
}

void Rotation::run(double angle, double left_pwm, double right_pwm)
{
  // angleの絶対値をとる
  angle = std::abs(angle);
  int pwm = std::abs(left_pwm) > std::abs(right_pwm) ? std::abs(left_pwm) : std::abs(right_pwm);
  controller.resetMotorCount();

  double motorAngle
      = this->calculate(controller.getLeftMotorCount(), controller.getRightMotorCount());

  // 指定した角度回転するまでループ
  while(filter.rotationFilter(motorAngle, angle, pwm) < angle) {
    controller.setLeftMotorPwm(left_pwm);
    controller.setRightMotorPwm(right_pwm);
    controller.tslpTsk(4);

    motorAngle = this->calculate(controller.getLeftMotorCount(), controller.getRightMotorCount());
  }
  controller.stopMotor();
}

double Rotation::calculate(const int leftAngle, const int rightAngle)
{
  // 両輪の回転角から回転角度を取得
  // @see docs/Odometry/odometry.pdf
  const double transform = 2.0 * Radius / Tread;
  double WheelAngle = (std::abs(leftAngle) + std::abs(rightAngle)) / 2;
  return transform * WheelAngle;
}
