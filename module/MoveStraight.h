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

#define THROTTLE_WHILE_BW 30  //黒白以外まで直進するときのモータ出力
#define THROTTLE_MOVETO_X 30  //任意の色まで直進するときのモータ出力

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

  /**
   * 白黒以外まで直進する
   *
   * @brief
   */
  void moveWhileBW();

  /**
   * 任意の色まで直進する
   *
   * @brief オーバーロードしてみた
   */
  void moveTo(Color destColor);

 private:
  Distance odometer;       // 距離計
  Controller& controller;  // 参照型Controllerクラス
};

#endif