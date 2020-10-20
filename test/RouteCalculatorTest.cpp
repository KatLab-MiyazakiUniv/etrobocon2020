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
     // フルビンゴ成立+数字カード黒ブロック設置+ガレージ開始座標へ移動のテスト
    // 青ブロックを(5,5)に運ぶ
    start = { 2, 6 };
    goal = { 5, 5 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(2, 6), actualList[0]);
    ASSERT_EQ(Coordinate(3, 6), actualList[1]);
    ASSERT_EQ(Coordinate(4, 6), actualList[2]);
    ASSERT_EQ(Coordinate(5, 5), actualList[3]);
    blockBingoData.setDirection(Direction::North);
    blockBingoData.moveBlock(start, goal);
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
    blockBingoData.moveBlock(start, goal);
    // (0,0)の青ブロックを取りに行く
    start = { 2, 0 };
    goal = { 0, 0 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(2, 0), actualList[0]);
    ASSERT_EQ(Coordinate(1, 0), actualList[1]);
    ASSERT_EQ(Coordinate(0, 0), actualList[2]);
    blockBingoData.setDirection(Direction::West);
    // 青ブロックを(1,3)に運ぶ
    start = { 0, 0 };
    goal = { 1, 3 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(0, 0), actualList[0]);
    ASSERT_EQ(Coordinate(0, 1), actualList[1]);
    ASSERT_EQ(Coordinate(0, 2), actualList[2]);
    ASSERT_EQ(Coordinate(1, 3), actualList[3]);
    blockBingoData.setDirection(Direction::West);
    blockBingoData.moveBlock(start, goal);
    // (2,2)の緑ブロックを取得
    start = { 0, 2 };
    goal = { 2, 2 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(0, 2), actualList[0]);
    ASSERT_EQ(Coordinate(1, 2), actualList[1]);
    ASSERT_EQ(Coordinate(2, 2), actualList[2]);
    blockBingoData.setDirection(Direction::East);
    // (2,2)の緑ブロックを(3,1)に運ぶ
    start = { 2, 2 };
    goal = { 3, 1 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(2, 2), actualList[0]);
    ASSERT_EQ(Coordinate(3, 1), actualList[1]);
    blockBingoData.setDirection(Direction::NEast);
    blockBingoData.moveBlock(start, goal);
    // (6,2)の赤ブロックを取得
    start = { 2, 2 };
    goal = { 6, 2 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(2, 2), actualList[0]);
    ASSERT_EQ(Coordinate(3, 2), actualList[1]);
    ASSERT_EQ(Coordinate(4, 2), actualList[2]);
    ASSERT_EQ(Coordinate(5, 2), actualList[3]);
    ASSERT_EQ(Coordinate(6, 2), actualList[4]);
    blockBingoData.setDirection(Direction::East);
    // (6,2)の赤ブロックを(5,1)に運ぶ
    start = { 6, 2 };
    goal = { 5, 1 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(6, 2), actualList[0]);
    ASSERT_EQ(Coordinate(5, 1), actualList[1]);
    blockBingoData.setDirection(Direction::NWest);
    blockBingoData.moveBlock(start, goal);
    // (4,0)の数字カード黒ブロックを取得
    start = { 6, 2 };
    goal = { 4, 0 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(6, 2), actualList[0]);
    ASSERT_EQ(Coordinate(6, 1), actualList[1]);
    ASSERT_EQ(Coordinate(6, 0), actualList[2]);
    ASSERT_EQ(Coordinate(5, 0), actualList[3]);
    ASSERT_EQ(Coordinate(4, 0), actualList[4]);
    blockBingoData.setDirection(Direction::West);
    // (4,0)の数字カード黒ブロックを(5,1)に設置
    start = { 4, 0 };
    goal = { 5, 1 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(4, 0), actualList[0]);
    ASSERT_EQ(Coordinate(5, 1), actualList[1]);
    blockBingoData.setDirection(Direction::SEast);
    blockBingoData.moveBlock(start, goal);
    // (3,5)の緑ブロックを取得
    start = { 4, 0 };
    goal = { 3, 5 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(4, 0), actualList[0]);
    ASSERT_EQ(Coordinate(4, 1), actualList[1]);
    ASSERT_EQ(Coordinate(4, 2), actualList[2]);
    ASSERT_EQ(Coordinate(4, 3), actualList[3]);
    ASSERT_EQ(Coordinate(4, 4), actualList[4]);
    ASSERT_EQ(Coordinate(3, 5), actualList[5]);
    blockBingoData.setDirection(Direction::SWest);
    // (3,5)の緑ブロックを(1,5)に設置
    start = { 3, 5 };
    goal = { 1, 5 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(3, 5), actualList[0]);
    ASSERT_EQ(Coordinate(2, 5), actualList[1]);
    ASSERT_EQ(Coordinate(1, 5), actualList[2]);
    blockBingoData.setDirection(Direction::West);
    blockBingoData.moveBlock(start, goal);
    // (0,4)の赤ブロックを取得
    start = { 2, 5 };
    goal = { 0, 4 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(2, 5), actualList[0]);
    ASSERT_EQ(Coordinate(2, 4), actualList[1]);
    ASSERT_EQ(Coordinate(1, 4), actualList[2]);
    ASSERT_EQ(Coordinate(0, 4), actualList[3]);
    blockBingoData.setDirection(Direction::West);
    // (0,4)の赤ブロックを(3,5)に設置
    start = { 0, 4 };
    goal = { 3, 5 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(0, 4), actualList[0]);
    ASSERT_EQ(Coordinate(1, 4), actualList[1]);
    ASSERT_EQ(Coordinate(2, 4), actualList[2]);
    ASSERT_EQ(Coordinate(3, 5), actualList[3]);
    blockBingoData.setDirection(Direction::SEast);
    blockBingoData.moveBlock(start, goal);
    // (0,6)に向かう
    start = { 2, 4 };
    goal = { 0, 6 };
    routeCalculator.solveBlockBingo(actualList, start, goal);
    ASSERT_EQ(Coordinate(2, 4), actualList[0]);
    ASSERT_EQ(Coordinate(2, 5), actualList[1]);
    ASSERT_EQ(Coordinate(2, 6), actualList[2]);
    ASSERT_EQ(Coordinate(1, 6), actualList[3]);
    ASSERT_EQ(Coordinate(0, 6), actualList[4]);
    blockBingoData.setDirection(Direction::West);
  }
}  // namespace etrobocon2020_test