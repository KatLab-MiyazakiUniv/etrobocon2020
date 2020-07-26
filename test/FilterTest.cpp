/**
 *  @file   FilterTest.cpp
 *  @brief  フィルタークラスのテストファイル
 *  @author T.Miyaji
 */
#include "Filter.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {

  TEST(Filter, lowPassFilterTest_init)
  {
    Filter filter;
    double sensor = 24.0;

    // 前回のセンサー値がない場合は、入力値をそのまま返す
    ASSERT_DOUBLE_EQ(sensor, filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilterTest_reset)
  {
    Filter filter;
    double sensor = 10.0;

    // 前回値の初期化
    filter.lowPassFilter(sensor);
    filter.lowPassFilter(sensor);

    filter.reset();
    ASSERT_DOUBLE_EQ(sensor, filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilterTest_filter)
  {
    Filter filter;
    double preSensor = 24.0;

    // フィルターを初期化する
    filter.lowPassFilter(preSensor);

    // 期待出力の計算
    double sensor = 77.0;
    double expected = preSensor * 0.9 + sensor * 0.1;
    // フィルターをかける
    ASSERT_DOUBLE_EQ(expected, filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilter_update)
  {
    Filter filter;
    double init = 10.0;

    // フィルターの初期化
    ASSERT_DOUBLE_EQ(init, filter.lowPassFilter(init));

    // 期待出力の計算
    double preSensor = 20.0;
    double expected = init * 0.9 + preSensor * 0.1;
    // フィルターをかける
    ASSERT_DOUBLE_EQ(expected, filter.lowPassFilter(preSensor));

    // 期待出力の計算
    double sensor = 30.0;
    double expected2 = preSensor * 0.9 + sensor * 0.1;
    // フィルターをかける(前回値の更新あり)
    ASSERT_DOUBLE_EQ(expected2, filter.lowPassFilter(sensor));
  }
}  // namespace etrobocon2020_test
