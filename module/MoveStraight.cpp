/**
 *  @file   MoveStraight.cpp
 *  @brief  直線移動するクラス
 *  @author T.Yoshino
 **/
#include "MoveStraight.h"

MoveStraight::MoveStraight(Controller* cont_ptr_) : cont_ptr(cont_ptr_) {}

void MoveStraight::moveto(int destination)
{
  static int prev;  //
  int pres = odometer.getDistance(cont_ptr->getLeftMotorCount(), cont_ptr->getRightMotorCount());

  static bool toggle = 0;

  if(toggle == 0) {
    prev = odometer.getDistance(cont_ptr->getLeftMotorCount(), cont_ptr->getRightMotorCount());
    toggle = 1;
  }

  if((destination > 0) ? (pres - prev < destination)
                       : (pres + prev > destination)) {  //変位と行き先を比較
    cont_ptr->setLeftMotorPwm((destination > 0) ? 30 : -30);
    cont_ptr->setRightMotorPwm((destination > 0) ? 30 : -30);

  } else {
    cont_ptr->stopMotor();
    cont_ptr->resetMotorCount();
    cont_ptr->tslpTsk(1000000);
    toggle = 0;
  }
}