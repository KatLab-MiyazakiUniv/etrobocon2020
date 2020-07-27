#include "app.h"
#include "EtRobocon2020.h"
// #include "Bluetooth.h"
#include "Controller.h"
// #include "Logger.h"
// #include "Distance.h"
// #include <array>
#include <cmath>

// 演習用のユーティリティ
// std::array<char, 256> Bluetooth::commands = {'#'};
// bool Bluetooth::is_start = false;

/**
 * メインタスク
 */
// tag::main_task_1[]
void main_task(intptr_t unused)
{
  // int debug_counts = 0;
  // while(1) {
  //   Display::print(1, "%d", debug_counts);
  //   tslp_tsk(1000);
  //   debug_counts++;
  // }
  EtRobocon2020::start();
  ext_tsk();
}
// end::main_task_2[]

void localization_task(intptr_t unused)
{
  //   Controller controller;
  //   Logger log("local.csv");
  //   Distance distance;

  //   int leftOld = 0;
  //   int rightOld = 0;
  //   double x = 0.0;
  //   double y = 0.0;
  //   double theta = 0.0;
  //   constexpr double Tread = 130.0;  // トレッド幅

  //   while(true) {
  //     int left = controller.getLeftMotorCount();
  //     int right = controller.getRightMotorCount();
  //     // 走行体の速度を算出
  //     double velocity = distance.getDistance(left - leftOld, right - rightOld);
  //     // 走行体の旋回角度を算出
  //     double omega = ((right - rightOld) - (left - leftOld)) / Tread;

  //     x += velocity * std::cos(theta + (omega / 2.0));  // x座標
  //     y += velocity * std::sin(theta + (omega / 2.0));  // y座標
  //     theta += omega;

  //     log << left    // 左モーターの回転量
  //         << right   // 右モーターの回転量
  //         << x       // x座標
  //         << y       // y座標
  //         << theta;  // 姿勢（角度）

  //     leftOld = left;
  //     rightOld = right;
  //     controller.tslpTsk(4);
  //   }
  ext_tsk();
}
