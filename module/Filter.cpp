/**
 *  @file   Filter.cpp
 *  @brief  外乱対策のためのフィルターをまとめたクラス
 *  @author T.Miyaji
 */
#include "Filter.h"

Filter::Filter() : preValue(0) {}

void Filter::reset()
{
  preValue = 0;
}

/**
 *  [Filter::lowPassFilter]
 *  @brief  ローパスフィルター(現在値と前回値を参考にして値を決定する)
 *  @param  value [現在の値]
 *  @param  rate  [前回値を参考にする割合]
 *  @return       [フィルター後の値]
 */
double Filter::lowPassFilter(double value, double rate)
{
  // 前回値の初期化
  if(preValue == 0) {
    preValue = value;
    return static_cast<double>(value);
  }

  double filtered = preValue * rate + value * (1 - rate);
  // 前回値の更新
  preValue = value;

  return filtered;
}

double Filter::complementaryFilter(double heavyValue, double lightValue, double rate)
{
  return rate * heavyValue + (1 - rate) * lightValue;
}
