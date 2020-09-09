/**
 *  @file   BlockBingoData.cpp
 *  @brief ビンゴエリアのデータ構造を管理する
 *  @author mutotaka0426, sugaken0528, Takahiro55555
 */
#include "BlockBingoData.h"

BlockBingoData::BlockBingoData(Controller& controller_, bool isLeftCourse_)
  : controller(controller_), isLeftCourse(isLeftCourse_), cardNumber(-1)
{
}

bool BlockBingoData::setBlockCircle(int x, int y, BlockCircle blockCircle)
{
  if((x % 2 != 1) || (y % 2 != 1)) {
    printf("[ERROR] Not BlockCircle\n");
    return false;
  }

  //ブロックサークルの色のエラー処理
  if(blockCircle.blockCircleColor == Color::black || blockCircle.blockCircleColor == Color::white) {
    printf("[ERROR] Unexpected color\n");
    return false;
  }

  //ブロックの色のエラー処理
  if(blockCircle.block.blockColor == Color::white) {
    printf("[ERROR] Unexpected color\n");
    return false;
  }

  // 座標指定のエラー処理
  if((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
    return false;
  }

  // ブロック数字のエラー処理
  if((blockCircle.block.blockNumber <= 0) || (blockCircle.block.blockNumber > 8)) {
    if(blockCircle.block.blockNumber != -1) {
      return false;
    }
  }

  // 正常時
  blockCircleCoordinate[(y - 1) / 2][(x - 1) / 2] = blockCircle;
  return true;
}

bool BlockBingoData::setCrossCircle(int x, int y, CrossCircle crossCircle)
{
  if((x % 2 != 0) || (y % 2 != 0)) {
    printf("[ERROR] Not CrossCircle\n");
    return false;
  }

  //交点サークルの色のエラー処理
  if(crossCircle.crossCircleColor == Color::none || crossCircle.crossCircleColor == Color::black
     || crossCircle.crossCircleColor == Color::white) {
    printf("[ERROR] Unexpected color\n");
    return false;
  }

  //ブロックの色のエラー処理
  if(crossCircle.block.blockColor == Color::white) {
    printf("[ERROR] Unexpected color\n");
    return false;
  }

  // 座標指定のエラー処理
  if((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
    return false;
  }

  // ブロック数字のエラー処理
  if((crossCircle.block.blockNumber <= 0) || (crossCircle.block.blockNumber > 8)) {
    if(crossCircle.block.blockNumber != -1) {
      return false;
    }
  }

  // 正常時
  crossCircleCoordinate[y / 2][x / 2] = crossCircle;
  return true;
}

BlockCircle BlockBingoData::getBlockCircle(int x, int y)
{
  if((x % 2 != 1) || (y % 2 != 1)) {
    printf("[ERROR] Coordinate is not BlockCircle\n");
    return BlockCircle{ Color::none, -1, Block{ Color::none, -1 } };
  };

  return blockCircleCoordinate[(y - 1) / 2][(x - 1) / 2];
}

CrossCircle BlockBingoData::getCrossCircle(int x, int y)
{
  if((x % 2 != 0) || (y % 2 != 0)) {
    printf("[ERROR] Coordinate is not CrossCircle\n");
    return CrossCircle{ Color::none, Block{ Color::none, -1 } };
  };
  return crossCircleCoordinate[y / 2][x / 2];
}

int BlockBingoData::getCardNumber(void)
{
  return cardNumber;
}

void BlockBingoData::initBlockBingoData(void)
{
  int blockCircleNumber = 1;
  Color circleColor;                      //サークルの色を受け取る
  Block noneBlock = { Color::none, -1 };  // とりあえずすべてブロックなしでセット
  BlockCircle initBlockCircle;            // 初期化用の情報を保持する
  CrossCircle initCrossCircle;            // 初期化用の情報を保持する

  // ブロックサークルの初期化
  for(int j = 0; j < 7; j++) {
    for(int i = 0; i < 7; i++) {
      // 交点サークルの場合
      if((i % 2 == 0) && (j % 2 == 0)) {
        circleColor = getCrossCircleColor(i, j);
        initCrossCircle = CrossCircle{ circleColor, noneBlock };
        setCrossCircle(i, j, initCrossCircle);
        // ブロックサークルの場合
      } else if((i % 2 == 1) && (j % 2 == 1)) {
        if((i == 3) && (j == 3)) {  // 真ん中のブロックサークルはすべてnone
          initBlockCircle = BlockCircle{ Color::none, -1, noneBlock };
        } else {
          circleColor = getBlockCircleColor(blockCircleNumber);
          initBlockCircle = BlockCircle{ circleColor, blockCircleNumber, noneBlock };
          blockCircleNumber++;
        }
        setBlockCircle(i, j, initBlockCircle);
      }
    }
  }

  // 数字カードの初期化
  initCardNumber(controller.getCourseInfo(ETROBOC_COURSE_INFO_CARD_NUMBER));

  // ブロックの初期位置を設定する
  initBlock(Color::black, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_BLACK1));
  initBlock(Color::black, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_BLACK2));
  initBlock(Color::red, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_RED1));
  initBlock(Color::red, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_RED2));
  initBlock(Color::yellow, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW1));
  initBlock(Color::yellow, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW2));
  initBlock(Color::blue, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_BLUE1));
  initBlock(Color::blue, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_BLUE2));
  initBlock(Color::green, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_GREEN1));
  initBlock(Color::green, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_GREEN2));
}

