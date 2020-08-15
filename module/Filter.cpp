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

void Filter::rotationFilterSet(int fancName, bool clockwise)
{
  //回頭の時の基準値をセット
  if(fancName == rotateFunc) {
    if(clockwise)
      filterData = { 1.2453, 1.128, 1.538, 1.237 };  //時計回り
    else
      filterData = { 1.1748, 1.097, 1.368, 1.17 };  //反時計回り
    //ピボットターン(前)の時の基準値をセット
  } else if(fancName == pivotTurnFunc) {
    if(clockwise)
      filterData = { 1.0, 1.0, 0.96, 1.01 };  //時計回り
    else
      filterData = { 0.98, 1.0, 0.98, 0.98 };  //反時計回り
    //ピボットターン(後)の時の基準値をセット
  } else if(fancName == pivotTurnBackFunc) {
    if(clockwise)
      filterData = { 1.01, 0.97, 1.053, 1.06 };  //時計回り
    else
      filterData = { 1.033, 0.98, 1.08, 1.075 };  //反時計回り
  }
}

double Filter::rotationFilter(double Angle, double targetAngle, int pwm)
{
  double filterValue = filterData.Phalf_Ahalf
                       + (filterData.Pmax_Ahalf - filterData.Phalf_Ahalf) * (pwm - 50) / 50
                       - (filterData.Phalf_Ahalf - filterData.Phalf_Amax) * (targetAngle - 90) / 90
                       - ((filterData.Pmax_Ahalf - filterData.Pmax_Amax)
                          - (filterData.Phalf_Ahalf - filterData.Phalf_Amax))
                             * (pwm - 50) / 50 * (targetAngle - 90) / 90;
  return filterValue * Angle;
}
