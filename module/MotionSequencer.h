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
  /**
   * @brief  コンストラクタ
   * @param　controller_
   * @param  isLeftCourse
   * @param  blockBingoData_
   **/
  MotionSequencer(Controller& controller, bool isLeftCourse, BlockBingoData& blockBingoData_);

  /**
   * @brief   経路->走行体動作に変換
   * @param   route [経路]
   * @return  最終的な走行体の向き
   **/
  Direction route2Motion(vector<Coordinate> const& route, vector<MotionCommand>& motionCommandList);

 private:
  Controller& controller;
  Navigator navigator;
  BlockBingoData& blockBingoData;
};
#endif  // MOTIONSEQUENCER_H
