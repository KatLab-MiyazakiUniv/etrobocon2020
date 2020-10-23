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
  double targetMotorCount = calculate(angle);
  int LeftPwm, RightPwm;  // タイヤのモーターパワー(回頭角度に応じて減衰していく)
  double leftCountRate, rightCountRate;  //現在のタイヤの回転比率[0.0~1.0]
  controller.resetMotorCount();

  // 両輪が止まるまでループ
  while(leftSign != 0 || rightSign != 0) {
    leftCountRate = 1 - abs(controller.getLeftMotorCount()) / targetMotorCount;
    rightCountRate = 1 - abs(controller.getRightMotorCount()) / targetMotorCount;
    LeftPwm
        = pwm * leftCountRate > minPwm ? (int)(pwm * leftCountRate * leftSign) : minPwm * leftSign;
    RightPwm = pwm * rightCountRate > minPwm ? (int)(pwm * rightCountRate * rightSign)
                                             : minPwm * rightSign;

    controller.setLeftMotorPwm(LeftPwm);
    controller.setRightMotorPwm(RightPwm);
    controller.tslpTsk(4000);

    if(abs(controller.getLeftMotorCount()) >= targetMotorCount) {
      leftSign = 0;
    }
    if(abs(controller.getRightMotorCount()) >= targetMotorCount) {
      rightSign = 0;
    }
  }
  controller.stopMotor();
}

void Rotation::pivotTurn(double angle, bool clockwise, int pwm)
{
  int left_pwm = clockwise ? pwm : 0;
  int right_pwm = clockwise ? 0 : pwm;
  this->run(angle, left_pwm, right_pwm);
}

void Rotation::pivotTurnBack(double angle, bool clockwise, int pwm)
{
  int left_pwm = clockwise ? 0 : -pwm;
  int right_pwm = clockwise ? -pwm : 0;
  this->run(angle, left_pwm, right_pwm);
}

double Rotation::calculate(int angle)
{
  // @see docs/Odometry/odometry.pdf
  const double transform = 2.0 * Radius / Tread;
  return angle / transform;
}
