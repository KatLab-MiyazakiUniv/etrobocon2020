/**
 *  @file   BlockBingoTest.cpp
 *  @brief  BlockBingoのテストファイル
 *  @author mutotaka0426
 */
#include "BlockBingo.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {

  TEST(Filter, init_cross_circle)
  {
    BlockBingo blockBingo;
    CrossCircle cross_circle;
    int x, y;
    int expected;

    // 色の異常時判定
    x = 0, y = 0;
    Block block = { Color::red, -1 };
    cross_circle = { Color::none, block };
    expected = 0;
    ASSERT_NE(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // 色の異常時判定
    x = 0, y = 0;
    cross_circle = CrossCircle{ Color::black, Block{ Color::red, -1 } };
    expected = 0;
    ASSERT_NE(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // 正常時（ブロック番号なし、XY座標境界値）
    x = 0, y = 0;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, -1 } };
    expected = 0 ASSERT_EQ(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // 正常時（ブロック番号境界値、XY座標境界値）
    x = 3, y = 3;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, 1 } };
    expected = 0 ASSERT_EQ(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // 正常時（ブロック番号境界値）
    x = 0, y = 0;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, 8 } };
    expected = 0 ASSERT_EQ(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // 座標異常時（指定したx座標が範囲外）
    x = 4, y = 2;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, 4 } };
    expected = 0;
    ASSERT_NE(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // 座標異常時（指定したy座標が範囲外）
    x = 2, y = 4;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, 4 } };
    expected = 0;
    ASSERT_NE(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // 座標異常時（指定したx座標が範囲外）
    x = -1, y = 2;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, 4 } };
    expected = 0;
    ASSERT_NE(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // 座標異常時（指定したy座標が範囲外）
    x = 2, y = -1;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, 4 } };
    expected = 0;
    ASSERT_NE(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // ブロック番号異常時（境界値01）
    x = 2, y = 2;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, 0 } };
    expected = 0;
    ASSERT_NE(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // ブロック番号異常時（境界値02）
    x = 2, y = 2;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, -2 } };
    expected = 0;
    ASSERT_NE(expected, blockBingo.init_cross_circle(x, y, cross_circle));

    // ブロック番号異常時（境界値03）
    x = 2, y = 2;
    cross_circle = CrossCircle{ Color::red, Block{ Color::red, 9 } };
    expected = 0;
    ASSERT_NE(expected, blockBingo.init_cross_circle(x, y, cross_circle));
  }

  TEST(BlockBingo, get_block_circle)
  {
    BlockBingo blockBingo;

    Color expected_block_circle_color = Color::red;
    Color expected_block_color = Color::blue;
    int expected_block_number = 5;
    int expected_circle_number = 6;

    int x = 1, y = 2;
    BlockCircle expected = { expected_block_circle_color,
                             { expected_block_color, expected_block_number },
                             expected_circle_number };
    blockBingo.init_block_circle(x, y, expected);

    BlockCircle block_circle = blockBingo.get_block_circle(x, y);

    ASSERT_EQ(expected_block_circle_color, block_circle.block_circle_color);
    ASSERT_EQ(expected_block_color, block_circle.block.block_color);
    ASSERT_EQ(expected_block_number, block_circle.block.block_number);
    ASSERT_EQ(expected_circle_number, block_circle.circle_number);
  }

  TEST(BlockBingo, get_cross_circle)
  {
    BlockBingo blockBingo;

    Color expected_cross_circle_color = Color::red;
    Color expected_block_color = Color::blue;
    int expected_block_number = 5;

    int x = 1, y = 2;
    CrossCircle expected
        = { expected_cross_circle_color, { expected_block_color, expected_block_number } };
    blockBingo.init_cross_circle(x, y, expected);

    CrossCircle cross_circle = blockBingo.get_cross_circle(x, y);

    ASSERT_EQ(expected_cross_circle_color, cross_circle.cross_circle_color);
    ASSERT_EQ(expected_block_color, cross_circle.block.block_color);
    ASSERT_EQ(expected_block_number, cross_circle.block.block_number);
  }
}  // namespace etrobocon2020_test
