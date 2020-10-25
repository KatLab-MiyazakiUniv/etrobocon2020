/**
 *  @file	Rotation.h
 *  @brief	走行体を回頭するクラス
 *  @author	mutotaka0426
 */
#ifndef ROTATION_H
#define ROTATION_H

#include "Distance.h"
#include <cmath>

class Rotation {
 private:
  Distance distance;
  Controller& controller;
  static constexpr double Radius = 45.0;  //車輪の半径[mm]
  static constexpr double Tread = 140.0;  //走行体のトレッド幅（両輪の間の距離）[mm]
  static constexpr int minPwm = 10;       // モーターパワーの最小値

  void run(int pwm, int leftSign, int rightSign, double targetMotorCount);

  /**
   *  @brief 指定角度回頭したときの片輪の回転角度を計算する
   *  @param Angle [走行体が回頭する角度[deg]]
   *  @return 片輪の回転角度(回転方向に関わらず正の数)
   */
  double calculate(int angle);

  /**
   *  @brief 実際にピボットターンをする
   *  @param Angle [走行体が回転する角度[deg]]
   *  @param leftPwm [左輪のモーターパワー]
   *  @param rightPwm [右輪のモーターパワー]
   *  @param targetMotorCount [タイヤが回る角度]
   */
  void pivotTurnRun(int angle, int leftPwm, int rightPwm, int targetMotorCount);

 public:
  /**　コンストラクタ
   *   @param controller_  [Controller]
   */
  Rotation(Controller& controller_);

  /**
   *  @brief 走行体を回頭させる
   *  @param angle [回頭角度]
   *  @param clockwise [回転方向(Trueが時計回り)]
   *  @param pwm [モーターパワー(PWMの最大値）]
   */
  void rotate(int angle, bool clockwise, int pwm = 100);

  /**
   *  @brief 走行体をピボットターンさせる
   *  @param angle [回頭角度]
   *  @param clockwise [回転方向(Trueが時計回り)]
   *  @param pwm [モーターパワー]
   */
  void pivotTurn(int angle, bool clockwise, int pwm = 50);

  /**
   *  @brief 走行体をピボットターン（バック）させる
   *  @param angle [回頭角度]
   *  @param clockwise [回転方向(Trueが時計回り)]
   *  @param pwm [モーターパワー]
   */
  void pivotTurnBack(int angle, bool clockwise, int pwm = 50);

  /**
   *  @brief アームを上げながら走行体をピボットターンさせる
   *  @param angle [回頭角度]
   *  @param clockwise [回転方向(Trueが時計回り)]
   *  @param pwm [モーターパワー]
   */
  void pivotTurnArm(int angle, bool clockwise, int pwm = 50);
};
#endif
