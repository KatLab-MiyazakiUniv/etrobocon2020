/**
 *  @file   Filter.h
 *  @brief  外乱対策のためのフィルターをまとめたクラス
 *  @author T.Miyaji
 */
#ifndef FILTER_H
#define FILTER_H

#define rotateFunc 0
#define pivotTurnFunc 1
#define pivotTurnBackFunc 2
struct rotationFilterData {
  //以下の4つの補正値を基準にしてrotationFilterの補正値を求める
  double Phalf_Ahalf;  // モーターパワー50で90度回転するときの補正値
  double Phalf_Amax;   // モーターパワー50で180度回転するときの補正値
  double Pmax_Ahalf;   // モーターパワー100で90度回転するときの補正値
  double Pmax_Amax;    // モーターパワー100で180度回転するときの補正値
};

class Filter {
 private:
  double preValue;
  rotationFilterData filterData = { 1, 1, 1, 1 };

 public:
  Filter();
  void reset();
  double lowPassFilter(double value, double rate = 0.9);
  double complementaryFilter(double heavyValue, double lightValue, double rate = 0.94);

  void rotationFilterSet(int funcName, bool clockwise);
  double rotationFilter(double Angle, double targetAngle, int pwm);
};

#endif
