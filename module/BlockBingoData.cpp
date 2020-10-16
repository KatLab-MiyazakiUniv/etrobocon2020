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

NodeType BlockBingoData::checkNode(Coordinate coordinate)
{
  if((coordinate.x % 2 == 0) && (coordinate.y % 2 == 0)) {
    return NodeType::crossCircle;
  } else if((coordinate.x % 2 == 1) && (coordinate.y % 2 == 1)) {
    return NodeType::blockCircle;
  } else {
    return NodeType::middlePoint;
  }
}

bool BlockBingoData::setBlockCircle(Coordinate coordinate, BlockCircle blockCircle)
{
  if(checkNode(coordinate) != NodeType::blockCircle) {
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
  if((coordinate.x < 0) || (coordinate.x >= 7) || (coordinate.y < 0) || (coordinate.y >= 7)) {
    return false;
  }

  // ブロック数字のエラー処理
  if((blockCircle.block.blockNumber <= 0) || (blockCircle.block.blockNumber > 8)) {
    if(blockCircle.block.blockNumber != -1) {
      return false;
    }
  }

  // 正常時
  blockCircleCoordinate[(coordinate.y - 1) / 2][(coordinate.x - 1) / 2] = blockCircle;
  return true;
}

bool BlockBingoData::setCrossCircle(Coordinate coordinate, CrossCircle crossCircle)
{
  if(checkNode(coordinate) != NodeType::crossCircle) {
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
  if((coordinate.x < 0) || (coordinate.x >= 7) || (coordinate.y < 0) || (coordinate.y >= 7)) {
    return false;
  }

  // ブロック数字のエラー処理
  if((crossCircle.block.blockNumber <= 0) || (crossCircle.block.blockNumber > 8)) {
    if(crossCircle.block.blockNumber != -1) {
      return false;
    }
  }

  // 正常時
  crossCircleCoordinate[coordinate.y / 2][coordinate.x / 2] = crossCircle;
  return true;
}

BlockCircle BlockBingoData::getBlockCircle(Coordinate coordinate)
{
  if(checkNode(coordinate) != NodeType::blockCircle) {
    printf("[ERROR] Coordinate is not BlockCircle\n");

    return BlockCircle{ Color::none, -1, Block{ Color::none, -1 } };
  }

  return blockCircleCoordinate[(coordinate.y - 1) / 2][(coordinate.x - 1) / 2];
}

CrossCircle BlockBingoData::getCrossCircle(Coordinate coordinate)
{
  if(checkNode(coordinate) != NodeType::crossCircle) {
    printf("[ERROR] Coordinate is not CrossCircle\n");
    return CrossCircle{ Color::none, Block{ Color::none, -1 } };
  }

  return crossCircleCoordinate[coordinate.y / 2][coordinate.x / 2];
}

int BlockBingoData::getCardNumber(void)
{
  return cardNumber;
}

void BlockBingoData::setDirection(Direction direction_)
{
  direction = direction_;
}

Direction BlockBingoData::getDirection(void)
{
  return direction;
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
      if(checkNode(Coordinate(i, j)) == NodeType::crossCircle) {
        circleColor = getCrossCircleColor(Coordinate(i, j));
        initCrossCircle = CrossCircle{ circleColor, noneBlock };
        setCrossCircle({ i, j }, initCrossCircle);
        // ブロックサークルの場合
      } else if(checkNode(Coordinate(i, j)) == NodeType::blockCircle) {
        if((i == 3) && (j == 3)) {  // 真ん中のブロックサークルはすべてnone
          initBlockCircle = BlockCircle{ Color::none, -1, noneBlock };
        } else {
          circleColor = getBlockCircleColor(blockCircleNumber);
          initBlockCircle = BlockCircle{ circleColor, blockCircleNumber, noneBlock };
          blockCircleNumber++;
        }
        setBlockCircle({ i, j }, initBlockCircle);
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
  Coordinate initCoordinate;
  BlockCircle blockCircle;
  CrossCircle crossCircle;

  switch(coordinate) {
      // ブロックサークル
    case 49:  // 1のとき
      initCoordinate = { 1, 1 };
      break;
    case 50:  // 2のとき
      initCoordinate = { 3, 1 };
      break;
    case 51:  // 3のとき
      initCoordinate = { 5, 1 };
      break;
    case 52:  // 4のとき
      initCoordinate = { 0, 3 };
      break;
    case 53:  // 5のとき
      initCoordinate = { 5, 3 };
      break;
    case 54:  // 6のとき
      initCoordinate = { 0, 5 };
      break;
    case 55:  // 7のとき
      initCoordinate = { 3, 5 };
      break;
    case 56:  // 8のとき
      initCoordinate = { 5, 5 };
      break;

      // 交点サークル
    case 65:  // Aのとき
      initCoordinate = { 0, 0 };
      break;
    case 67:  // Cのとき
      initCoordinate = { 4, 0 };
      break;
    case 70:  // Fのとき
      initCoordinate = { 2, 2 };
      break;
    case 72:  // Hのとき
      initCoordinate = { 6, 2 };
      break;
    case 74:  // Jのとき
      initCoordinate = { 0, 4 };
      break;
    case 76:  // Lのとき
      initCoordinate = { 4, 4 };
      break;
    case 81:  // Qのとき
      initCoordinate = { 2, 6 };
      break;
    case 83:  // Sのとき
      initCoordinate = { 6, 6 };
      break;
    default:
      initCoordinate = { -1, -1 };
      break;
  }

  if((coordinate >= 49) && (coordinate <= 56)) {
    blockCircle = getBlockCircle(initCoordinate);
    blockCircle.block.blockColor = initColor;
    setBlockCircle(initCoordinate, blockCircle);
  } else {
    crossCircle = getCrossCircle(initCoordinate);
    crossCircle.block.blockColor = initColor;
    setCrossCircle(initCoordinate, crossCircle);
  }
}

Color BlockBingoData::getBlockCircleColor(int circleNumber)
{
  // ブロックサークルにない数字の時のエラー処理
  if((circleNumber < 1) || (circleNumber > 8)) {
    return Color::none;
  }
  return isLeftCourse ? blockCircleColorL[circleNumber - 1] : blockCircleColorR[circleNumber - 1];
}

Color BlockBingoData::getCrossCircleColor(Coordinate coordinate)
{
  // 座標が範囲外の時のエラー処理
  if((coordinate.x < 0) || (coordinate.x >= 7) || (coordinate.y < 0) || (coordinate.y >= 7)) {
    return Color::none;
  }
  // 交点サークルではない時のエラー処理
  if(checkNode(coordinate) != NodeType::crossCircle) {
    return Color::none;
  }

  return isLeftCourse ? crossCircleColorL[coordinate.y / 2][coordinate.x / 2]
                      : crossCircleColorR[coordinate.y / 2][coordinate.x / 2];
}
