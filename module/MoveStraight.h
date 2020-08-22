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
  MoveStraight(Controller& controller_);
  /**
   * 任意の距離だけ直線移動する
   *
   * @brief
   * @param destination 移動距離（mm, 正で前進・負で後退）
   * @param pwm モーター出力
   */
  void moveTo(int destination, unsigned int pwm = 30);

 private:
  Distance odometer;       // 距離計
  Controller& controller;  // 参照型Controllerクラス
};

#endif  