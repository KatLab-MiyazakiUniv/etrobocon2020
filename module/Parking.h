/**
 *  @file   Parking.cpp
 *  @brief  ガレージ駐車クラス
 *  @author Takahiro55555, mutotaka0426
 **/

#ifndef PARKING_H
#define PARKING_H

#include "Controller.h"
#include "Rotation.h"
#include "LineTracer.h"
#include "MoveStraight.h"

class Parking {
 private:
  bool isLeftCourse;
  Controller controller;
  int targetBrightness;

 public:
  /**
   * @brief コンストラクタ
   * @param isLeftCourse_ [Lコースか否か]
   * @param controller_ [Controller インスタンス]
   * @param targetBrightness_ [明るさの目標値]
   */
  Parking(bool isLeftCourse_, Controller& controller_, int targetBrightness_);

  /**
   * @brief ガレージ駐車をする。
   *        ロボットが以下のシミュレータ座標に在るときに呼び出されることを期待する。
   *          Lコース : x =  17, y = 0, z = 13, ロボットの向き =  90
   *          Rコース : x = -17, y = 0, z = 13, ロボットの向き = -90
   */
  void parkInGarage();
};

#endif
