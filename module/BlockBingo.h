/**
 *  @file   BlockCircle.h
 *  @brief
 *  @author mutotaka0426,sugaken0528,Takahiro55555
 */
#ifndef BLOCK_BINGO_H
#define BLOCK_BINGO_H

#include "Controller.h"

struct Block {
  Color block_color;
  int block_number = -1;
};

struct CrossCircle {
  Color cross_circle_color;
  Block block;
};

struct BlockCircle {
  Color block_circle_color;
  Block block;
  int circle_number = -1;
};

class BlockBingo {
 public:
  /** コンストラクタ
   *  @param 引数名 [引数の説明]
   */
  BlockBingo();

  /**
   *  @param x [ブロックサークルのx座標]
   *  @param y [ブロックサークルのy座標]
   *  @param block_circle [データ設定済みのBlockCircle構造体]
   */
  int init_block_circle(int x, int y, BlockCircle block_circle);

  /**
   *  @param x [クロスサークルのx座標]
   *  @param y [クロスサークルのy座標]
   *  @param cross_circle [データ設定済みのCrossCircle構造体]
   */
  int init_cross_circle(int x, int y, CrossCircle cross_circle);

  /**
   *  @param x [ブロックサークルのx座標]
   *  @param y [ブロックサークルのy座標]
   *  @return [BlockCircle構造体]
   */
  BlockCircle get_block_circle(int x, int y);

  /**
   *  @param x [クロスサークルのx座標]
   *  @param y [クロスサークルのy座標]
   *  @return [CrossCircle構造体]
   */
  CrossCircle get_cross_circle(int x, int y);

 private:
  const int BLOCK_CIRCLE_SIZE = 3;
  const int CROSS_CIRCLE_SIZE = 4;
  const int MAX_BLOCK_NUMBER = 8;
  const int MAX_BLOCK_CIRCLE_NUMBER = 8;
  struct BlockCircle block_circle_coordinate[3][3];
  struct CrossCircle cross_circle_coordinate[4][4];
};

#endif
