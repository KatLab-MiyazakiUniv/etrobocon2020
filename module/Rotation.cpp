/**
 *  @file	Rotation.cpp
 *  @brief	機体を回頭するクラス
 *  @author	mutotaka0426
 */

#include "Rotation.h"

Rotation::Rotation(Controller& controller_) : Radius(50.0), distance(), controller(controller_) {}

void Rotation::run(double angle, bool clockwise, int pwm)
{
  // angleの絶対値をとる
  angle = std::abs(angle);
  Filter filter;
  controller.resetMotorCount();
  // controller.resetGyroSensor();
  //ジャイロセンサはとりあえず保留

  double motorAngle
      = this->calculate(controller.getLeftMotorCount(), controller.getRightMotorCount());
  // double gyroAngle = std::abs(static_cast<double>(controller.getAngleOfRotation()));

  // while(filter.complementaryFilter(motorAngle, gyroAngle) < angle) {
  // 指定した角度回頭するまでループ
  while(motorAngle < angle) {
    // clockwiseがtrueの場合時計回り、falseの場合反時計回り
    controller.setLeftMotorPwm(clockwise ? pwm : -pwm);
    controller.setRightMotorPwm(clockwise ? -pwm : pwm);
    controller.tslpTsk(4);

    motorAngle = this->calculate(controller.getLeftMotorCount(), controller.getRightMotorCount());
    // gyroAngle = std::abs(static_cast<double>(controller.getAngleOfRotation()));
  }
  controller.stopMotor();
}

double Rotation::calculate(const int leftAngle, const int rightAngle)
{
  //両輪の回転角から回頭角度を取得（資料は準備中）
  const double transform = 2.0 * Radius / Tread;
  double arc = distance.getDistance(std::abs(leftAngle), std::abs(rightAngle));

  return transform * arc;
}
