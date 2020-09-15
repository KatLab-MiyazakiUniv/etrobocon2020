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
  int x;
  int y;
  double estimateCost;

  AStarProperty(int x_, int y_, double estimateCost_) : x(x_), y(y_), estimateCost(estimateCost_) {}

  bool operator<(const AStarProperty& another) const { return estimateCost < another.estimateCost; }
  bool operator>(const AStarProperty& another) const { return estimateCost > another.estimateCost; }
};

struct Route {
  int px;  //親ノード
  int py;
  int currentCost;             //このノードに到達するまでのコスト
  Direction currentDirection;  //このノードに到達したときの向き　

  Route() : px(-1), py(-1), currentCost(0), currentDirection(Direction::North) {}

  void set(int px_, int py_, double currentCost_)
  {
    px = px_;
    py = py_;
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
   *  @param sx [スタートノードのx座標]
   *  @param sy [スタートノードのy座標]
   *  @param gx [ゴールノードのx座標]
   *  @param gy [ゴールノードのy座標]
   *  @param  [走行体の向き(0~7)]
   */
  void solveBlockBingo(std::vector<std::vector<int>>& list, int sx, int sy, int gx, int gy);

 private:
  BlockBingoData& blockBingoData;
  int gX, gY;  //クラス内でゴールノードを共有しておく

  /**
   *  @brief 指定ノードの隣接ノードをすべて求める
   *  @param x [指定ノードのx座標]
   *  @param y [指定ノードのy座標]
   *  @param currentCost [スタートノードから指定ノードまでの現時点の最短コスト]
   *  @param route [経路情報]
   *  @return 隣接ノードそれぞれの情報(エリア外のノードは除外する)
   */
  std::vector<AStarProperty> nextNode(int x, int y, double currentCost, Route route[7][7]);

  /**
   *  @brief その座標のブロックの有無を判定する(7×7座標)
   *  @param x [x座標]
   *  @param y [y座標]
   *  @return 判定結果 [trueがブロックあり]
   */
  bool blockCheck(int x, int y);

  /**
   *  @brief リストに隣接ノードと同じノードがあるか判定
   *  @param node [隣接ノードの情報]
   *  @param list [オープンorクローズリスト]
   *  @return 判定結果 [この隣接ノードを探索する必要がない場合true]
   */
  bool listCheck(AStarProperty node, std::vector<AStarProperty>& list);

  /**
   *  @brief 移動コストを設定する
   *  @param x [移動元のx座標]
   *  @param y [移動元のy座標]
   *  @param nx [移動先のx座標]
   *  @param ny [移動先のy座標]
   *  @param route [経路情報]
   *  @return 移動コスト [int]
   */
  int moveCost(int x, int y, int nx, int ny, Route route[7][7]);

  /**
   *  @brief ヒューリスティック関数としてユークリッド距離を取る
   *  @param nx [隣接ノードのx座標]
   *  @param ny [隣接ノードのy座標]
   *  @return 隣接ノードとゴールノードのユークリッド距離 [double]
   */
  double euclideanDistance(int nx, int ny);

  /**
   *  @brief 指定ノードまでの経路をセットする
   *  @param list [経路座標を保持するリスト]
   *  @param route [経路情報]
   *  @param x [x座標]
   *  @param y [y座標]
   */
  void setRoute(std::vector<std::vector<int>>& list, Route route[7][7], int x, int y);
};

#endif
