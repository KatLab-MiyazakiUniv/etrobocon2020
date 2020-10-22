/**
 *  @file   MoveStraight.h
 *  @brief  直進、後退するクラス
 *  @author T.Yoshino
 **/
#ifndef MOVESTRAIGHT_H
#define MOVESTRAIGHT_H

#define _USE_MATH_DEFINES
#include "Controller.h"
#include "Curvature.h"
#include "Distance.h"
#include <cmath>

class MoveStraight {
 public:
  /**
   * @brief MoveStraightクラスのコンストラクタ
   */

  MoveStraight(Controller& controller_);
  /**
   * @brief 任意の距離だけ直線移動する
   * @param destination 移動距離（mm, 正で前進・負で後退）
   * @param maxPwm モータ出力の最大値
   */
  void moveTo(int destination, unsigned int maxPwm = 30);

  /**
   * @brief 白黒以外まで直進する
   * @param pwm モータ出力
   */
  void moveWhileBW(unsigned int pwm = 30);

  /**
   * @brief 任意の色まで直進する
   * @param destColor 直進して目指す色
   * @param pwm モータ出力
   */
  void moveTo(Color destColor, unsigned int pwm = 30);

 private:
  Controller& controller;  // 参照型Controllerクラス
  Curvature curvature;
  Distance odometer;  // 距離計
  /**
   * @brief 放物線の方程式から、走行距離に応じてminPwm→maxPwm→minPwmとなるようなpwm値を計算する
   * @param presPos     現在位置
   * @param destination 移動距離
   * @param maxPwm      モータ出力の最大値
   */
  int calcPwm(int presPos, int destination, int maxPwm);
};

#endif
