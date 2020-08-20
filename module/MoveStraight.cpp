/**
 *  @file   MoveStraight.cpp
 *  @brief  直線移動するクラス
 *  @author T.Yoshino
 **/
#include "MoveStraight.h"

MoveStraight::MoveStraight(Controller& controller_) : controller(controller_) {}

void MoveStraight::moveTo(int destination, unsigned int pwm)
{
  // 現在の位置
  int presPos
      = odometer.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

  // 目的位置
  int goal = presPos + destination;

  if(destination > 0) {      // 目的位置が走行体より前方
    while(presPos < goal) {  // 目的位置にたどり着くまで前進
      controller.setLeftMotorPwm(pwm);
      controller.setRightMotorPwm(pwm);
      presPos
          = odometer.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
      controller.tslpTsk(4000);
    }
  } else {
    //目的位置が走行体より後方
    while(presPos > goal + BACK_BIAS) {  // 目的位置にたどり着くまで後退 (BIASは補正値)
      controller.setLeftMotorPwm(-pwm);
      controller.setRightMotorPwm(-pwm);
      presPos
          = odometer.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
      controller.tslpTsk(4000);
    }
  }
  // 目的位置に到着
  controller.stopMotor();
  // ブレーキをかける
}
