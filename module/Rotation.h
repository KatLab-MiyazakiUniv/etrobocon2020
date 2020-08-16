/**
 *  @file	Rotation.h
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
  static constexpr double Tread = 140.0;  //走行体のトレッド幅（両輪の間の距離）[mm]
  Distance distance;
  Filter filter;
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
  void rotate(double angle, bool clockwise, int pwm = 50);

  /**
   *  @brief 走行体を軸足回転させる
   *  @param angle [軸足回転角度]
   *  @param clockwise [回転方向(Trueが時計回り)]
   *  @param pwm [モーターパワー]
   */
  void pivotTurn(double angle, bool clockwise, int pwm = 30);

  /**
   *  @brief 走行体をバックで軸足回転させる
   *  @param angle [軸足回転角度]
   *  @param clockwise [回転方向(Trueが時計回り)]
   *  @param pwm [モーターパワー]
   */
  void pivotTurnBack(double angle, bool clockwise, int pwm = 30);

  /**
   *  @brief 走行体を指定されたように回転させる
   *  @param angle [回転角度]
   *  @param left_pwm [左車輪のモーターパワー]
   *  @param right_pwm [右車輪のモーターパワー]
   */
  void run(double angle, double left_pwm, double right_pwm);

  /**
   *  @brief 回転したときの角度を求める
   *  @param leftAngle [左車輪の回頭角度[deg]]
   *  @param rightAngle [右車輪の回頭角度[deg]]
   *  @return 回転角度(回転方向に関わらず正の数)
   */
  double calculate(const int leftAngle, const int rightAngle);
};

#endif
