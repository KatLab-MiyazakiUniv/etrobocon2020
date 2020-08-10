/**
 *  @file	Rotation.cpp
 *  @brief	走行体を回頭するクラス
 *  @author	mutotaka0426
 */
#ifndef ROTATION_H
#define ROTATION_H

#include "Distance.h"
#include "Filter.h"
#include <cmath>

class Rotation {
 private:
  const double Radius;                    //車輪の半径[mm]
  static constexpr double Tread = 128.0;  //走行体のトレッド幅（両輪の間の距離）[mm]
  Distance distance;
  Controller& controller;

 public:
  /**　コンストラクタ
   *   @param controller_  [Controller]
   */
  Rotation(Controller& controller_);

  /**
   *  @brief 走行体を回頭させる
   *  @param angle [回頭角度]
   *  @param clockwise [回転方向(Trueが時計回り)]
   *  @param pwm [モーターパワー]
   */
  void run(double angle, bool clockwise, int pwm = 7);

  /**
   *  @brief 回頭したときの角度を求める
   *  @param leftAngle [左車輪の回頭角度[deg]]
   *  @param rightAngle [右車輪の回頭角度[deg]]
   *  @return 自転角度(回転方向に関わらず正の数)
   */
  double calculate(const int leftAngle, const int rightAngle);
};

#endif
