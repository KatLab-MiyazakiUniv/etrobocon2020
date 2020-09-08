/**
 *  @file   BlockBingoDataTest.cpp
 *  @brief  BlockBingoDataのテストファイル
 *  @author mutotaka0BingoNumber::four26,sugaken0528,Takahiro55555
 */
#include "BlockBingoData.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {

  TEST(BlockBingoData, setBlockCircle)
  {
    BlockBingoData blockBingoData;
    BlockCircle blockCircle;
    int x, y;

    // ブロックサークルの色の異常時判定(black)
    x = 0, y = 0;
    blockCircle
        = BlockCircle{ Color::black, BingoNumber::one, Block{ Color::red, BingoNumber::none } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(x, y, blockCircle));

    // ブロックサークルの色の異常時判定(white)
    x = 0, y = 0;
    blockCircle
        = BlockCircle{ Color::white, BingoNumber::one, Block{ Color::red, BingoNumber::none } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(x, y, blockCircle));

    // 正常時（XY座標境界値1）
    x = 0, y = 0;
    blockCircle
        = BlockCircle{ Color::red, BingoNumber::one, Block{ Color::red, BingoNumber::none } };
    ASSERT_TRUE(blockBingoData.setBlockCircle(x, y, blockCircle));

    // 正常時(XY座標境界値2）
    x = 2, y = 2;
    blockCircle
        = BlockCircle{ Color::red, BingoNumber::one, Block{ Color::red, BingoNumber::none } };
    ASSERT_TRUE(blockBingoData.setBlockCircle(x, y, blockCircle));

    // 座標異常時（指定したx座標が範囲外）
    x = 3, y = 0;
    blockCircle
        = BlockCircle{ Color::red, BingoNumber::one, Block{ Color::red, BingoNumber::four } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(x, y, blockCircle));

    // 座標異常時（指定したy座標が範囲外）
    x = 0, y = 3;
    blockCircle
        = BlockCircle{ Color::red, BingoNumber::one, Block{ Color::red, BingoNumber::four } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(x, y, blockCircle));

    // 座標異常時（指定したx座標が範囲外）
    x = -1, y = 2;
    blockCircle
        = BlockCircle{ Color::red, BingoNumber::one, Block{ Color::red, BingoNumber::four } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(x, y, blockCircle));

    // 座標異常時（指定したy座標が範囲外）
    x = 2, y = -1;
    blockCircle
        = BlockCircle{ Color::red, BingoNumber::one, Block{ Color::red, BingoNumber::four } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(x, y, blockCircle));

    // ブロックカラー異常時
    x = 2, y = 2;
    blockCircle
        = BlockCircle{ Color::red, BingoNumber::one, Block{ Color::white, BingoNumber::none } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(x, y, blockCircle));
  }

  TEST(BlockBingoData, setCrossCircle)
  {
    BlockBingoData blockBingoData;
    CrossCircle crossCircle;
    int x, y;

    //交点サークルの色の異常時判定(none)
    x = 0, y = 0;
    crossCircle = CrossCircle{ Color::none, Block{ Color::red, BingoNumber::none } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(x, y, crossCircle));

    // 交点サークルの色の異常時判定(black)
    x = 0, y = 0;
    crossCircle = CrossCircle{ Color::black, Block{ Color::red, BingoNumber::none } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(x, y, crossCircle));

    // 交点サークルの色の異常時判定(white)
    x = 0, y = 0;
    crossCircle = CrossCircle{ Color::white, Block{ Color::red, BingoNumber::none } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(x, y, crossCircle));

    // 正常時（XY座標境界値1）
    x = 0, y = 0;
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, BingoNumber::none } };
    ASSERT_TRUE(blockBingoData.setCrossCircle(x, y, crossCircle));

    // 正常時（XY座標境界値2）
    x = 3, y = 3;
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, BingoNumber::none } };
    ASSERT_TRUE(blockBingoData.setCrossCircle(x, y, crossCircle));

    // 座標異常時（指定したx座標が範囲外）
    x = 4, y = 2;
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, BingoNumber::four } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(x, y, crossCircle));

    // 座標異常時（指定したy座標が範囲外）
    x = 2, y = 4;
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, BingoNumber::four } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(x, y, crossCircle));

    // 座標異常時（指定したx座標が範囲外）
    x = -1, y = 2;
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, BingoNumber::four } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(x, y, crossCircle));

    // 座標異常時（指定したy座標が範囲外）
    x = 2, y = -1;
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, BingoNumber::four } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(x, y, crossCircle));

    // ブロックカラー異常時
    x = 2, y = 2;
    crossCircle = CrossCircle{ Color::red, Block{ Color::white, BingoNumber::none } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(x, y, crossCircle));
  }

  TEST(BlockBingoData, getBlockCircle)
  {
    BlockBingoData blockBingoData;

    Color expectedBlockCircleColor = Color::red;
    Color expectedBlockColor = Color::blue;
    BingoNumber expectedBlockNumber = BingoNumber::five;
    BingoNumber expectedCircleNumber = BingoNumber::six;

    int x = 1, y = 2;
    BlockCircle expected = { expectedBlockCircleColor,
                             expectedCircleNumber,
                             { expectedBlockColor, expectedBlockNumber } };
    blockBingoData.setBlockCircle(x, y, expected);

    BlockCircle blockCircle = blockBingoData.getBlockCircle(x, y);

    ASSERT_EQ(expectedBlockCircleColor, blockCircle.blockCircleColor);
    ASSERT_EQ(expectedBlockColor, blockCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, blockCircle.block.blockNumber);
    ASSERT_EQ(expectedCircleNumber, blockCircle.circleNumber);
  }

  TEST(BlockBingoData, getCrossCircle)
  {
    BlockBingoData blockBingoData;

    Color expectedCrossCircleColor = Color::red;
    Color expectedBlockColor = Color::blue;
    BingoNumber expectedBlockNumber = BingoNumber::five;

    int x = 1, y = 2;
    CrossCircle expected
        = { expectedCrossCircleColor, { expectedBlockColor, expectedBlockNumber } };
    blockBingoData.setCrossCircle(x, y, expected);

    CrossCircle crossCircle = blockBingoData.getCrossCircle(x, y);

    ASSERT_EQ(expectedCrossCircleColor, crossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, crossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, crossCircle.block.blockNumber);
  }

  TEST(BlockBingoData, cardNumber)
  {
    BlockBingoData blockBingoData;

    BingoNumber expected = BingoNumber::three;
    blockBingoData.setCardNumber(expected);

    ASSERT_EQ(expected, blockBingoData.getCardNumber());
  }

  TEST(BlockBingoData, getCircleColorL)
  {
    BlockBingoData blockBingoData;

    BingoNumber circleNumber = BingoNumber::six;
    Color expected = Color::green;
    ASSERT_EQ(expected, blockBingoData.getBlockCircleColorL(circleNumber));

    int x = 0, y = 0;
    expected = Color::red;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorL(x, y));

    x = 3, y = 1;
    expected = Color::blue;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorL(x, y));

    x = 1, y = 3;
    expected = Color::yellow;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorL(x, y));

    x = 2, y = 2;
    expected = Color::green;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorL(x, y));

    // 座標異常時
    x = -1, y = 3;
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorL(x, y));
    // 座標異常時
    x = 3, y = -1;
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorL(x, y));

    // 座標異常時
    x = 4, y = 0;
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorL(x, y));
    // 座標異常時
    x = 0, y = 4;
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorL(x, y));
  }

  TEST(BlockBingoData, getCircleColorR)
  {
    BlockBingoData blockBingoData;

    BingoNumber circleNumber = BingoNumber::six;
    Color expected = Color::blue;
    ASSERT_EQ(expected, blockBingoData.getBlockCircleColorR(circleNumber));

    int x = 0, y = 0;
    expected = Color::blue;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorR(x, y));

    x = 3, y = 1;
    expected = Color::red;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorR(x, y));

    x = 1, y = 3;
    expected = Color::green;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorR(x, y));

    x = 2, y = 2;
    expected = Color::yellow;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorR(x, y));

    // 座標異常時
    x = -1, y = 3;
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorR(x, y));
    // 座標異常時
    x = 3, y = -1;
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorR(x, y));

    // 座標異常時
    x = 4, y = 0;
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorR(x, y));
    // 座標異常時
    x = 0, y = 4;
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColorR(x, y));
  }
}  // namespace etrobocon2020_test
