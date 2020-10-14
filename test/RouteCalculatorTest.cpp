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
    vector<Coordinate> actualList;
    int AREASIZE = 7;
    int actualDiffX, actualDiffY;
    Coordinate expectedStart, expectedGoal;
    int goalPoint;

    blockBingoData.initBlockBingoData();

    for(int sx = 0; sx < AREASIZE; sx++) {
      for(int sy = 0; sy < AREASIZE; sy++) {
        for(int gx = 0; gx < AREASIZE; gx++) {
          for(int gy = 0; gy < AREASIZE; gy++) {
            expectedStart = { sx, sy };
            expectedGoal = { gx, gy };
            routeCalculator.solveBlockBingo(actualList, expectedStart, expectedGoal);
            // スタートとゴールが指定されたものか
            goalPoint = (int)actualList.size() - 1;
            ASSERT_EQ(expectedStart, actualList[0]);
            ASSERT_EQ(expectedGoal, actualList[goalPoint]);
            // 座標が隣り合っているか
            for(int i = 1; i < (int)actualList.size(); i++) {
              actualDiffX = abs(actualList[i - 1].x - actualList[i].x);
              actualDiffY = abs(actualList[i - 1].y - actualList[i].y);
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

    Coordinate start, goal;
    //(2,6)のブロックと(4,4)のブロックを設置して(0,6)に行くまでの経路をテスト
    // 青ブロックを(5,5)に運ぶ
    start = { 2, 6 };
    goal = { 5, 5 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(2, 6), actualList[0]);
    ASSERT_EQ(Coordinate(3, 6), actualList[1]);
    ASSERT_EQ(Coordinate(4, 6), actualList[2]);
    ASSERT_EQ(Coordinate(5, 5), actualList[3]);
    blockBingoData.setDirection(Direction::North);

    // 黄ブロックを取りに行く
    start = { 4, 6 };
    goal = { 4, 4 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(4, 6), actualList[0]);
    ASSERT_EQ(Coordinate(4, 5), actualList[1]);
    ASSERT_EQ(Coordinate(4, 4), actualList[2]);
    blockBingoData.setDirection(Direction::North);

    // 黄ブロックを(1,1)に運ぶ
    start = { 4, 4 };
    goal = { 1, 1 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(4, 4), actualList[0]);
    ASSERT_EQ(Coordinate(4, 3), actualList[1]);
    ASSERT_EQ(Coordinate(4, 2), actualList[2]);
    ASSERT_EQ(Coordinate(4, 1), actualList[3]);
    ASSERT_EQ(Coordinate(3, 0), actualList[4]);
    ASSERT_EQ(Coordinate(2, 0), actualList[5]);
    ASSERT_EQ(Coordinate(1, 1), actualList[6]);
    blockBingoData.setDirection(Direction::SWest);

    // (0,6)に向かう
    start = { 2, 0 };
    goal = { 0, 6 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(2, 0), actualList[0]);
    ASSERT_EQ(Coordinate(2, 1), actualList[1]);
    ASSERT_EQ(Coordinate(1, 2), actualList[2]);
    ASSERT_EQ(Coordinate(2, 3), actualList[3]);
    ASSERT_EQ(Coordinate(2, 4), actualList[4]);
    ASSERT_EQ(Coordinate(2, 5), actualList[5]);
    ASSERT_EQ(Coordinate(1, 6), actualList[6]);
    ASSERT_EQ(Coordinate(0, 6), actualList[7]);
  }
}  // namespace etrobocon2020_test
