/**
 *  @file	BlockBingo.h
 *  @brief	ビンゴエリアを攻略する
 *  @author	mutotaka0426, sugaken0528
 */
#include "BlockBingo.h"
BlockBingo::BlockBingo(Controller& controller_, bool isLeftCourse_, BlockBingoData& blockBingoData_)
  : controller(controller_), isLeftCourse(isLeftCourse_), blockBingoData(blockBingoData_)
{
}

void BlockBingo::run(void)
{
  this->initBlockBingoData();
  // ここにビンゴエリアの処理を書く
}

void BlockBingo::initBlockBingoData(void)
{
  int i, j;  // i=x, j=y
  int blockCircleNumber = 1;
  BingoNumber castNumber;  // blockCircleNumberをBingoNumberにキャストした値を代入
  Color circleColor;       //サークルの色を受け取る
  Block tempBlock = { Color::none, BingoNumber::none };  // とりあえずすべてnoneでセット
  BlockCircle tempBlockCircle;                           // 初期化用の情報を保持する
  CrossCircle tempCrossCircle;                           // 初期化用の情報を保持する
  int tempNumber;                                        // 数字カードの値を受け取る

  // ブロックサークルの初期化
  for(j = 0; j < 3; j++) {
    for(i = 0; i < 3; i++) {
      // 真ん中のブロックサークルはすべてnone
      if((i == 1) && (j == 1)) {
        tempBlockCircle = BlockCircle{ Color::none, BingoNumber::none, tempBlock };
      } else {
        castNumber = static_cast<BingoNumber>(blockCircleNumber);
        circleColor = isLeftCourse ? blockBingoData.getBlockCircleColorL(castNumber)
                                   : blockBingoData.getBlockCircleColorR(castNumber);
        tempBlockCircle = BlockCircle{ circleColor, castNumber, tempBlock };
        blockCircleNumber++;
      }
      blockBingoData.setBlockCircle(i, j, tempBlockCircle);
    }
  }

  // 交点サークルの初期化
  for(j = 0; j < 4; j++) {
    for(i = 0; i < 4; i++) {
      circleColor = isLeftCourse ? blockBingoData.getCrossCircleColorL(i, j)
                                 : blockBingoData.getCrossCircleColorR(i, j);
      tempCrossCircle = CrossCircle{ circleColor, tempBlock };
      blockBingoData.setCrossCircle(i, j, tempCrossCircle);
    }
  }

  // 数字カードの初期化
  tempNumber = controller.getCourseInfo(ETROBOC_COURSE_INFO_CARD_NUMBER);
  blockBingoData.setCardNumber(static_cast<BingoNumber>(tempNumber));

  // ブロックの初期位置を設定する
  this->initBlock(Color::black, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_BLACK1));
  this->initBlock(Color::black, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_BLACK2));
  this->initBlock(Color::red, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_RED1));
  this->initBlock(Color::red, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_RED2));
  this->initBlock(Color::yellow, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW1));
  this->initBlock(Color::yellow, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW2));
  this->initBlock(Color::blue, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_BLUE1));
  this->initBlock(Color::blue, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_BLUE2));
  this->initBlock(Color::green, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_GREEN1));
  this->initBlock(Color::green, controller.getCourseInfo(ETROBOC_COURSE_INFO_BLOCK_POS_GREEN2));
}

void BlockBingo::initBlock(Color initColor, int coordinate)
{
  int x, y;
  BlockCircle tempBlockCircle;
  CrossCircle tempCrossCircle;

  switch(coordinate) {
      // ブロックサークル
    case 1:
      x = 0, y = 0;
      break;
    case 2:
      x = 1, y = 0;
      break;
    case 3:
      x = 2, y = 0;
      break;
    case 4:
      x = 0, y = 1;
      break;
    case 5:
      x = 2, y = 1;
      break;
    case 6:
      x = 0, y = 2;
      break;
    case 7:
      x = 1, y = 2;
      break;
    case 8:
      x = 2, y = 2;
      break;

      // 交点サークル
    case 65:
      x = 0, y = 0;
      break;
    case 67:
      x = 2, y = 0;
      break;
    case 70:
      x = 1, y = 1;
      break;
    case 72:
      x = 3, y = 1;
      break;
    case 74:
      x = 0, y = 2;
      break;
    case 76:
      x = 2, y = 2;
      break;
    case 81:
      x = 1, y = 3;
      break;
    case 83:
      x = 3, y = 3;
      break;
    default:
      x = -1, y = -1;
  }

  if((coordinate > 0) && (coordinate <= 8)) {
    tempBlockCircle = blockBingoData.getBlockCircle(x, y);
    tempBlockCircle.block.blockColor = initColor;
    blockBingoData.setBlockCircle(x, y, tempBlockCircle);
  } else {
    tempCrossCircle = blockBingoData.getCrossCircle(x, y);
    tempCrossCircle.block.blockColor = initColor;
    blockBingoData.setCrossCircle(x, y, tempCrossCircle);
  }
}
