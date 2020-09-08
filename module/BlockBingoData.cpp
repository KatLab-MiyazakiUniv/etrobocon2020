/**
 *  @file   BlockBingoData.cpp
 *  @brief ビンゴエリアのデータ構造を管理する
 *  @author mutotaka0426, sugaken0528, Takahiro55555
 */
#include "BlockBingoData.h"

bool BlockBingoData::setBlockCircle(int x, int y, BlockCircle blockCircle)
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

bool BlockBingoData::setCrossCircle(int x, int y, CrossCircle crossCircle)
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

void BlockBingoData::setCardNumber(BingoNumber cardNumber_)
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

Color BlockBingoData::getBlockCircleColorL(BingoNumber circleNumber)
{
  switch(circleNumber) {
    case BingoNumber::one:
    case BingoNumber::five:
      return Color::yellow;
    case BingoNumber::two:
    case BingoNumber::six:
      return Color::green;
    case BingoNumber::three:
    case BingoNumber::seven:
      return Color::red;
    case BingoNumber::four:
    case BingoNumber::eight:
      return Color::blue;
    default:
      return Color::none;
  }
}

Color BlockBingoData::getCrossCircleColorL(int x, int y)
{
  if((x >= 0) && (x < 2) && (y >= 0) && (y < 2)) {
    return Color::red;
  } else if((x >= 2) && (x < 4) && (y >= 0) && (y < 2)) {
    return Color::blue;
  } else if((x >= 0) && (x < 2) && (y >= 2) && (y < 4)) {
    return Color::yellow;
  } else if((x >= 2) && (x < 4) && (y >= 2) && (y < 4)) {
    return Color::green;
  } else {
    return Color::none;
  }
}

Color BlockBingoData::getBlockCircleColorR(BingoNumber circleNumber)
{
  switch(circleNumber) {
    case BingoNumber::one:
    case BingoNumber::seven:
      return Color::red;
    case BingoNumber::two:
    case BingoNumber::eight:
      return Color::green;
    case BingoNumber::three:
    case BingoNumber::four:
      return Color::yellow;
    case BingoNumber::five:
    case BingoNumber::six:
      return Color::blue;
    default:
      return Color::none;
  }
}

Color BlockBingoData::getCrossCircleColorR(int x, int y)
{
  if((x >= 0) && (x < 2) && (y >= 0) && (y < 2)) {
    return Color::blue;
  } else if((x >= 2) && (x < 4) && (y >= 0) && (y < 2)) {
    return Color::red;
  } else if((x >= 0) && (x < 2) && (y >= 2) && (y < 4)) {
    return Color::green;
  } else if((x >= 2) && (x < 4) && (y >= 2) && (y < 4)) {
    return Color::yellow;
  } else {
    return Color::none;
  }
}

