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
      controller.tslpTsk(2000);  // 実機では4000に
    }
  } else {
    //目的位置が走行体より後方
    while(presPos > goal) {  // 目的位置にたどり着くまで後退
      controller.setLeftMotorPwm(-pwm);
      controller.setRightMotorPwm(-pwm);
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
  Color col;
  while((col = controller.getColor()) == Color::black
        || col == Color::white)  //色評価変数colが黒か白の場合は継続
  {
    controller.setLeftMotorPwm(pwm);
    controller.setRightMotorPwm(pwm);
    controller.tslpTsk(2000);  // 実機では4000に
  }
  controller.stopMotor();
}

void MoveStraight::moveTo(Color destColor, unsigned int pwm)
{
  while(controller.getColor() != destColor)  //目的の色まで達するまで継続
  {
    controller.setLeftMotorPwm(pwm);
    controller.setRightMotorPwm(pwm);
    controller.tslpTsk(2000);  // 実機では4000に
  }
  controller.stopMotor();
}