#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ev3api.h"

#include "Clock.h"
#include "ColorSensor.h"
#include "Motor.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
#include "etroboc_ext.h"

struct HsvStatus {
  //色相 範囲(0~360)
  double hue;
  //彩度 範囲(0~100)
  double saturation;
  //明度 範囲(0~100)
  double value;
};

enum class Color { black, red, green, blue, yellow, white, none };

using namespace ev3api;

class Controller {
 public:
  Controller();
  TouchSensor touchSensor;
  ColorSensor colorSensor;
  Clock clock;
  GyroSensor gyroSensor;
  // モータ入力電圧の最大値
  static constexpr int MOTOR_PWM_MAX = 100;
  // モータ入力電圧の最小値
  static constexpr int MOTOR_PWM_MIN = -100;

  // 白色のデフォルト値
  rgb_raw_t standardWhite;
  // 黒色のデフォルト値
  rgb_raw_t standardBlack;

  void speakerSetVolume(int volume);
  void ledSetColorOrange();
  void ledSetColorGreen();
  int getBrightness();
  static void speakerPlayToneFS6(int duration);
  bool buttonIsPressedBack();
  bool buttonIsPressedUp();
  bool buttonIsPressedDown();
  bool buttonIsPressedRight();
  bool buttonIsPressedLeft();
  bool buttonIsPressedEnter();
  static float getBatteryVoltage();
  static void tslpTsk(int time = 10000);  // 引数はマイクロ秒で指定する
  void getRawColor(int& r, int& g, int& b);
  void convertHsv(int& r, int& g, int& b);  // RGBをHSV変換する
  HsvStatus getHsv() const;
  Color hsvToColor(const HsvStatus& status);  // HSVから色を識別する
  static void lcdFillRect(int x, int y, int h);
  static void lcdDrawString(const char* str, int x, int y);
  static void lcdSetFont();
  int getLeftMotorCount();
  int getRightMotorCount();
  int getArmMotorCount();
  int getTargetBrightness();
  void setTargetBrightness(int brightness_);
  void setLeftMotorPwm(const int pwm);
  void setRightMotorPwm(const int pwm);
  void setArmMotorPwm(const int pwm);
  void setStandardWhite(const rgb_raw_t& rgb);
  void setStandardBlack(const rgb_raw_t& rgb);
  void resetMotorCount();
  void stopMotor();
  int getAngleOfRotation();
  Color getColor();
  void resetGyroSensor();
  int getAmp();
  int getVolt();

  /**
   * アームを動かす
   * @brief countが正の場合、アームを上げる。countが負の場合、アームを下げる。
   * @param count
   * [カラーセンサーが地面に対して垂直に向いている状態をcount=0としたとき、countの最大値が約40、最小値が約-20]
   * @param pwm [モーターパワー]
   */
  void moveArm(int count, int pwm = 45);
  void resetArmMotorCount();
  void stopLiftMotor();
  void steer(int power, int turnRatio);

  // シミュレータ用拡張API
  /**
   * @brief   コース情報の取得
   * @param   コース情報取得関数用ID
   * @return  指定されたidの情報
   * @note    https://github.com/ETrobocon/etrobo/wiki/sim_extended_api
   */
  int getCourseInfo(ETROBOC_COURSE_INFO_ID id);

  /**
   * @brief アームを水平にする
   */
  void keepArm(void);

  /**
   * @brief   競技終了通知をシミュレータに送信する
   */
  void notifyCompleted(void);

 private:
  int targetBrightness = 127;
  HsvStatus hsv;
  Motor liftMotor;
  Motor rightWheel;
  Motor leftWheel;
  Motor tailMotor;

  // static int suppressPwmValue(const int value);
  int suppressPwmValue(const int value);
};
#endif
