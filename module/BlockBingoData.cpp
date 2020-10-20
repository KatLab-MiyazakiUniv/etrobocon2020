/**
 *  @file   BlockBingoData.cpp
 *  @brief ビンゴエリアのデータ構造を管理する
 *  @author mutotaka0426, sugaken0528, Takahiro55555
 */
#include "BlockBingoData.h"

BlockBingoData::BlockBingoData(Controller& controller_, bool isLeftCourse_)
  : controller(controller_),
    isLeftCourse(isLeftCourse_),
    cardNumber(-1),
    coordinate(isLeftCourse ? Coordinate(2, 6) : Coordinate(4, 6))
{
}

NodeType BlockBingoData::checkNode(Coordinate coordinate)
{
  if((coordinate.x < 0) || (coordinate.x >= 7) || (coordinate.y < 0) || (coordinate.y >= 7)) {
    return NodeType::none;
  } else if((coordinate.x % 2 == 0) && (coordinate.y % 2 == 0)) {
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

  if((coordinate >= 49) && (coordinate <= 56)) {
    initCoordinate = initBlockCircleCoordinate[coordinate - 49];
    blockCircle = getBlockCircle(initCoordinate);
    blockCircle.block.blockColor = initColor;
    setBlockCircle(initCoordinate, blockCircle);
  } else if((coordinate >= 65) && (coordinate <= 83)) {
    // 交点サークル
    switch(coordinate) {
      case 65:  // Aのとき
        initCoordinate = { 0, 0 };
        break;
      case 66:  // Bのとき
        initCoordinate = { 2, 0 };
        break;
      case 67:  // Cのとき
        initCoordinate = { 4, 0 };
        break;
      case 68:  // Dのとき
        initCoordinate = { 6, 0 };
        break;
      case 69:  // Eのとき
        initCoordinate = { 0, 2 };
        break;
      case 70:  // Fのとき
        initCoordinate = { 2, 2 };
        break;
      case 71:  // Gのとき
        initCoordinate = { 4, 2 };
        break;
      case 72:  // Hのとき
        initCoordinate = { 6, 2 };
        break;
      case 74:  // Jのとき
        initCoordinate = { 0, 4 };
        break;
      case 75:  // Kのとき
        initCoordinate = { 2, 4 };
        break;
      case 76:  // Lのとき
        initCoordinate = { 4, 4 };
        break;
      case 77:  // Mのとき
        initCoordinate = { 6, 4 };
        break;
      case 80:  // Pのとき
        initCoordinate = { 0, 6 };
        break;
      case 81:  // Qのとき
        initCoordinate = { 2, 6 };
        break;
      case 82:  // Rのとき
        initCoordinate = { 4, 6 };
        break;
      case 83:  // Sのとき
        initCoordinate = { 6, 6 };
        break;
      default:
        initCoordinate = { -1, -1 };
        printf("[ERROR] Faild initBlock");
        break;
    }
    crossCircle = getCrossCircle(initCoordinate);
    crossCircle.block.blockColor = initColor;
    setCrossCircle(initCoordinate, crossCircle);
  } else {
    printf("[ERROR] Faild initBlock");
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

Direction BlockBingoData::calcNextDirection(Coordinate const& currentCoordinate,
                                            Coordinate const& nextCoordinate)
{
  int xDiff = nextCoordinate.x - currentCoordinate.x;
  int yDiff = nextCoordinate.y - currentCoordinate.y;

  if(xDiff < 0) {
    if(yDiff < 0) {
      return Direction::NWest;
    } else if(yDiff == 0) {
      return Direction::West;
    } else {
      return Direction::SWest;
    }
  } else if(xDiff == 0) {
    if(yDiff <= 0) {
      // currentCoordinate == nextCoordinatteのときもNorthを返す
      return Direction::North;
    } else {
      return Direction::South;
    }
  } else {
    if(yDiff < 0) {
      return Direction::NEast;
    } else if(yDiff == 0) {
      return Direction::East;
    } else {
      return Direction::SEast;
    }
  }
}

bool BlockBingoData::moveBlock(Coordinate const& coordinateFrom, Coordinate const& coordinateTo)
{
  Block temp;
  NodeType nodeTypeFrom = checkNode(coordinateFrom);
  NodeType nodeTypeTo = checkNode(coordinateTo);
  // 運搬元にブロックがない
  if(!hasBlock(coordinateFrom)) {
    printf("[ERROR] Don't have block\n");
    return false;
  }

  Block blockFrom = getBlock(coordinateFrom);
  if(nodeTypeFrom == NodeType::crossCircle) {
    temp = crossCircleCoordinate[coordinateFrom.y / 2][coordinateFrom.x / 2].block;
    crossCircleCoordinate[coordinateFrom.y / 2][coordinateFrom.x / 2].block = { Color::none, -1 };
  } else if(nodeTypeFrom == NodeType::blockCircle) {
    temp = blockCircleCoordinate[(coordinateFrom.y - 1) / 2][(coordinateFrom.x - 1) / 2].block;
    blockCircleCoordinate[coordinateFrom.y / 2][coordinateFrom.x / 2].block = { Color::none, -1 };
  }

  if(blockFrom.blockColor == Color::black) {
    // 黒ブロックは運搬しても運搬先の座標情報を書き換えない
    return true;
  } else {
    if(nodeTypeTo == NodeType::crossCircle) {
      crossCircleCoordinate[coordinateTo.y / 2][coordinateTo.x / 2].block = temp;
    } else if(nodeTypeTo == NodeType::blockCircle) {
      blockCircleCoordinate[(coordinateTo.y - 1) / 2][(coordinateTo.x - 1) / 2].block = temp;
    }
    return true;
  }
}

bool BlockBingoData::setBlock(Coordinate const& coordinate, Block block)
{
  if(coordinate.x % 2 == 0 && coordinate.y % 2 == 0) {
    crossCircleCoordinate[coordinate.y / 2][coordinate.x / 2].block = block;
    return true;
  } else if(coordinate.x % 2 == 1 && coordinate.y % 2 == 1) {
    blockCircleCoordinate[(coordinate.y - 1) / 2][(coordinate.x - 1) / 2].block = block;
    return true;
  } else {
    return false;
  }
}

Block BlockBingoData::getBlock(Coordinate const& coordinate)
{
  NodeType nodeType = checkNode(coordinate);
  if(nodeType == NodeType::crossCircle) {
    return crossCircleCoordinate[coordinate.y / 2][coordinate.x / 2].block;
  } else if(nodeType == NodeType::blockCircle) {
    return blockCircleCoordinate[(coordinate.y - 1) / 2][(coordinate.x - 1) / 2].block;
  } else {
    return Block();
  }
}

bool BlockBingoData::hasBlock(Coordinate const& coordinate)
{
  if(getBlock(coordinate).blockColor == Color::none) {
    return false;
  } else {
    return true;
  }
}

Coordinate BlockBingoData::getCoordinate()
{
  return coordinate;
}

bool BlockBingoData::setCoordinate(Coordinate coordinate_)
{
  if(checkNode(coordinate) != NodeType::none) {
    coordinate = coordinate_;
    return true;
  } else {
    printf("[ERROR] This coordinate is not of range\n");
    return false;
  }
}

Coordinate BlockBingoData::numberToCoordinate(int circleNumber)
{
  return initBlockCircleCoordinate[circleNumber - 1];
}

int BlockBingoData::calcRotationCount(Direction currentDirection, Direction nextDirection)
{
  constexpr int numDirection = 8;
  int diffDirection = static_cast<int>(nextDirection) - static_cast<int>(currentDirection);

  if(diffDirection > numDirection / 2) {
    diffDirection -= numDirection;
  } else if(diffDirection < -numDirection / 2) {
    diffDirection += numDirection;
  }

  return diffDirection;
}
