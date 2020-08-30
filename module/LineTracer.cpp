/**
 *  @file   LineTracer.cpp
 *  @brief  ライントレースを行うクラス
 *  @author Takahiro55555
 */

#include "LineTracer.h"

LineTracer::LineTracer(Controller& controller_, int targetBrightness_, bool isLeftCourse_)
  : controller(controller_),
    targetBrightness(targetBrightness_),
    isLeftCourse(isLeftCourse_),
    distance(),
    turnControl(targetBrightness_, 0.0, 0.0, 0.0)
{
}

void LineTracer::run(const NormalCourseProperty& settings)
{
  printf("LineTracer:run\n");

  // 関数呼び出し時の走行距離を取得・設定
  int initialDistance
      = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

  int currentDistance = initialDistance;  // 現在の走行距離
  int turnValue = 0;                      // 旋回値
  int speedValue = 0;                     // 直進値
  int leftPWM = 0;                        // 左モータの出力
  int rightPWM = 0;                       // 右モータの出力

  // 目標距離を走り終えるまでループ
  while(currentDistance - initialDistance < settings.targetDistance) {
    // 前進値の計算
    speedValue = settings.targetSpeed;

    // 旋回値の計算
    turnValue = calculateTurnValue(speedValue, settings.curvature, settings.turnPid.Kp,
                                   settings.turnPid.Ki, settings.turnPid.Kd);

    // モータ出力の計算
    if(isLeftCourse) {
      // Leftコースの場合
      leftPWM = speedValue + turnValue;
      rightPWM = speedValue - turnValue;
    } else {
      // Rightコースの場合
      leftPWM = speedValue - turnValue;
      rightPWM = speedValue + turnValue;
    }
    // PWM値の設定
    controller.setLeftMotorPwm(leftPWM);
    controller.setRightMotorPwm(rightPWM);

    // 現在の走行距離の取得
    currentDistance
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    controller.tslpTsk(4000);
  }
}

void LineTracer::setTargetBrightness(int targetBrightness_)
{
  targetBrightness = targetBrightness_;
}

int LineTracer::calculateTurnValue(int speedValue, double curvatureValue, double pGain,
                                   double iGain, double dGain, double curvaturePGain,
                                   double curvatureIGain, double curvatureDGain)
{
  int turnValue = 0;  // 旋回値
  Curvature curvature(curvatureValue, curvaturePGain, curvatureIGain,
                      curvatureDGain);                // 曲率PID制御
  constexpr double baseSpeedRate = 436.332313 / 100;  // PWM100で436.332313mm/secとしたときの速度比

  // カラーセンサー値を用いたPID制御
  turnValue = turnControl.calculateTurn(speedValue, controller.getBrightness(), targetBrightness,
                                        pGain, iGain, dGain);

  // 曲率PID制御による旋回値の計算
  turnValue += curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount(),
                                 baseSpeedRate * speedValue);

  return turnValue;
}

void LineTracer::runToColor(int targetSpeed, double pGain, double iGain, double dGain,
                            double curvatureValue = 0.0)
{
  int turnValue = 0;   // 旋回値
  int speedValue = 0;  // 直進値
  int leftPWM = 0;     // 左モータの出力
  int rightPWM = 0;    // 右モータの出力
  Color currentColor = controller.getColor();

  // 現在のラインの色が黒、または白の間ループ
  while(currentColor == Color::black || currentColor == Color::white) {
    // 前進値の計算
    speedValue = targetSpeed;

    // 旋回値の計算
    turnValue = calculateTurnValue(speedValue, curvatureValue, pGain, iGain, dGain);

    // モータ出力の計算
    if(isLeftCourse) {
      // Leftコースの場合
      leftPWM = speedValue + turnValue;
      rightPWM = speedValue - turnValue;
    } else {
      // Rightコースの場合
      leftPWM = speedValue - turnValue;
      rightPWM = speedValue + turnValue;
    }
    // PWM値の設定
    controller.setLeftMotorPwm(leftPWM);
    controller.setRightMotorPwm(rightPWM);

    // 現在のラインの色の取得
    currentColor = controller.getColor();

    controller.tslpTsk(4000);
  }
}

void LineTracer::runToSpecifiedColor(Color targetColor, int targetSpeed, double pGain, double iGain,
                                     double dGain, double curvatureValue = 0.0)
{
  int turnValue = 0;                           // 旋回値
  int speedValue = 0;                          // 直進値
  int leftPWM = 0;                             // 左モータの出力
  int rightPWM = 0;                            // 右モータの出力
  Color currentColor = controller.getColor();  //現在のラインの色を取得

  // 現在のラインの色が指定された色でない間ループ
  while(currentColor != targetColor) {
    // 前進値の計算
    speedValue = targetSpeed;

    // 旋回値の計算
    turnValue = calculateTurnValue(speedValue, curvatureValue, pGain, iGain, dGain);

    // モータ出力の計算
    if(isLeftCourse) {
      // Leftコースの場合
      leftPWM = speedValue + turnValue;
      rightPWM = speedValue - turnValue;
    } else {
      // Rightコースの場合
      leftPWM = speedValue - turnValue;
      rightPWM = speedValue + turnValue;
    }
    // PWM値の設定
    controller.setLeftMotorPwm(leftPWM);
    controller.setRightMotorPwm(rightPWM);

    // 現在のラインの色の取得
    currentColor = controller.getColor();

    controller.tslpTsk(4000);
  }
}