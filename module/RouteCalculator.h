/**
 *  @file	RouteCalculator.h
 *  @brief	経路計算をする
 *  @author	mutotaka0426, sugaken0528
 */
#ifndef ROUTE_CALCULATOR_H
#define ROUTE_CALCULATOR_H

#include "BlockBingoData.h"
#include <array>
#include <math.h>
#include <vector>
#include <algorithm>

struct AStarProperty {
  // ノードの座標
  Coordinate coordinate;
  int estimateCost;

  AStarProperty(Coordinate coordinate_, int estimateCost_)
    : coordinate(coordinate_), estimateCost(estimateCost_)
  {
  }

  bool operator<(const AStarProperty& another) const { return estimateCost < another.estimateCost; }
  bool operator>(const AStarProperty& another) const { return estimateCost > another.estimateCost; }
};

struct Route {
  //親ノード
  Coordinate parent;
  int currentCost;             //このノードに到達するまでのコスト
  Direction currentDirection;  //このノードに到達したときの向き　

  Route() : parent(-1, -1), currentCost(0), currentDirection(Direction::North) {}

  void set(Coordinate parent_, int currentCost_)
  {
    parent = parent_;
    currentCost = currentCost_;
  }
};

class RouteCalculator {
 public:
  /** コンストラクタ
   *  @param blockBingoData_ [BlockBingoData]
   */
  RouteCalculator(BlockBingoData& blockBingoData_);

  /**
   *  @brief 経路計算をする
   *  @param list 経路座標を格納するリスト
   *  @param startCoordinate [スタートノードの座標]
   *  @param goalCoordinate [ゴールノードの座標]
   */
  void solveBlockBingo(std::vector<Coordinate>& list, Coordinate startCoordinate,
                       Coordinate goalCoordinate);

 private:
  BlockBingoData& blockBingoData;
  Coordinate gCoordinate;  //クラス内でゴールノードを共有しておく
  static constexpr int AREASIZE = 7;

  /**
   *  @brief 指定ノードの隣接ノードをすべて求める
   *  @param coordinate [指定ノードの座標]
   *  @param route [経路情報]
   *  @return 隣接ノードそれぞれの情報(エリア外のノードは除外する)
   */
  std::vector<AStarProperty> nextNode(Coordinate coordinate, Route route[AREASIZE][AREASIZE]);

  /**
   *  @brief 指定ノードのブロックの有無を判定する(7×7座標)
   *  @param coordinate [指定ノードの座標]
   *  @return 判定結果 [trueがブロックあり]
   */
  bool blockCheck(Coordinate coordinate);

  /**
   *  @brief リストに隣接ノードと同じノードがあるか調べて，ある場合は削除する
   *  @param node [隣接ノードの情報]
   *  @param list [オープンorクローズリスト]
   *  @return 判定結果 [この隣接ノードを探索する必要がない場合true]
   */
  bool listCheck(AStarProperty node, std::vector<AStarProperty>& list);

  /**
   *  @brief 移動コストを設定する
   *  @param coordinate [移動元の座標]
   *  @param nextCoordinate [移動先の座標]
   *  @param route [経路情報]
   *  @return 移動コスト [int]
   */
  int moveCost(Coordinate coordinate, Coordinate nextCoordinate, Route route[AREASIZE][AREASIZE]);

  /**
   *  @brief ヒューリスティック関数としてマンハッタン距離を取る
   *  @param coordinate [指定ノードの座標]
   *  @return 指定ノードとゴールノードのマンハッタン距離 [int]
   */
  int manhattanDistance(Coordinate coordinate);

  /**
   *  @brief 指定ノードまでの経路をセットする
   *  @param list [経路座標を保持するリスト]
   *  @param route [経路情報]
   *  @param coordinate [指定ノードの座標]
   */
  void setRoute(std::vector<Coordinate>& list, Route route[AREASIZE][AREASIZE],
                Coordinate coordinate);
};

#endif
