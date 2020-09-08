/**
 *  @file   BlockBingoData.h
 *  @brief	ビンゴエリアのデータ構造を管理する
 *  @author mutotaka0426,sugaken0528,Takahiro55555
 */
#ifndef BLOCK_BINGO_DATA_H
#define BLOCK_BINGO_DATA_H

#include "Controller.h"

enum class BingoNumber { none, one, two, three, four, five, six, seven, eight };

struct Block {
  Color blockColor;
  BingoNumber blockNumber;
};

struct BlockCircle {
  Color blockCircleColor;
  BingoNumber circleNumber;
  Block block;
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
  bool setBlockCircle(int x, int y, BlockCircle blockCircle);

  /**
   *  @param x [クロスサークルのx座標]
   *  @param y [クロスサークルのy座標]
   *  @param crossCircle [データ設定済みのCrossCircle構造体]
   */
  bool setCrossCircle(int x, int y, CrossCircle crossCircle);

  /**
   *  @param crossCircle [データ設定済みのCrossCircle構造体]
   */
  void setCardNumber(BingoNumber cardNumber);

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

  /**
   *  @param x [ブロックサークルの数字]
   *  @return [ブロックサークルの色]
   */
  Color getBlockCircleColorL(BingoNumber circleNumber);

  /**
   *  @param x [クロスサークルのx座標]
   *  @param y [クロスサークルのy座標]
   *  @return [クロスサークルの色]
   */
  Color getCrossCircleColorL(int x, int y);

  /**
   *  @param x [ブロックサークルの数字]
   *  @return [ブロックサークルの色]
   */
  Color getBlockCircleColorR(BingoNumber circleNumber);

  /**
   *  @param x [クロスサークルのx座標]
   *  @param y [クロスサークルのy座標]
   *  @return [クロスサークルの色]
   */
  Color getCrossCircleColorR(int x, int y);

 private:
  const int BlockCircleSize = 3;
  const int CrossCircleSize = 4;
  struct BlockCircle blockCircleCoordinate[3][3];
  struct CrossCircle crossCircleCoordinate[4][4];
  BingoNumber cardNumber = BingoNumber::none;
};

#endif
