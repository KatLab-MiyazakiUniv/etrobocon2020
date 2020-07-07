#include "EtRobocon2020.h"
#include "Controller.h"
#include "Display.h"

/*
* タッチセンサーを押すと直進する
* エンターボタンを押すと止まる
* 下ボタンを押すとカラーセンサーのRGBをターミナルに表示する
*/
void EtRobocon2020::start()
{
  // Controllerクラスを使うためにインスタンス化する
  Controller controller;

  while (true)
  {
    // タッチセンサーを押すと直進する
    if (controller.touchSensor.isPressed())
    {
      controller.setLeftMotorPwm(30);
      controller.setRightMotorPwm(30);
    }

    // エンターボタンを押すと停止する
    if (controller.buttonIsPressedEnter())
    {
      controller.stopMotor();
    }

    // 下ボタンを押すとカラーセンサーのRGB値を表示する
    if (controller.buttonIsPressedDown())
    {
      rgb_raw_t rgb;
      controller.colorSensor.getRawColor(rgb);
      printf("R:%3d, G:%3d, B:%3d\n", rgb.r, rgb.g, rgb.b);
      // 走行体の画面に表示する(動かない)
      Display::print(6, "R:%3d, G:%3d, B:%3d", rgb.r, rgb.g, rgb.b);
    }

    // バックボタンを押すと終了する
    if (controller.buttonIsPressedBack())
    {
      break;
    }

    // タスク時間4０００マイクロ秒=4ミリ秒待つ while文では必要らしい
    controller.tslpTsk(4000);
  }
}
