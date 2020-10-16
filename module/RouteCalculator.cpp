/**
 *  @file	RouteCalculator.cpp
 *  @brief	経路計算をする
 *  @author	mutotaka0426, sugaken0528
 */
#include "RouteCalculator.h"

using namespace std;

RouteCalculator::RouteCalculator(BlockBingoData& blockBingoData_)
  : blockBingoData(blockBingoData_), gCoordinate(0, 0)
{
}

void RouteCalculator::solveBlockBingo(vector<Coordinate>& list, Coordinate startCoordinate,
                                      Coordinate goalCoordinate)
{
  vector<AStarProperty> open;
  vector<AStarProperty> close;
  struct AStarProperty elem({ 0, 0 }, 0);
  int actualCost;
  Route route[AREASIZE][AREASIZE];

  list.clear();
  gCoordinate = goalCoordinate;  // ゴールノードをセット

  route[startCoordinate.y][startCoordinate.x].set(startCoordinate, 0);
  route[startCoordinate.y][startCoordinate.x].currentDirection = blockBingoData.getDirection();
  open.push_back(
      AStarProperty(startCoordinate, route[startCoordinate.y][startCoordinate.x].currentCost
                                         + manhattanDistance(startCoordinate)));
  while(!open.empty()) {
    sort(open.begin(), open.end(), std::greater<AStarProperty>());
    elem = open.back();
    open.pop_back();
    if(elem.coordinate == gCoordinate) {
      break;
    }
    vector<AStarProperty> next = nextNode(elem.coordinate, route);
    for(const auto& m : next) {
      if((m.coordinate == route[elem.coordinate.y][elem.coordinate.x].parent)) {
        // 親ノードの場合はopenに追加しない
        // printf("(%d,%d)は親ノードだから除外した\n", m.x, m.y);
      } else if(blockCheck(m.coordinate)) {
        // ブロックがある場合はopenに追加しない
        // printf("(%d,%d)はブロックがあったから除外した\n", m.x, m.y);
      } else if(listCheck(m, open)) {
        // openにより大きいコストの同じ座標がある場合はopenから削除する
        // printf("(%d,%d)はオープンによりコストの小さいものがあったから除外した\n", m.x, m.y);
      } else if(listCheck(m, close)) {
        // closeにより大きいコストの同じ座標がある場合はcloseから削除する
        // printf("(%d,%d)はクローズによりコストの小さいものがあったから除外した\n", m.x, m.y);
      } else {
        actualCost = route[elem.coordinate.y][elem.coordinate.x].currentCost
                     + moveCost(elem.coordinate, m.coordinate, route);
        open.push_back(AStarProperty(m.coordinate, actualCost + manhattanDistance(m.coordinate)));
        route[m.coordinate.y][m.coordinate.x].set(elem.coordinate, actualCost);
        // printf("openに(%d,%d)を追加した(カレントコスト:%f,推定コスト:%f)\n", m.x, m.y,
        //     route[m.y][m.x].currentCost, m.estimateCost);
      }
    }
    close.push_back(elem);
  }

  setRoute(list, route, gCoordinate);
}

vector<AStarProperty> RouteCalculator::nextNode(Coordinate coordinate,
                                                Route route[AREASIZE][AREASIZE])
{
  vector<AStarProperty> nodeList;
  int nx, ny;

  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      if(i != 0 || j != 0) {
        nx = coordinate.x + i;
        ny = coordinate.y + j;
        if((nx >= 0) && (nx < AREASIZE) && (ny >= 0) && (ny < AREASIZE)) {
          nodeList.push_back(AStarProperty({ nx, ny }, route[coordinate.y][coordinate.x].currentCost
                                                           + moveCost(coordinate, { nx, ny }, route)
                                                           + manhattanDistance({ nx, ny })));
        }
      }
    }
  }
  return nodeList;
}

