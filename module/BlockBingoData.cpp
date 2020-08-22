/**
 *  @file   BlockBingoData.cpp
 *  @brief ビンゴエリアのデータ構造を管理する
 *  @author mutotaka0426, sugaken0528, Takahiro55555
 */
#include "BlockBingoData.h"

bool BlockBingoData::initBlockCircle(int x, int y, BlockCircle blockCircle)
{
  //ブロックサークルの色のエラー処理
  if(blockCircle.blockCircleColor == Color::black || blockCircle.blockCircleColor == Color::white) {
    printf("[ERROR] Unexpected color\n");
    return false;
  }

  //ブロックの色のエラー処理
  if(blockCircle.block.blockColor == Color::white) {
    return false;
  }

  // 座標指定のエラー処理
  if((x < 0) || (x >= BlockCircleSize) || (y < 0) || (y >= BlockCircleSize)) {
    return false;
  }

  // 正常時
  blockCircleCoordinate[x][y] = blockCircle;
  return true;
}

bool BlockBingoData::initCrossCircle(int x, int y, CrossCircle crossCircle)
{
  //交点サークルの色のエラー処理
  if(crossCircle.crossCircleColor == Color::none || crossCircle.crossCircleColor == Color::black
     || crossCircle.crossCircleColor == Color::white) {
    printf("[ERROR] Unexpected color\n");
    return false;
  }

  //ブロックの色のエラー処理
  if(crossCircle.block.blockColor == Color::white) {
    return false;
  }

  // 座標指定のエラー処理
  if((x < 0) || (x >= CrossCircleSize) || (y < 0) || (y >= CrossCircleSize)) {
    return false;
  }
  // 正常時
  crossCircleCoordinate[x][y] = crossCircle;
  return true;
}

void BlockBingoData::initCardNumber(BingoNumber cardNumber_)
{
  cardNumber = cardNumber_;
}

BlockCircle BlockBingoData::getBlockCircle(int x, int y)
{
  return blockCircleCoordinate[x][y];
}

CrossCircle BlockBingoData::getCrossCircle(int x, int y)
{
  return crossCircleCoordinate[x][y];
}

BingoNumber BlockBingoData::getCardNumber(void)
{
  return cardNumber;
}
