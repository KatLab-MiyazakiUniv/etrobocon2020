/**
 *  @file   EtRobocon2020.cpp
 *  @brief  全体を制御するクラス
 *  @author Arima Kaoru
 **/

#include "EtRobocon2020.h"
#include "Controller.h"
#include "NormalCourse.h"
#include "BlockBingo.h"
#include "Parking.h"

void EtRobocon2020::start()
{
  // コースを設定(Lコース:ture, Rコース:false)
  constexpr bool isLeftCourse = false;
  // 白黒の基準値として実測値を設定
  constexpr rgb_raw_t standardWhite = { 124, 118, 167 };
  constexpr rgb_raw_t standardBlack = { 4, 5, 8 };
  // 明るさの目標値を設定
  constexpr int targetBrightness = (255 - 0) / 2;

  Controller controller;
  controller.setStandardWhite(standardWhite);
  controller.setStandardBlack(standardBlack);

  // タッチセンサーが押されるまで待機
  while(!controller.touchSensor.isPressed()) {
    controller.tslpTsk();
  }

  // ノーマルコースの走行開始
  NormalCourse normalCourse(controller, isLeftCourse, targetBrightness);
  normalCourse.runNormalCourse();

  // ビンゴエリアの攻略開始
  BlockBingo blockBingo(controller, isLeftCourse);
  blockBingo.runBlockBingo();

  // ガレージ駐車開始
  Parking parking(isLeftCourse, controller, targetBrightness);
  parking.parkInGarage();

  controller.tslpTsk(5000000);

  // 競技終了通知を送信する
  controller.notifyCompleted();
}
