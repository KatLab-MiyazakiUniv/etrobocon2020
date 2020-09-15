/**
 *  @file	RouteCalculator.cpp
 *  @brief	経路計算をする
 *  @author	mutotaka0426, sugaken0528
 */
#include "RouteCalculator.h"

using namespace std;

RouteCalculator::RouteCalculator(BlockBingoData& blockBingoData_) : blockBingoData(blockBingoData_)
{
}

void RouteCalculator::solveBlockBingo(vector<vector<int>>& list, int sx, int sy, int gx, int gy)
{
  // vector<vector<int>> list;  // 戻り値用配列
  vector<AStarProperty> open;
  vector<AStarProperty> close;
  struct AStarProperty elem(0, 0, 0.0);
  int actualCost;
  Route route[7][7];

  list.clear();
  gX = gx;  // ゴールノードをセット
  gY = gy;

  route[sy][sx].set(sx, sy, 0.0);
  route[sy][sx].currentDirection = blockBingoData.getDirection();
  open.push_back(AStarProperty(sx, sy, route[sy][sx].currentCost + euclideanDistance(sx, sy)));
  while(!open.empty()) {
    sort(open.begin(), open.end(), std::greater<AStarProperty>());
    elem = open.back();
    open.pop_back();
    if(elem.x == gX && elem.y == gY) {
      break;
    }
    vector<AStarProperty> next = nextNode(elem.x, elem.y, route[elem.y][elem.x].currentCost, route);
    for(const auto& m : next) {
      if((m.x == route[elem.y][elem.x].px) && (m.y == route[elem.y][elem.x].py)) {
        // 親ノードの場合はopenに追加しない
        // printf("(%d,%d)は親ノードだから除外した\n", m.x, m.y);
      } else if(blockCheck(m.x, m.y)) {
        // ブロックがる場合はopenに追加しない
        // printf("(%d,%d)はブロックがあったから除外した\n", m.x, m.y);
      } else if(listCheck(m, open)) {
        // openにより大きいコストの同じ座標がある場合はopenを更新する
        // printf("(%d,%d)はオープンによりコストの小さいものがあったから除外した\n", m.x, m.y);
      } else if(listCheck(m, close)) {
        // closeにより小さいコストの同じ座標がある場合はopenに追加しない
        // printf("(%d,%d)はクローズによりコストの小さいものがあったから除外した\n", m.x, m.y);
      } else {
        actualCost = route[elem.y][elem.x].currentCost + moveCost(elem.x, elem.y, m.x, m.y, route);
        open.push_back(AStarProperty(m.x, m.y, actualCost + euclideanDistance(m.x, m.y)));
        route[m.y][m.x].set(elem.x, elem.y, actualCost);
        // printf("openに(%d,%d)を追加した(カレントコスト:%f,推定コスト:%f)\n", m.x, m.y,
        //     route[m.y][m.x].currentCost, m.estimateCost);
      }
    }
    close.push_back(elem);
  }

  setRoute(list, route, gX, gY);
}

vector<AStarProperty> RouteCalculator::nextNode(int x, int y, double currentCost, Route route[7][7])
{
  vector<AStarProperty> nodeList;
  int nx, ny;

  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      if(i != 0 || j != 0) {
        nx = x + i, ny = y + j;
        if((nx >= 0) && (nx < 7) && (ny >= 0) && (ny < 7)) {
          nodeList.push_back(AStarProperty(
              nx, ny, currentCost + moveCost(x, y, nx, ny, route) + euclideanDistance(nx, ny)));
        }
      }
    }
  }
  return nodeList;
}

bool RouteCalculator::blockCheck(int x, int y)
{
  if((x == gX) && (y == gY)) {
    return false;  // ゴールノードの場合はブロックがあっても避けない
  }
  // 交点サークルの場合
  if((x % 2 == 0) && (y % 2 == 0)) {
    CrossCircle crossCircle = blockBingoData.getCrossCircle(x, y);
    if(crossCircle.block.blockColor != Color::none) {
      return true;  // ブロックがあるのでこのノードの処理を終える
    } else {
      return false;  // ブロックがないので次の処理に移る
    }
    // ブロックサークルの場合
  } else if((x % 2 == 1) && (y % 2 == 1)) {
    BlockCircle blockCircle = blockBingoData.getBlockCircle(x, y);
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
    if((node.x == list[i].x) && (node.y == list[i].y)) {
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

int RouteCalculator::moveCost(int x, int y, int nx, int ny, Route route[7][7])
{
  int cost = 0;
  bool nextNode = (x == nx) || (y == ny);
  bool blockCircleNode = (nx % 2 == 1) && (ny % 2 == 1);
  // castDirection[Y][X]で向くべき方向を返す
  int castDirection[3][3] = { { 3, 4, 5 }, { 2, -1, 6 }, { 1, 0, 7 } };
  int X, Y;

  if(nextNode) {  //横縦移動の時
    cost += 1;
  } else {  //斜め移動の時
    if(blockCheck(x, ny) || blockCheck(nx, y)) {
      cost += 1;  // 隣にブロックがあるときコストを高く設定する
    }
    cost += 6;
  }

  // ブロックサークルに侵入する場合コストを高く設定する
  if(blockCircleNode) {
    if((nx != gX) || (ny != gY)) cost += 9;  // ゴールの場合は高く設定しなくてよい
  }

  // 回頭のコストの設定
  if(x < nx) {
    X = 0;
  } else if(x == nx) {
    X = 1;
  } else {
    X = 2;
  }
  if(y < ny) {
    Y = 0;
  } else if(y == ny) {
    Y = 1;
  } else {
    Y = 2;
  }
  // 回頭の角度差
  int diffAngle = abs((int)route[y][x].currentDirection - castDirection[Y][X]);
  // //printf("diffAngle:%d, X:%d, Y:%d, castDirection:%d\n", diffAngle, X, Y, castDirection[Y][X]);
  if(diffAngle > 4) {
    cost += 8 - diffAngle;
  } else {
    cost += diffAngle;
  }
  route[ny][nx].currentDirection = (Direction)castDirection[Y][X];

  if((nx == gX) && (ny == gY)) {
    return 0;
  } else {
    return cost;
  }
}

double RouteCalculator::euclideanDistance(int nx, int ny)
{
  return sqrt(pow((gX - nx), 2) + pow((gY - ny), 2));
}

void RouteCalculator::setRoute(vector<vector<int>>& list, Route route[7][7], int x, int y)
{
  // (x,y)を通っていないときのエラー処理
  if((route[y][x].px == -1) && (route[y][x].py == -1)) {
    list.push_back({ x, y });
    printf("[ERROR] This coordinate does not pass.\n");
  } else if((route[y][x].px == x) && (route[y][x].py == y)) {  // スタートノードの場合
    list.push_back({ x, y });
  } else {
    setRoute(list, route, route[y][x].px, route[y][x].py);
    list.push_back({ x, y });
  }
}
