/**
 *  @file  Navigator.h
 *  @brief ビンゴエリアを走る
 *  @author sugaken0528, arimakaoru
 */

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <vector>
#include "MoveStraight.h"
#include "LineTracer.h"
#include "Rotation.h"

using std::abs;
using std::vector;

enum class MotionCommand {
  RT,  // 時計回りに45°方向転換(Rotation True)
  RF,  // 反時計回りに45°方向転換(Rotation False)
  CM,  // 交点サークル→中点の移動(Cross circle to Middle point)
  GC,  // 交点サークルからブロックサークルのブロックを取得する(Get block from Cross circle)
  SC,  // 交点サークルからブロックサークルにブロックを設置する(Set block from Cross circle)
  MC,  // 中点→交点サークルの移動(Middle point to Cross circle)
  MM,  // 中点→中点の移動(Midlle point to Middle point)
  GM,  // 中点からブロックサークルのブロックを取得する(Get block from Middle point)
  SM,  // 中点からブロックサークルにブロックを設置する(Set block from Middle point)
  BC,  // ブロックサークル→交点サークルの移動(Block circle to Cross circle)
  BM   // ブロックサークル→中点の移動(Block circle to Middle point)
};

class Navigator {
 public:
  /**
   * コンストラクタ
   *
   * @brief Navigatorクラスのコンストラクタ
   * @param &controller_ [Controllerインスタンスの参照]
   * @param isLeftCourse_ [コースがどっちかtrueがLeftコース]
   * @param targetBrightness_ [黒と白の閾値]
   */
  Navigator(Controller& controller_, bool isLeftCourse_);

  /**
   * @brief 動作命令に対応する動作を実行する
   * @param motionCommandList [動作命令リスト]
   */
  void execMotion(vector<MotionCommand> const& motionCommandList);

  /**
   * @brief ビンゴエリアにまっすぐ進入する(Lコースなら(2,6)へ)
   */
  void enterStraight();

  /**
   * @brief ビンゴエリアに左斜めに進入する(Lコースなら(1,6)へ)
   */
  void enterLeft();

  /**
   * @brief ビンゴエリアに右斜めに進入する(Lコースなら(3,6)へ)
   */
  void enterRight();

 private:
  Controller& controller;
  bool isLeftCourse;
  bool isLeftEdge;
  MoveStraight moveStraight;
  LineTracer lineTracer;
  Rotation rotation;

  /**
   * @brief 同じ動作命令が連続して繰り返されている回数を数える
   * @param motionCommandList [動作命令リスト]
   * @param startIndex [カウントを始めるインデックス]
   */
  int countRepeatedCommand(vector<MotionCommand> const& motionCommandList, int startIndex);

  /**
   * @brief 方向転換
   * @param rotationAngle [方向転換に必要な角度]
   * @param clockwise     [方向転換の向き、正=時計回り、負=反時計回り]
   */
  void changeDirection(unsigned int rotationAngle, bool clockwise);

  /**
   * @brief 交点サークルから中点への移動
   */
  void moveC2M();

  /**
   * @brief 交点サークルからブロックサークルのブロックを取得する
   */
  void getBlockFromC();

  /**
   * @brief 交点サークルからブロックサークルにブロックを設置する
   */
  void setBlockFromC();

  /**
   * @brief 中点から交点サークルへの移動
   */
  void moveM2C();

  /**
   * @brief 中点から中点への移動
   */
  void moveM2M();

  /**
   * @brief 中点からブロックサークルのブロックを取得する
   */
  void getBlockFromM();

  /**
   * @brief 中点からブロックサークルにブロックを設置する
   */
  void setBlockFromM();

  /**
   * @brief ブロックサークルから交点サークルへの移動
   */
  void moveB2C();

  /**
   * @brief ブロックサークルから中点への移動
   */
  void moveB2M();
};

#endif
