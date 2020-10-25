#include "MotionSequencer.h"

MotionSequencer::MotionSequencer(Controller& controller_, bool isLeftCourse_,
                                 BlockBingoData& blockBingoData_)
  : navigator(controller_, isLeftCourse_), blockBingoData(blockBingoData_)
{
}

Direction MotionSequencer::route2Motion(vector<Coordinate> const& route,
                                        vector<MotionCommand>& motionCommandList)
{
  Coordinate currentCoordinate = route.front();
  Direction currentDirection = blockBingoData.getDirection();
  Coordinate nextCoordinate = currentCoordinate;
  Direction nextDirection = currentDirection;
  bool hasBlock = blockBingoData.hasBlock(currentCoordinate);

  for(unsigned int i = 1; i < route.size(); i++) {
    nextCoordinate = route[i];
    nextDirection = blockBingoData.calcNextDirection(currentCoordinate, nextCoordinate);
    NodeType currentType = blockBingoData.checkNode(currentCoordinate);
    NodeType nextType = blockBingoData.checkNode(nextCoordinate);

    // 次の座標の方向を向く
    int rotationCount = blockBingoData.calcRotationCount(currentDirection, nextDirection);
    int rotationAngle = abs(rotationCount) * 45;
    bool clockwise = rotationCount >= 0;
    if(hasBlock && currentType == NodeType::crossCircle) {
      navigator.changeDirectionWithBlock(rotationAngle, clockwise);
      if(rotationCount == 0) {
        motionCommandList.push_back(MotionCommand::RNWB);
      } else if(clockwise) {
        for(int i = 0; i < rotationCount; i++) motionCommandList.push_back(MotionCommand::RTWB);
      } else {
        for(int i = 0; i < rotationCount; i++) motionCommandList.push_back(MotionCommand::RFWB);
      }
    } else if(rotationAngle > 0) {
      navigator.changeDirection(rotationAngle, clockwise);
      if(clockwise) {
        for(int i = 0; i < rotationCount; i++) motionCommandList.push_back(MotionCommand::RT);
      } else {
        for(int i = 0; i < rotationCount; i++) motionCommandList.push_back(MotionCommand::RF);
      }
    }

    // 現在座標から次の座標へ移動する。現在座標と次の座標の種類に応じて、移動方法を切り替える
    if(currentType == NodeType::crossCircle && nextType == NodeType::middlePoint) {
      // 交点サークルから中点への移動
      if(hasBlock) {
        navigator.moveC2MWithBlock();
        motionCommandList.push_back(MotionCommand::CMWB);
      } else {
        navigator.moveC2M();
        motionCommandList.push_back(MotionCommand::CM);
      }
    } else if(currentType == NodeType::crossCircle && nextType == NodeType::blockCircle) {
      if(i == route.size() - 1 && hasBlock) {
        // 交点サークルからブロックサークルにブロックを設置
        navigator.setBlockFromC(rotationAngle, clockwise);
        motionCommandList.push_back(MotionCommand::SC);
        if(rotationAngle == 135) {
          nextDirection = blockBingoData.calcNextDirection(
              currentCoordinate, Coordinate(nextCoordinate.x, currentCoordinate.y));
        }
      } else {
        // 交点サークルからブロックサークルのブロックを取得
        navigator.getBlockFromC();
        motionCommandList.push_back(MotionCommand::GC);
      }
    } else if(currentType == NodeType::middlePoint && nextType == NodeType::crossCircle) {
      // 中点から交点サークルへの移動
      if(hasBlock) {
        navigator.moveM2CWithBlock();
        motionCommandList.push_back(MotionCommand::MCWB);
      } else {
        navigator.moveM2C();
        motionCommandList.push_back(MotionCommand::MC);
      }
    } else if(currentType == NodeType::middlePoint && nextType == NodeType::middlePoint) {
      // 中点から中点への移動
      navigator.moveM2M();
      motionCommandList.push_back(MotionCommand::MM);
    } else if(currentType == NodeType::middlePoint && nextType == NodeType::blockCircle) {
      if(i == route.size() - 1 && hasBlock) {
        // 中点からブロックサークルにブロックを設置
        navigator.setBlockFromM();
        motionCommandList.push_back(MotionCommand::SM);
      } else {
        // 中点からブロックサークルのブロックを取得
        navigator.getBlockFromM();
        motionCommandList.push_back(MotionCommand::GM);
      }
    } else if(currentType == NodeType::blockCircle && nextType == NodeType::crossCircle) {
      // ブロックサークルから交点サークルへの移動
      navigator.moveB2C();
      motionCommandList.push_back(MotionCommand::BC);
    } else if(currentType == NodeType::blockCircle && nextType == NodeType::middlePoint) {
      // ブロックサークルから中点への移動
      navigator.moveB2M();
      motionCommandList.push_back(MotionCommand::BM);
    }

    currentCoordinate = nextCoordinate;
    currentDirection = nextDirection;
  }
  return nextDirection;
}
