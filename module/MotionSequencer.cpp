#include "MotionSequencer.h"

MotionSequencer::MotionSequencer(BlockBingoData& blockBingoData_) : blockBingoData(blockBingoData_)
{
}

Direction MotionSequencer::route2MotionCommand(vector<Coordinate> const& route,
                                               vector<MotionCommand>& motionCommandList)
{
  Coordinate currentCoordinate = route.front();
  Direction currentDirection = blockBingoData.getDirection();
  Coordinate nextCoordinate = currentCoordinate;
  Direction nextDirection = currentDirection;

  for(unsigned int i = 1; i < route.size(); i++) {
    nextCoordinate = route[i];
    nextDirection = blockBingoData.calcNextDirection(currentCoordinate, nextCoordinate);

    // 次の座標の方向を向く
    int rotationCount = calcRotationCount(currentDirection, nextDirection);
    if(rotationCount > 0) {
      // 時計回りに方向転換 MotionCommand::RTは時計回りに45°方向転換
      for(int count = 0; count < abs(rotationCount); count++) {
        motionCommandList.push_back(MotionCommand::RT);
      }
    } else if(rotationCount < 0) {
      // 反時計回りに方向転換 MotionCommand::RTは反時計回りに45°方向転換
      for(int count = 0; count < abs(rotationCount); count++) {
        motionCommandList.push_back(MotionCommand::RF);
      }
    }

    // 現在座標から次の座標へ移動する
    NodeType currentType = blockBingoData.checkNode(currentCoordinate);
    NodeType nextType = blockBingoData.checkNode(nextCoordinate);

    // 現在座標と次の座標の種類に応じて、移動方法を切り替える
    if(currentType == NodeType::crossCircle && nextType == NodeType::middlePoint) {
      // 交点サークルから中点への移動
      motionCommandList.push_back(MotionCommand::CM);
    } else if(currentType == NodeType::crossCircle && nextType == NodeType::blockCircle) {
      if(i == route.size() - 1 && blockBingoData.hasBlock(route.front())) {
        // 交点サークルからブロックサークルにブロックを設置
        motionCommandList.push_back(MotionCommand::SC);
      } else {
        // 交点サークルからブロックサークルのブロックを取得
        motionCommandList.push_back(MotionCommand::GC);
      }
    } else if(currentType == NodeType::middlePoint && nextType == NodeType::crossCircle) {
      // 中点から交点サークルへの移動
      motionCommandList.push_back(MotionCommand::MC);
    } else if(currentType == NodeType::middlePoint && nextType == NodeType::middlePoint) {
      // 中点から中点への移動
      motionCommandList.push_back(MotionCommand::MM);
    } else if(currentType == NodeType::middlePoint && nextType == NodeType::blockCircle) {
      if(i == route.size() - 1 && blockBingoData.hasBlock(route.front())) {
        // 中点からブロックサークルにブロックを設置
        motionCommandList.push_back(MotionCommand::SM);
      } else {
        // 中点からブロックサークルのブロックを取得
        motionCommandList.push_back(MotionCommand::GM);
      }
    } else if(currentType == NodeType::blockCircle && nextType == NodeType::crossCircle) {
      // ブロックサークルから交点サークルへの移動
      motionCommandList.push_back(MotionCommand::BC);
    } else if(currentType == NodeType::blockCircle && nextType == NodeType::middlePoint) {
      // ブロックサークルから中点への移動
      motionCommandList.push_back(MotionCommand::BM);
    }

    currentCoordinate = nextCoordinate;
    currentDirection = nextDirection;
  }
  return nextDirection;
}

int MotionSequencer::calcRotationCount(Direction currentDirection, Direction nextDirection)
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