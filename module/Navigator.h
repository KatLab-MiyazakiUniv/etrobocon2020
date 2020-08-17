/**
 *  @file  Navigator.h
 *  @brief ビンゴエリアを走る
 *  @author sugaken0528
 *  updated by T.Miyaji
 */

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "LineTracer.h"
#include <array>

class Navigator {
 public:
  /**
   * コンストラクタ
   *
   * @brief Navigatorクラスのコンストラクタ
   * @param &controller_ [Controllerインスタンスの参照]
   * @param isLeftCourse_ [エッジがどっちかtrueがLeftコース]
   * @param targetBrightness_ [黒と白の閾値]
   */
  Navigator(Controller& controller_, bool isLeftCourse_, int targetBrightness_);

  /**
   * 実際にビンゴエリアを走る．
   */
  void traceBingoArea(bool isRightEdge);

 private:
  Controller& controller;
  bool isLeftCourse;
  int targetBrightness;
};

#endif
