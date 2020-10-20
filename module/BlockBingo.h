/**
 *  @file   BlockBingo.h
 *  @brief	ビンゴエリアを攻略する
 *  @author mutotaka0426
 */
#ifndef BLOCK_BINGO_H
#define BLOCK_BINGO_H

#include "Controller.h"
#include "BlockBingoData.h"
#include "RouteCalculator.h"
#include "MotionSequencer.h"
#include "Navigator.h"
#include <array>
#include <vector>

class BlockBingo {
 private:
  Controller& controller;
  bool isLeftCourse;
  BlockBingoData blockBingoData;
  static constexpr int AREASIZE = 7;

  /** @brief ブロックとサークルの座標を色ごとにそれぞれリストにセットする
   *  @param blockList [ブロック座標を格納するリスト]
   *  @param circleList [サークル座標を格納するリスト]
   */
  void setColorList(std::array<std::array<Coordinate, 2>, 5>& blockList,
                    std::array<std::array<Coordinate, 2>, 5>& circleList);

  /** @brief ブロックの運搬先を計算する
   *  @param blockList [ブロック座標が格納されたリスト]
   *  @param circleList [サークル座標が格納されたリスト]
   *  @return 各ブロックの運搬先リスト
   */
  std::vector<std::pair<Coordinate, Coordinate>> transportCalculate(
      std::array<std::array<Coordinate, 2>, 5> blockList,
      std::array<std::array<Coordinate, 2>, 5> circleList);

  /** @brief 2つの座標のマンハッタン距離を計算する
   *  @param coordinateFrom [座標1]
   *  @param coordinateTo [座標2]
   *  @return マンハッタン距離
   */
  int manhattanDistance(Coordinate coordinateFrom, Coordinate coordinateTo);

  /** @brief 運搬先リストから、現在座標に一番近いブロック座標のリスト番号を取得する
   *  @param transportList [運搬先リスト]
   *  @return ブロック座標のリスト番号
   */
  int popCoordinate(std::vector<std::pair<Coordinate, Coordinate>> const& transportList);

 public:
  /** コンストラクタ
   *  @param controller_ [Controller]
   *  @param isLeftCourse_ [Bool]
   */
  BlockBingo(Controller& controller_, bool isLeftCourse_);

  /**
   *  @brief ブロックビンゴの攻略をする
   */
  void runBlockBingo();

  /**
   *  @brief ビンゴエリア情報を返す
   *  @return ビンゴエリア情報
   */
  BlockBingoData& getBlockBingoData();
};

#endif