void BlockBingoData::initCardNumber(int cardNumber_)
{
  cardNumber = cardNumber_;
}

void BlockBingoData::initBlock(Color initColor, int coordinate)
{
  int x, y;
  BlockCircle blockCircle;
  CrossCircle crossCircle;

  switch(coordinate) {
      // ブロックサークル
    case 1:
      x = 1, y = 1;
      break;
    case 2:
      x = 3, y = 1;
      break;
    case 3:
      x = 5, y = 1;
      break;
    case 4:
      x = 0, y = 3;
      break;
    case 5:
      x = 5, y = 3;
      break;
    case 6:
      x = 0, y = 5;
      break;
    case 7:
      x = 3, y = 5;
      break;
    case 8:
      x = 5, y = 5;
      break;

      // 交点サークル
    case 65:
      x = 0, y = 0;
      break;
    case 67:
      x = 4, y = 0;
      break;
    case 70:
      x = 2, y = 2;
      break;
    case 72:
      x = 6, y = 2;
      break;
    case 74:
      x = 0, y = 4;
      break;
    case 76:
      x = 4, y = 4;
      break;
    case 81:
      x = 2, y = 6;
      break;
    case 83:
      x = 6, y = 6;
      break;
    default:
      x = -1, y = -1;
  }

  if((coordinate > 0) && (coordinate <= 8)) {
    blockCircle = getBlockCircle(x, y);
    blockCircle.block.blockColor = initColor;
    setBlockCircle(x, y, blockCircle);
  } else {
    crossCircle = getCrossCircle(x, y);
    crossCircle.block.blockColor = initColor;
    setCrossCircle(x, y, crossCircle);
  }
}

Color BlockBingoData::getBlockCircleColor(int circleNumber)
{
  // ブロックサークルにない数字の時のエラー処理
  if((circleNumber < 1) && (circleNumber > 8)) {
    return Color::none;
  }
  return isLeftCourse ? blockCircleColorL[circleNumber - 1] : blockCircleColorR[circleNumber - 1];
}

Color BlockBingoData::getCrossCircleColor(int x, int y)
{
  // 座標が範囲外の時のエラー処理
  if((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
    return Color::none;
  }
  // 交点サークルではない時のエラー処理
  if((x % 2 != 0) || (y % 2 != 0)) {
    return Color::none;
  }

  return isLeftCourse ? crossCircleColorL[y / 2][x / 2] : crossCircleColorR[y / 2][x / 2];
}

