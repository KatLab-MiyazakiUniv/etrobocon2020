/**
 *  @file   MoveStraight.h
 *  @brief  直進、後退するクラス
 *  @author T.Yoshino
 **/
#ifndef MOVESTRAIGHT_H
#define MOVESTRAIGHT_H

#define _USE_MATH_DEFINES
#include "Controller.h"
#include "Distance.h"
#include <cmath>

class MoveStraight {
 public:
  /**
   * コンストラクタ
   * @brief MoveStraightクラスのコンストラクタ
   */
  MoveStraight(Controller* cont_ptr_);
  /**
   * 任意の距離だけ直線移動する
   *
   * @brief
   * @param destination 行き先（mm, 正で前進・負で後退）
   * @param pwm モーター出力
   */
  void moveto(int destination, unsigned int pwm = 30);

 private:
  Distance odometer;     // 距離計
  Controller* cont_ptr;  // Controllerクラスポインタ
};

#endif