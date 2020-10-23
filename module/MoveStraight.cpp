/**
 *  @file   MoveStraight.cpp
 *  @brief  直線移動するクラス
 *  @author T.Yoshino
 **/
#include "MoveStraight.h"

MoveStraight::MoveStraight(Controller& controller_)
  : controller(controller_), odometer(), curvature(0.0, 2.5, 1.8, 0.0)
{
}

void MoveStraight::moveTo(int destination, unsigned int maxPwm)
{
  int presPos = 0;
  int correction = 0;  // 曲率PIDによる補正値
  int currentPwm = 0;

  controller.resetMotorCount();

  if(destination > 0) {             // 目的位置が走行体より前方
    while(presPos < destination) {  // 目的位置にたどり着くまで前進
      currentPwm = calcPwm(presPos, destination, maxPwm);
      // correction = static_cast<int>(
      //    curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount()));

      // printf("currentPwm:%d correction:%d\n", currentPwm, correction);
      controller.setLeftMotorPwm(currentPwm + correction);
      controller.setRightMotorPwm(currentPwm - correction);

      presPos
          = odometer.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

      controller.tslpTsk(2000);  // 実機では4000に
    }
  } else {
    //目的位置が走行体より後方
    while(presPos > destination) {  // 目的位置にたどり着くまで後退
      currentPwm = calcPwm(presPos, destination, maxPwm);
      // correction
      //    = curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount());

      controller.setLeftMotorPwm(-(currentPwm + correction));
      controller.setRightMotorPwm(-(currentPwm - correction));

      presPos
          = odometer.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

      controller.tslpTsk(2000);  // 実機では4000に
    }
  }
  // 目的位置に到着
  controller.stopMotor();
  // ブレーキをかける
}

void MoveStraight::moveWhileBW(unsigned int pwm)
{
  int correction = 0;  // 曲率PIDによる補正値
  Color col;

  while((col = controller.getColor()) == Color::black
        || col == Color::white)  //色評価変数colが黒か白の場合は継続
  {
    correction = curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount());
    controller.setLeftMotorPwm(pwm + correction);
    controller.setRightMotorPwm(pwm - correction);
    controller.tslpTsk(2000);  // 実機では4000に
  }
  controller.stopMotor();
}

void MoveStraight::moveTo(Color destColor, unsigned int pwm)
{
  int correction = 0;  // 曲率PIDによる補正値

  while(controller.getColor() != destColor)  //目的の色まで達するまで継続
  {
    correction = curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount());
    controller.setLeftMotorPwm(pwm + correction);
    controller.setRightMotorPwm(pwm - correction);
    controller.tslpTsk(2000);  // 実機では4000に
  }
  controller.stopMotor();
}

int MoveStraight::calcPwm(int presPos, int destination, int maxPwm)
{
  int minPwm = 10;
  int pwm = 10;
  constexpr int changePwm = 10;
  constexpr float changeDis = 30.0;
  const float a = changePwm / changeDis;
  if(maxPwm < minPwm) minPwm = maxPwm;

  if(presPos < destination / 2) {
    // y = ax + b
    pwm = a * presPos + minPwm;
  } else {
    // y = -ax + b
    pwm = -a * presPos + (a * destination + minPwm);
  }

  if(pwm < minPwm) {
    pwm = minPwm;
  } else if(pwm > maxPwm) {
    pwm = maxPwm;
  }
  return pwm;
}
