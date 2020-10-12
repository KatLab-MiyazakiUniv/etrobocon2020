/**
 *  @file	Rotation.h
 *  @brief	走行体を回頭するクラス
 *  @author	mutotaka0426
 */

#include "Rotation.h"

using namespace std;

Rotation::Rotation(Controller& controller_) : distance(), controller(controller_) {}

void Rotation::rotate(int angle, bool clockwise, int pwm)
{
  // angleの絶対値をとる
  angle = abs(angle);
  int leftSign = clockwise ? 1 : -1;
  int rightSign = clockwise ? -1 : 1;
  double targetAngle = calculate(angle);
  int LeftPwm, RightPwm;  // タイヤのモーターパワー(回頭角度に応じて減衰していく)
  double leftAngleRate, rightAngleRate;  //現在のタイヤの回転比率[0.0~1.0]
  controller.resetMotorCount();

  // 両輪が止まるまでループ
  while(leftSign != 0 || rightSign != 0) {
    leftAngleRate = 1 - abs(controller.getLeftMotorCount()) / targetAngle;
    rightAngleRate = 1 - abs(controller.getRightMotorCount()) / targetAngle;
    LeftPwm
        = pwm * leftAngleRate > minPwm ? (int)(pwm * leftAngleRate * leftSign) : minPwm * leftSign;
    RightPwm = pwm * rightAngleRate > minPwm ? (int)(pwm * rightAngleRate * rightSign)
                                             : minPwm * rightSign;

    controller.setLeftMotorPwm(LeftPwm);
    controller.setRightMotorPwm(RightPwm);
    controller.tslpTsk(4000);

    if(abs(controller.getLeftMotorCount()) >= targetAngle) {
      leftSign = 0;
    }
    if(abs(controller.getRightMotorCount()) >= targetAngle) {
      rightSign = 0;
    }
  }
  controller.stopMotor();
}

double Rotation::calculate(int Angle)
{
  // @see docs/Odometry/odometry.pdf
  const double transform = 2.0 * Radius / Tread;
  return Angle / transform;
}
