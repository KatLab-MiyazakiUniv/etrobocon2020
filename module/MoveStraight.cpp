/**
 *  @file   MoveStraight.cpp
 *  @brief  直線移動するクラス
 *  @author T.Yoshino
 **/
#include "MoveStraight.h"

MoveStraight::MoveStraight(Controller& controller_)
  : controller(controller_), odometer(), curvature(0.0, 4.0, 1.0, 0.0)
{
}

void MoveStraight::moveTo(int destination, unsigned int maxPwm)
{
  controller.resetMotorCount();

  int presPos = 0;
  int correction = 0;  // 曲率PIDによる補正値
  int currentPwm = 0;

  if(destination > 0) {             // 目的位置が走行体より前方
    while(presPos < destination) {  // 目的位置にたどり着くまで前進
      currentPwm = calcPwm(presPos, destination, maxPwm);
      correction
          = curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount());

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
      correction
          = curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount());

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
  if(maxPwm < minPwm) minPwm = maxPwm;

  // 上に凸の放物線の方程式より、走行距離に応じてpwmを計算する。放物線は、次の点を通る。
  // (0, minPwm) (destination/2, maxPwm) (destination, minPwm)
  double pwm = 4 * (minPwm - maxPwm) * (presPos - destination / 2) * (presPos - destination / 2);
  pwm = pwm / (destination * destination) + maxPwm;

  return static_cast<int>(pwm);
}
