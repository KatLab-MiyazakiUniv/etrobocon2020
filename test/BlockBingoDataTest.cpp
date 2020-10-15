/**
 *  @file   BlockBingoDataTest.cpp
 *  @brief  BlockBingoDataのテストファイル
 *  @author mutotaka0426,sugaken0528,Takahiro55555
 */
#include "BlockBingoData.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {

  TEST(BlockBingoData, setBlockCircle)
  {
    Controller controller;
    bool isLeftCourse = true;
    BlockBingoData blockBingoData(controller, isLeftCourse);
    BlockCircle blockCircle;
    Coordinate coordinate;

    // ブロックサークルの色の異常時判定(black)
    coordinate = { 1, 1 };
    blockCircle = BlockCircle{ Color::black, 1, Block{ Color::red, -1 } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(coordinate, blockCircle));

    // ブロックサークルの色の異常時判定(white)
    coordinate = { 1, 1 };
    blockCircle = BlockCircle{ Color::white, 1, Block{ Color::red, -1 } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(coordinate, blockCircle));

    // 正常時（XY座標境界値1）
    coordinate = { 1, 1 };
    blockCircle = BlockCircle{ Color::red, 1, Block{ Color::red, -1 } };
    ASSERT_TRUE(blockBingoData.setBlockCircle(coordinate, blockCircle));

    // 正常時(XY座標境界値2）
    coordinate = { 5, 5 };
    blockCircle = BlockCircle{ Color::red, 1, Block{ Color::red, -1 } };
    ASSERT_TRUE(blockBingoData.setBlockCircle(coordinate, blockCircle));

    // 座標異常時（指定したx座標が範囲外）
    coordinate = { 6, 1 };
    blockCircle = BlockCircle{ Color::red, 1, Block{ Color::red, 4 } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(coordinate, blockCircle));

    // 座標異常時（指定したy座標が範囲外）
    coordinate = { 1, 7 };
    blockCircle = BlockCircle{ Color::red, 1, Block{ Color::red, 4 } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(coordinate, blockCircle));

    // 座標異常時（指定したx座標が範囲外）
    coordinate = { -1, 5 };
    blockCircle = BlockCircle{ Color::red, 1, Block{ Color::red, 4 } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(coordinate, blockCircle));

    // 座標異常時（指定したy座標が範囲外）
    coordinate = { 5, -1 };
    blockCircle = BlockCircle{ Color::red, 1, Block{ Color::red, 4 } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(coordinate, blockCircle));

    // ブロックカラー異常時
    coordinate = { 5, 5 };
    blockCircle = BlockCircle{ Color::red, 1, Block{ Color::white, -1 } };
    ASSERT_FALSE(blockBingoData.setBlockCircle(coordinate, blockCircle));
  }

  TEST(BlockBingoData, setCrossCircle)
  {
    Controller controller;
    bool isLeftCourse = true;
    BlockBingoData blockBingoData(controller, isLeftCourse);
    CrossCircle crossCircle;
    Coordinate coordinate;

    //交点サークルの色の異常時判定(none)
    coordinate = { 0, 0 };
    crossCircle = CrossCircle{ Color::none, Block{ Color::red, -1 } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(coordinate, crossCircle));

    // 交点サークルの色の異常時判定(black)
    coordinate = { 0, 0 };
    crossCircle = CrossCircle{ Color::black, Block{ Color::red, -1 } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(coordinate, crossCircle));

    // 交点サークルの色の異常時判定(white)
    coordinate = { 0, 0 };
    crossCircle = CrossCircle{ Color::white, Block{ Color::red, -1 } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(coordinate, crossCircle));

    // 正常時（XY座標境界値1）
    coordinate = { 0, 0 };
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, -1 } };
    ASSERT_TRUE(blockBingoData.setCrossCircle(coordinate, crossCircle));

    // 正常時（XY座標境界値2）
    coordinate = { 6, 6 };
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, -1 } };
    ASSERT_TRUE(blockBingoData.setCrossCircle(coordinate, crossCircle));

    // 座標異常時（指定したx座標が範囲外）
    coordinate = { 8, 2 };
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, 4 } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(coordinate, crossCircle));

    // 座標異常時（指定したy座標が範囲外）
    coordinate = { 2, 8 };
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, 4 } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(coordinate, crossCircle));

    // 座標異常時（指定したx座標が範囲外）
    coordinate = { -2, 2 };
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, 4 } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(coordinate, crossCircle));

    // 座標異常時（指定したy座標が範囲外）
    coordinate = { 2, -2 };
    crossCircle = CrossCircle{ Color::red, Block{ Color::red, 4 } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(coordinate, crossCircle));

    // ブロックカラー異常時
    coordinate = { 4, 4 };
    crossCircle = CrossCircle{ Color::red, Block{ Color::white, -1 } };
    ASSERT_FALSE(blockBingoData.setCrossCircle(coordinate, crossCircle));
  }  // namespace etrobocon2020_test

  TEST(BlockBingoData, getBlockCircle)
  {
    Controller controller;
    bool isLeftCourse = true;
    BlockBingoData blockBingoData(controller, isLeftCourse);

    Color expectedBlockCircleColor = Color::red;
    Color expectedBlockColor = Color::blue;
    int expectedBlockNumber = 5;
    int expectedCircleNumber = 6;

    Coordinate coordinate = { 3, 5 };
    BlockCircle expected = { expectedBlockCircleColor,
                             expectedCircleNumber,
                             { expectedBlockColor, expectedBlockNumber } };
    blockBingoData.setBlockCircle(coordinate, expected);

    BlockCircle blockCircle = blockBingoData.getBlockCircle(coordinate);

    ASSERT_EQ(expectedBlockCircleColor, blockCircle.blockCircleColor);
    ASSERT_EQ(expectedBlockColor, blockCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, blockCircle.block.blockNumber);
    ASSERT_EQ(expectedCircleNumber, blockCircle.circleNumber);
  }

  TEST(BlockBingoData, getCrossCircle)
  {
    Controller controller;
    bool isLeftCourse = true;
    BlockBingoData blockBingoData(controller, isLeftCourse);

    Color expectedCrossCircleColor = Color::red;
    Color expectedBlockColor = Color::blue;
    int expectedBlockNumber = 5;

    Coordinate coordinate = { 2, 4 };
    CrossCircle expected
        = { expectedCrossCircleColor, { expectedBlockColor, expectedBlockNumber } };
    blockBingoData.setCrossCircle(coordinate, expected);

    CrossCircle crossCircle = blockBingoData.getCrossCircle(coordinate);

    ASSERT_EQ(expectedCrossCircleColor, crossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, crossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, crossCircle.block.blockNumber);
  }

  TEST(BlockBingoData, getCircleColorLeft)
  {
    Controller controller;
    bool isLeftCourse = true;
    BlockBingoData blockBingoData(controller, isLeftCourse);

    int circleNumber = 6;
    Color expected = Color::green;
    ASSERT_EQ(expected, blockBingoData.getBlockCircleColor(circleNumber));
    Coordinate coordinate;

    coordinate = { 0, 0 };
    expected = Color::red;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    coordinate = { 6, 2 };
    expected = Color::blue;

    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    coordinate = { 2, 6 };
    expected = Color::yellow;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    coordinate = { 4, 4 };
    expected = Color::green;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    // 座標異常時
    coordinate = { -2, 6 };
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));
    // 座標異常時
    coordinate = { 6, -2 };
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    // 座標異常時
    coordinate = { 8, 0 };
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));
    // 座標異常時
    coordinate = { 0, 8 };
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));
  }  // namespace etrobocon2020_test

  TEST(BlockBingoData, getCircleColorRight)
  {
    Controller controller;
    bool isLeftCourse = false;
    BlockBingoData blockBingoData(controller, isLeftCourse);

    int circleNumber = 6;
    Color expected = Color::blue;
    ASSERT_EQ(expected, blockBingoData.getBlockCircleColor(circleNumber));
    Coordinate coordinate;

    coordinate = { 0, 0 };
    expected = Color::blue;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    coordinate = { 6, 2 };
    expected = Color::red;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    coordinate = { 2, 6 };
    expected = Color::green;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    coordinate = { 4, 4 };
    expected = Color::yellow;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    // 座標異常時
    coordinate = { -1, 6 };
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));
    // 座標異常時
    coordinate = { 6, -1 };
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));

    // 座標異常時
    coordinate = { 7, 0 };
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));
    // 座標異常時
    coordinate = { 0, 7 };
    expected = Color::none;
    ASSERT_EQ(expected, blockBingoData.getCrossCircleColor(coordinate));
  }

  TEST(BlockBingoData, initBlockBingoData)
  {
    Controller controller;
    bool isLeftCourse = true;
    BlockBingoData blockBingoData(controller, isLeftCourse);
    ;

    Color expectedCircleColor;
    int expectedCircleNumber;
    Color expectedBlockColor;
    int expectedBlockNumber;

    CrossCircle actualCrossCircle;
    BlockCircle actualBlockCircle;

    blockBingoData.initBlockBingoData();

    // 数字カード
    int expected = 3;
    ASSERT_EQ(expected, blockBingoData.getCardNumber());

    // ブロックのテスト(1の左上)
    expectedCircleColor = Color::red;
    expectedBlockColor = Color::blue;
    expectedBlockNumber = -1;
    actualCrossCircle = blockBingoData.getCrossCircle(Coordinate(0, 0));
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(3の左上)
    expectedCircleColor = Color::blue;
    expectedBlockColor = Color::black;
    expectedBlockNumber = -1;
    actualCrossCircle = blockBingoData.getCrossCircle(Coordinate(4, 0));
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(1の右下)
    expectedCircleColor = Color::red;
    expectedBlockColor = Color::green;
    expectedBlockNumber = -1;
    actualCrossCircle = blockBingoData.getCrossCircle(Coordinate(2, 2));
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(3の右下)
    expectedCircleColor = Color::blue;
    expectedBlockColor = Color::red;
    expectedBlockNumber = -1;
    actualCrossCircle = blockBingoData.getCrossCircle(Coordinate(6, 2));
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(6の左上)
    expectedCircleColor = Color::yellow;
    expectedBlockColor = Color::red;
    expectedBlockNumber = -1;
    actualCrossCircle = blockBingoData.getCrossCircle(Coordinate(0, 4));
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(8の左上)
    expectedCircleColor = Color::green;
    expectedBlockColor = Color::yellow;
    expectedBlockNumber = -1;
    actualCrossCircle = blockBingoData.getCrossCircle(Coordinate(4, 4));
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(6の右下)
    expectedCircleColor = Color::yellow;
    expectedBlockColor = Color::blue;
    expectedBlockNumber = -1;
    actualCrossCircle = blockBingoData.getCrossCircle(Coordinate(2, 6));
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(8の右下)
    expectedCircleColor = Color::green;
    expectedBlockColor = Color::black;
    expectedBlockNumber = -1;
    actualCrossCircle = blockBingoData.getCrossCircle(Coordinate(6, 6));
    ASSERT_EQ(expectedCircleColor, actualCrossCircle.crossCircleColor);
    ASSERT_EQ(expectedBlockColor, actualCrossCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualCrossCircle.block.blockNumber);

    // ブロックのテスト(ブロックサークルの5)
    expectedCircleColor = Color::yellow;
    expectedCircleNumber = 5;
    expectedBlockColor = Color::yellow;
    expectedBlockNumber = -1;
    actualBlockCircle = blockBingoData.getBlockCircle(Coordinate(5, 3));
    ASSERT_EQ(expectedCircleColor, actualBlockCircle.blockCircleColor);
    ASSERT_EQ(expectedCircleNumber, actualBlockCircle.circleNumber);
    ASSERT_EQ(expectedBlockColor, actualBlockCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualBlockCircle.block.blockNumber);

    // ブロックのテスト(ブロックサークルの7)
    expectedCircleColor = Color::red;
    expectedCircleNumber = 7;
    expectedBlockColor = Color::green;
    expectedBlockNumber = -1;
    actualBlockCircle = blockBingoData.getBlockCircle(Coordinate(3, 5));
    ASSERT_EQ(expectedCircleColor, actualBlockCircle.blockCircleColor);
    ASSERT_EQ(expectedCircleNumber, actualBlockCircle.circleNumber);
    ASSERT_EQ(expectedBlockColor, actualBlockCircle.block.blockColor);
    ASSERT_EQ(expectedBlockNumber, actualBlockCircle.block.blockNumber);
  }

  TEST(BlockBingoData, Direction)
  {
    Controller controller;
    bool isLeftCourse = false;
    BlockBingoData blockBingoData(controller, isLeftCourse);

    Direction expected = Direction::North;
    Direction actual = blockBingoData.getDirection();
    ASSERT_EQ(expected, actual);

    expected = Direction::South;
    blockBingoData.setDirection(expected);
    actual = blockBingoData.getDirection();
    ASSERT_EQ(expected, actual);
  }
}  // namespace etrobocon2020_test
