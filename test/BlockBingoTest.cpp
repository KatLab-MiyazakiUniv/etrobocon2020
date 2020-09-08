/**
 *  @file   BlockBingoTest.cpp
 *  @brief  BlockBingoのテストファイル
 *  @author mutotaka0426,sugaken0528
 */
#include "BlockBingo.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {

  TEST(BlockBingo, initBlockBingoData)
  {
    Controller controller;
    bool isLeftCourse = true;
    BlockBingoData blockBingoData;
    BlockBingo blockBingo(controller, isLeftCourse, blockBingoData);

    Color expectedCircleColor;
    BingoNumber expectedCircleNumber;
    Color expectedBlockColor;
    BingoNumber expectedBlockNumber;

    CrossCircle actualCrossCircle;
    BlockCircle actualBlockCircle;

    blockBingo.run();

    // 数字カード
    BingoNumber expected = BingoNumber::three;
    ASSERT_EQ(expected, blockBingoData.getCardNumber());

    // ブロックのテスト(1の左上)
    expectedCircleColor = Color::red;
    expectedBlockColor = Color::blue;
    expectedBlockNumber = BingoNumber::none;
    actualCrossCircle = blockBingoData.getCrossCircle(0, 0);
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(3の左上)
    expectedCircleColor = Color::blue;
    expectedBlockColor = Color::black;
    expectedBlockNumber = BingoNumber::none;
    actualCrossCircle = blockBingoData.getCrossCircle(2, 0);
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(1の右下)
    expectedCircleColor = Color::red;
    expectedBlockColor = Color::green;
    expectedBlockNumber = BingoNumber::none;
    actualCrossCircle = blockBingoData.getCrossCircle(1, 1);
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(3の右下)
    expectedCircleColor = Color::blue;
    expectedBlockColor = Color::red;
    expectedBlockNumber = BingoNumber::none;
    actualCrossCircle = blockBingoData.getCrossCircle(3, 1);
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(6の左上)
    expectedCircleColor = Color::yellow;
    expectedBlockColor = Color::red;
    expectedBlockNumber = BingoNumber::none;
    actualCrossCircle = blockBingoData.getCrossCircle(0, 2);
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(8の左上)
    expectedCircleColor = Color::green;
    expectedBlockColor = Color::yellow;
    expectedBlockNumber = BingoNumber::none;
    actualCrossCircle = blockBingoData.getCrossCircle(2, 2);
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(6の右下)
    expectedCircleColor = Color::yellow;
    expectedBlockColor = Color::blue;
    expectedBlockNumber = BingoNumber::none;
    actualCrossCircle = blockBingoData.getCrossCircle(1, 3);
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(8の右下)
    expectedCircleColor = Color::green;
    expectedBlockColor = Color::black;
    expectedBlockNumber = BingoNumber::none;
    actualCrossCircle = blockBingoData.getCrossCircle(3, 3);
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(ブロックサークルの5)
    expectedCircleColor = Color::yellow;
    expectedCircleNumber = BingoNumber::five;
    expectedBlockColor = Color::yellow;
    expectedBlockNumber = BingoNumber::none;
    actualBlockCircle = blockBingoData.getBlockCircle(2, 1);
    ASSERT_EQ(expectedCircleColor, actualBlockCircle.blockCircleColor);
    ASSERT_EQ(expectedCircleNumber, actualBlockCircle.circleNumber);
    ASSERT_EQ(expectedBlockColor, actualBlockCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualBlockCircle.block.blockNumber);

    // ブロックのテスト(ブロックサークルの7)
    expectedCircleColor = Color::red;
    expectedCircleNumber = BingoNumber::seven;
    expectedBlockColor = Color::green;
    expectedBlockNumber = BingoNumber::none;
    actualBlockCircle = blockBingoData.getBlockCircle(1, 2);
    ASSERT_EQ(expectedCircleColor, actualBlockCircle.blockCircleColor);
    ASSERT_EQ(expectedCircleNumber, actualBlockCircle.circleNumber);
    ASSERT_EQ(expectedBlockColor, actualBlockCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualBlockCircle.block.blockNumber);
  }
}  // namespace etrobocon2020_test
