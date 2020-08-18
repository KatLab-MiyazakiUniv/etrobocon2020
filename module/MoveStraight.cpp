/**
 *  @file   MoveStraight.cpp
 *  @brief  直線移動するクラス
 *  @author T.Yoshino
 **/
#include "MoveStraight.h"

MoveStraight::MoveStraight(Controller* cont_ptr_) : cont_ptr(cont_ptr_) {}

void MoveStraight::moveto(int destination, unsigned int pwm)
{
  //現在の位置
  int presPos = odometer.getDistance(cont_ptr->getLeftMotorCount(), cont_ptr->getRightMotorCount());

  //目的位置
  int goal = presPos + destination;

  if(destination > 0) {      //目的位置が走行体より前方
    while(presPos < goal) {  //目的位置にたどり着くまで前進
      cont_ptr->setLeftMotorPwm(pwm);
      cont_ptr->setRightMotorPwm(pwm);
      presPos = odometer.getDistance(cont_ptr->getLeftMotorCount(), cont_ptr->getRightMotorCount());
      cont_ptr->tslpTsk(4000);
    }
  } else {
    　  //目的位置が走行体より後方
        while(presPos > goal)
    {
      　  //目的位置にたどり着くまで後退
          cont_ptr->setLeftMotorPwm(-pwm);
      cont_ptr->setRightMotorPwm(-pwm);
      presPos = odometer.getDistance(cont_ptr->getLeftMotorCount(), cont_ptr->getRightMotorCount());
      cont_ptr->tslpTsk(4000);
    }
  }
  //目的位置に到着
  cont_ptr->stopMotor();
  　  //ブレーキをかける
}