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
  int leftPwm, rightPwm;  // タイヤのモーターパワー(回頭角度に応じて減衰していく)
  double leftCountRate, rightCountRate;  //現在のタイヤの回転比率[0.0~1.0]
  controller.resetMotorCount();

  // 両輪が止まるまでループ
  while(leftSign != 0 || rightSign != 0) {
    leftCountRate = 1 - abs(controller.getLeftMotorCount()) / targetMotorCount;
    rightCountRate = 1 - abs(controller.getRightMotorCount()) / targetMotorCount;
    leftPwm
        = pwm * leftCountRate > minPwm ? (int)(pwm * leftCountRate * leftSign) : minPwm * leftSign;
    rightPwm = pwm * rightCountRate > minPwm ? (int)(pwm * rightCountRate * rightSign)
                                             : minPwm * rightSign;

    controller.setLeftMotorPwm(leftPwm);
    controller.setRightMotorPwm(rightPwm);
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

void Rotation::pivotTurn(int angle, bool clockwise, int pwm)
{
  // angleの絶対値をとる
  angle = abs(angle);
  int leftPwm = clockwise ? pwm : -1;
  int rightPwm = clockwise ? -1 : pwm;
  double targetMotorCount = calculate(angle);
  pivotTurnRun(angle, leftPwm, rightPwm, targetMotorCount);
}

void Rotation::pivotTurnBack(int angle, bool clockwise, int pwm)
{
  // angleの絶対値をとる
  angle = abs(angle);
  int leftPwm = clockwise ? 1 : -pwm;
  int rightPwm = clockwise ? -pwm : 1;
  double targetMotorCount = calculate(angle);
  pivotTurnRun(angle, leftPwm, rightPwm, targetMotorCount);
}

void Rotation::pivotTurnRun(int angle, int leftPwm, int rightPwm, int targetMotorCount)
{
  // angleの絶対値をとる
  int motorCountAve = 0;
  controller.resetMotorCount();

  // 両輪が止まるまでループ
  while(motorCountAve < targetMotorCount) {
    controller.setLeftMotorPwm(leftPwm);
    controller.setRightMotorPwm(rightPwm);
    controller.tslpTsk(4000);

    printf("left:%d, right:%d\n", controller.getLeftMotorCount(), controller.getRightMotorCount());
    motorCountAve
        = (abs(controller.getLeftMotorCount()) + abs(controller.getRightMotorCount())) / 2;
  }
  controller.stopMotor();
}

double Rotation::calculate(int angle)
{
  // @see docs/Odometry/odometry.pdf
  const double transform = 2.0 * Radius / Tread;
  return angle / transform;
}
