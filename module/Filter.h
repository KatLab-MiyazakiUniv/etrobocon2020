/**
 *  @file   Filter.h
 *  @brief  外乱対策のためのフィルターをまとめたクラス
 *  @author T.Miyaji
 */
#ifndef FILTER_H
#define FILTER_H

class Filter {
 private:
  double preValue;

 public:
  Filter();
  void reset();
  double lowPassFilter(double value, double rate = 0.9);
  double complementaryFilter(double heavyValue, double lightValue, double rate = 0.94);
};

#endif
