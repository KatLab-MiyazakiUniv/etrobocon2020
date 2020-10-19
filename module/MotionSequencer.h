/**
 * @file MotionSequencer.h
 * @brief 座標情報を機動に変換するクラス
 * @author T.Yoshino(Mikoyaan), D.Hirayama(Kanikama)
 **/

#ifndef MOTIONSEQUENCER_H
#define MOTIONSEQUENCER_H

#include <vector>
#include "Controller.h"
#include "BlockBingoData.h"
#include "Navigator.h"

using std::abs;
using std::vector;

class MotionSequencer {
 public:
  /** コンストラクタ
   * @param　controller_
   * @param isLeftCourse
   * @param blockBingoData_
   **/
  MotionSequencer(BlockBingoData& blockBingoData_);

  /** 経路->動作命令リスト変換
   * @param route             [経路]
   * @param motionCommandList [動作命令リスト]
   * @return 最終的な走行体の向き
   **/
  Direction route2MotionCommand(vector<Coordinate> const& route,
                                vector<MotionCommand>& motionCommandList);

 private:
  BlockBingoData& blockBingoData;

  /** 45°方向転換を行う回数と、方向転換の向き(時計回り/反時計回り)を計算する
   * @param   currentDirection  [現在の走行体の方向]
   * @param   nextDirection     [現在座標から見た、次の座標の方向]
   * @return  45°方向転換を行う回数(正=時計回り,負=反時計回り)
   **/
  int calcRotationCount(Direction currentDirection, Direction nextDirection);
};
#endif  // MOTIONSEQUENCER_H