bool RouteCalculator::blockCheck(Coordinate coordinate)
{
  if(coordinate == gCoordinate) {
    return false;  // ゴールノードの場合はブロックがあっても避けない
  }
  // 交点サークルの場合
  if(blockBingoData.checkNode(coordinate) == NodeType::crossCircle) {
    CrossCircle crossCircle = blockBingoData.getCrossCircle(coordinate);
    if(crossCircle.block.blockColor != Color::none) {
      return true;  // ブロックがあるのでこのノードの処理を終える
    } else {
      return false;  // ブロックがないので次の処理に移る
    }
    // ブロックサークルの場合
  } else if(blockBingoData.checkNode(coordinate) == NodeType::blockCircle) {
    BlockCircle blockCircle = blockBingoData.getBlockCircle(coordinate);
    if(blockCircle.block.blockColor != Color::none) {
      return true;  //ブロックがあるのでこのノードの処理を終える
    } else {
      return false;  // ブロックがないので次の処理に移る
    }
  } else {
    return false;  //交点サークルでもブロックサークルでもない場合ブロックがないので次の処理に移る
  }
}

bool RouteCalculator::listCheck(AStarProperty node, vector<AStarProperty>& list)
{
  for(int i = 0; i < (int)list.size(); i++) {
    // listに既に同じノードがあるか調べる
    if(node.coordinate == list[i].coordinate) {
      if(node < list[i]) {
        list.erase(list.begin() + i);
        return false;  // listにすでにあるノードよりもコストが低いため、listから削除して次の処理に移る
      } else {
        return true;  // listにすでに同コストのノードがある場合はこのノードの処理を終える
      }
    }
  }
  return false;  // listにないノードなので次の処理に移る
}

int RouteCalculator::moveCost(Coordinate coordinate, Coordinate nextCoordinate,
                              Route route[AREASIZE][AREASIZE])
{
  int cost = 0;
  bool isNext = (coordinate.x == nextCoordinate.x) || (coordinate.y == nextCoordinate.y);
  bool blockCircleNode = (nextCoordinate.x % 2 == 1) && (nextCoordinate.y % 2 == 1);
  // castDirection[Y][X]で向くべき方向を返す
  int castDirection[3][3] = { { 3, 4, 5 }, { 2, -1, 6 }, { 1, 0, 7 } };
  int X, Y;

  if(isNext) {  //横縦移動の時
    cost += 1;
  } else {  //斜め移動の時
    cost += 6;
  }

  // ブロックサークルに侵入する場合コストを高く設定する
  if(blockCircleNode) {
    cost += 9;
  }

  // 回頭のコストの設定
  if(coordinate.x < nextCoordinate.x) {
    X = 0;
  } else if(coordinate.x == nextCoordinate.x) {
    X = 1;
  } else {
    X = 2;
  }
  if(coordinate.y < nextCoordinate.y) {
    Y = 0;
  } else if(coordinate.y == nextCoordinate.y) {
    Y = 1;
  } else {
    Y = 2;
  }
  // 回頭の角度差
  int diffAngle
      = abs((int)route[coordinate.y][coordinate.x].currentDirection - castDirection[Y][X]);
  // //printf("diffAngle:%d, X:%d, Y:%d, castDirection:%d\n", diffAngle, X, Y, castDirection[Y][X]);
  if(diffAngle > 4) {
    cost += 8 - diffAngle;
  } else {
    cost += diffAngle;
  }
  route[nextCoordinate.y][nextCoordinate.x].currentDirection = (Direction)castDirection[Y][X];

  if((nextCoordinate == gCoordinate)) {
    return 0;
  } else {
    return cost;
  }
}

int RouteCalculator::manhattanDistance(Coordinate coordinate)
{
  int diffX = abs(gCoordinate.x - coordinate.x);
  int diffY = abs(gCoordinate.y - coordinate.y);
  return diffX + diffY;
}

void RouteCalculator::setRoute(vector<Coordinate>& list, Route route[AREASIZE][AREASIZE],
                               Coordinate coordinate)
{
  // (x,y)を通っていないときのエラー処理
  if(route[coordinate.y][coordinate.x].parent == Coordinate{ -1, -1 }) {
    printf("[ERROR] This coordinate does not pass.\n");
  } else if(route[coordinate.y][coordinate.x].parent == coordinate) {  // スタートノードの場合
    list.push_back(coordinate);
  } else {
    setRoute(list, route, route[coordinate.y][coordinate.x].parent);
    list.push_back(coordinate);
  }
}
