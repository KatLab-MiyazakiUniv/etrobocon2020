/**
 *  @file	BlockBingo.h
 *  @brief	ビンゴエリアを攻略する
 *  @author	mutotaka0426, sugaken0528
 */
#ifndef BLOCK_BINGO_H
#define BLOCK_BINGO_H

#include "BlockBingoData.h"

class BlockBingo {
 public:
  /** コンストラクタ
   *  @param controller_ [Controller]
   *  @param isLeftCourse_ [Bool]
   *  @param blockBingoData_ [BlockBingoData]
   */
  BlockBingo(Controller& controller_, bool isLeftCourse_, BlockBingoData& blockBingoData_);

  /**
   *  @brief
   */
  void run(void);

 private:
  Controller& controller;
  bool isLeftCourse;
  BlockBingoData& blockBingoData;

  /**
   *  @brief ビンゴエリアのデータを初期化する
   */
  void initBlockBingoData(void);

  /**
   *  @brief ブロック情報を初期化する
   *  @param initColor [初期化する色]
   *  @param coordinate [APIで受け取った座標]
   */
  void initBlock(Color initColor, int coordinate);
};

#endif
