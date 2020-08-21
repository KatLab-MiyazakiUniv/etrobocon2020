/**
 *  @file   BlockBingoData.h
 *  @brief	ビンゴエリアのデータ構造を管理する
 *  @author mutotaka0426,sugaken0528,Takahiro55555
 */
#ifndef BLOCK_BINGO_H
#define BLOCK_BINGO_H

#include "Controller.h"

enum class BingoNumber { one, two, three, four, five, six, seven, eight, none };

struct Block {
  Color blockColor;
  BingoNumber blockNumber;
};

struct BlockCircle {
  Color blockCircleColor;
  Block block;
  BingoNumber circleNumber;
};

struct CrossCircle {
  Color crossCircleColor;
  Block block;
};

class BlockBingoData {
 public:
  /**
   *  @param x [ブロックサークルのx座標]
   *  @param y [ブロックサークルのy座標]
   *  @param blockCircle [データ設定済みのBlockCircle構造体]
   */
  int initBlockCircle(int x, int y, BlockCircle blockCircle);

  /**
   *  @param x [クロスサークルのx座標]
   *  @param y [クロスサークルのy座標]
   *  @param crossCircle [データ設定済みのCrossCircle構造体]
   */
  int initCrossCircle(int x, int y, CrossCircle crossCircle);

  /**
   *  @param crossCircle [データ設定済みのCrossCircle構造体]
   */
  void initCardNumber(BingoNumber cardNumber);

  /**
   *  @param x [ブロックサークルのx座標]
   *  @param y [ブロックサークルのy座標]
   *  @return [BlockCircle構造体]
   */
  BlockCircle getBlockCircle(int x, int y);

  /**
   *  @param x [クロスサークルのx座標]
   *  @param y [クロスサークルのy座標]
   *  @return [crosscircle構造体]
   */
  CrossCircle getCrossCircle(int x, int y);

  /**
   *  @return [BingoNumber]
   */
  BingoNumber getCardNumber(void);

 private:
  const int BlockCircleSize = 3;
  const int CrossCircleSize = 4;
  struct BlockCircle blockCircleCoordinate[3][3];
  struct CrossCircle crossCircleCoordinate[4][4];
  BingoNumber cardNumber = BingoNumber::none;
};

#endif
