/**
 *  @file   EtRobocon2020.cpp
 *  @brief  全体を制御するクラス
 *  @author Arima Kaoru
 **/

#include "EtRobocon2020.h"
#include "Controller.h"
#include "NormalCourse.h"

void EtRobocon2020::start()
{
  // コースを設定(Lコース:ture, Rコース:false)
  constexpr bool isLeftCourse = true;
  // 白黒の基準値として実測値を設定
  const rgb_raw_t standardWhite = { 7, 7, 12 };
  const rgb_raw_t standardBlack = { 126, 120, 166 };
  // 光センサーの目標値を設定
  constexpr double targetBrightness = (255 - 0) / 2.0;

  Controller controller;
  controller.setStandardWhite(standardWhite);
  controller.setStandardBlack(standardBlack);

  // タッチセンサーが押されるまで待機
  while(!controller.touchSensor.isPressed()) {
    controller.tslpTsk(4000);
  }

  // ノーマルコースの走行開始
  NormalCourse normalCourse(controller, isLeftCourse, targetBrightness);
  normalCourse.runNormalCourse();
}
