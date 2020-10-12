/**
 *  @file   RouteCalculatorTest.cpp
 *  @brief  RouteCalculatorクラスのテストファイル
 *  @author mutotaka0426, sugaken0528
 */
#include "RouteCalculator.h"
#include <gtest/gtest.h>

using namespace std;

namespace etrobocon2020_test {
  TEST(RouteCalculator, solveBlockBingoData)
  {
    Controller controller;
    bool isLeftCourse = true;
    BlockBingoData blockBingoData(controller, isLeftCourse);
    RouteCalculator routeCalculator(blockBingoData);
    vector<vector<int>> actualList;
    int AREASIZE = 7;
    int actualDiffX, actualDiffY;
    int expectedSX, expectedSY, expectedGX, expectedGY;
    int goalPoint;

    blockBingoData.initBlockBingoData();

    for(expectedSX = 0; expectedSX < AREASIZE; expectedSX++) {
      for(expectedSY = 0; expectedSY < AREASIZE; expectedSY++) {
        for(expectedGX = 0; expectedGX < AREASIZE; expectedGX++) {
          for(expectedGY = 0; expectedGY < AREASIZE; expectedGY++) {
            routeCalculator.solveBlockBingo(actualList, expectedSX, expectedSY, expectedGX,
                                            expectedGY);
            // スタートとゴールが指定されたものか
            goalPoint = (int)actualList.size() - 1;
            ASSERT_EQ(expectedSX, actualList[0][0]);
            ASSERT_EQ(expectedSY, actualList[0][1]);
            ASSERT_EQ(expectedGX, actualList[goalPoint][0]);
            ASSERT_EQ(expectedGY, actualList[goalPoint][1]);
            // 座標が隣り合っているか
            for(int i = 1; i < (int)actualList.size(); i++) {
              actualDiffX = abs(actualList[i - 1][0] - actualList[i][0]);
              actualDiffY = abs(actualList[i - 1][1] - actualList[i][1]);
              ASSERT_TRUE(actualDiffX == 0 || actualDiffX == 1)
                  << "actualList[" << i << "]'-actualDiffX=" << actualDiffX;
              ASSERT_TRUE(actualDiffY == 0 || actualDiffY == 1)
                  << "actualList[" << i << "]'-actualDiffY=" << actualDiffY;
              ASSERT_FALSE(actualDiffX == 0 && actualDiffY == 0);
            }
          }
        }
      }
    }

    //(2,6)のブロックと(4,4)のブロックを設置して(0,6)に行くまでの経路をテスト
    routeCalculator.solveBlockBingo(actualList, 2, 6, 5, 5);  // 青ブロックを(5,5)に運ぶ
    ASSERT_EQ(2, actualList[0][0]);
    ASSERT_EQ(6, actualList[0][1]);
    ASSERT_EQ(3, actualList[1][0]);
    ASSERT_EQ(6, actualList[1][1]);
    ASSERT_EQ(4, actualList[2][0]);
    ASSERT_EQ(6, actualList[2][1]);
    ASSERT_EQ(5, actualList[3][0]);
    ASSERT_EQ(5, actualList[3][1]);
    blockBingoData.setDirection(Direction::North);
    routeCalculator.solveBlockBingo(actualList, 4, 6, 4, 4);  // 黄ブロックを取りに行く
    ASSERT_EQ(4, actualList[0][0]);
    ASSERT_EQ(6, actualList[0][1]);
    ASSERT_EQ(4, actualList[1][0]);
    ASSERT_EQ(5, actualList[1][1]);
    ASSERT_EQ(4, actualList[2][0]);
    ASSERT_EQ(4, actualList[2][1]);
    blockBingoData.setDirection(Direction::North);
    routeCalculator.solveBlockBingo(actualList, 4, 4, 1, 1);  // 黄ブロックを(1,1)に運ぶ
    ASSERT_EQ(4, actualList[0][0]);
    ASSERT_EQ(4, actualList[0][1]);
    ASSERT_EQ(4, actualList[1][0]);
    ASSERT_EQ(3, actualList[1][1]);
    ASSERT_EQ(4, actualList[2][0]);
    ASSERT_EQ(2, actualList[2][1]);
    ASSERT_EQ(4, actualList[3][0]);
    ASSERT_EQ(1, actualList[3][1]);
    ASSERT_EQ(3, actualList[4][0]);
    ASSERT_EQ(0, actualList[4][1]);
    ASSERT_EQ(2, actualList[5][0]);
    ASSERT_EQ(0, actualList[5][1]);
    ASSERT_EQ(1, actualList[6][0]);
    ASSERT_EQ(1, actualList[6][1]);
    blockBingoData.setDirection(Direction::SWest);
    routeCalculator.solveBlockBingo(actualList, 2, 0, 0, 6);  // (0,6)に向かう
    ASSERT_EQ(2, actualList[0][0]);
    ASSERT_EQ(0, actualList[0][1]);
    ASSERT_EQ(2, actualList[1][0]);
    ASSERT_EQ(1, actualList[1][1]);
    ASSERT_EQ(1, actualList[2][0]);
    ASSERT_EQ(2, actualList[2][1]);
    ASSERT_EQ(2, actualList[3][0]);
    ASSERT_EQ(3, actualList[3][1]);
    ASSERT_EQ(2, actualList[4][0]);
    ASSERT_EQ(4, actualList[4][1]);
    ASSERT_EQ(2, actualList[5][0]);
    ASSERT_EQ(5, actualList[5][1]);
    ASSERT_EQ(1, actualList[6][0]);
    ASSERT_EQ(6, actualList[6][1]);
    ASSERT_EQ(0, actualList[7][0]);
    ASSERT_EQ(6, actualList[7][1]);
  }
}  // namespace etrobocon2020_test
