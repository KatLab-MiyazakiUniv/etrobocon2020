/**
 *  @file  Navigator.cpp
 *  @brief 動作命令に従ってブロックビンゴエリアを走行する
 *  @author sugaken0528, arimakaoru
 */

#include "Navigator.h"

Navigator::Navigator(Controller& controller_, bool isLeftCourse_)
  : controller(controller_),
    isLeftCourse(isLeftCourse_),
    isLeftEdge(!isLeftCourse_),
    moveStraight(controller_),
    lineTracer(controller_, controller_.getTargetBrightness(), !isLeftCourse_),
    rotation(controller_)
{
}

void Navigator::execMotion(vector<MotionCommand> const& motionCommandList)
{
  for(unsigned int i = 0; i < motionCommandList.size(); i++) {
    MotionCommand motionCommand = motionCommandList[i];
    int countRepeated = 0;
    switch(motionCommand) {
      case MotionCommand::RT:
        // 連続するRTはまとめて回頭する
        countRepeated = countRepeatedCommand(motionCommandList, i);
        changeDirection(abs(45 * countRepeated), true);
        i += countRepeated - 1;
        break;
      case MotionCommand::RF:
        // 連続するRFはまとめて回頭する
        countRepeated = countRepeatedCommand(motionCommandList, i);
        changeDirection(abs(45 * countRepeated), false);
        i += countRepeated - 1;
        break;
      case MotionCommand::CM:
        moveC2M();
        break;
      case MotionCommand::GC:
        getBlockFromC();
        break;
      case MotionCommand::SC:
        setBlockFromC();
        break;
      case MotionCommand::MC:
        moveM2C();
        break;
      case MotionCommand::MM:
        moveM2M();
        break;
      case MotionCommand::GM:
        getBlockFromM();
        break;
      case MotionCommand::SM:
        setBlockFromM();
        break;
      case MotionCommand::BC:
        moveB2C();
        break;
      case MotionCommand::BM:
        moveB2M();
        break;
      default:
        break;
    }
    controller.tslpTsk(4000);
  }
}

void Navigator::enterStraight()
{
  lineTracer.runToColor(30, 0.2, 0.005, 0.01, 0.0);
  moveStraight.moveTo(110, 30);
  printf("ビンゴエリアにまっすぐ進入\n");
}

void Navigator::enterLeft()
{
  lineTracer.run({ 70, 30, 0.0, { 0.2, 0.005, 0.01 } });
  changeDirection(45, true);
  moveStraight.moveTo(215, 30);
}

void Navigator::enterRight()
{
  lineTracer.run({ 70, 30, 0.0, { 0.2, 0.005, 0.01 } });
  changeDirection(45, false);
  moveStraight.moveTo(215, 30);
}

int Navigator::countRepeatedCommand(vector<MotionCommand> const& motionCommandList, int startIndex)
{
  MotionCommand startCommand = motionCommandList[startIndex];
  int count = 1;
  for(unsigned int i = startIndex + 1; i < motionCommandList.size(); i++) {
    if(motionCommandList[i] != startCommand) break;
    count++;
  }
  return count;
}

void Navigator::changeDirection(unsigned int rotationAngle, bool clockwise)
{
  rotation.rotate(rotationAngle, clockwise, 15);
  printf("方向転換 %d° %d\n", rotationAngle, clockwise);
}

void Navigator::moveC2M()
{
  lineTracer.run({ 175, 30, 0.0, { 0.2, 0.005, 0.01 } });
  printf("交点サークルから中点への移動\n");
}

void Navigator::getBlockFromC()
{
  moveStraight.moveTo(186, 30);
  printf("交点サークルからブロックサークルのブロックを取得\n");
}

void Navigator::setBlockFromC()
{
  moveStraight.moveTo(185, 15);
  moveStraight.moveTo(-170, 15);
  printf("交点サークルからブロックサークルにブロックを設置\n");
}

void Navigator::moveM2C()
{
  lineTracer.runToColor(30, 0.2, 0.005, 0.01, 0.0);
  moveStraight.moveTo(100, 30);
  printf("中点から交点サークルへの移動\n");
}

void Navigator::moveM2M()
{
  moveStraight.moveTo(247, 30);
  printf("中点から中点への移動\n");
}

void Navigator::getBlockFromM()
{
  moveStraight.moveTo(145, 30);
  printf("中点からブロックサークルのブロックを取得\n");
}

void Navigator::setBlockFromM()
{
  moveStraight.moveTo(145, 30);
  moveStraight.moveTo(-145, 30);
  printf("中点からブロックサークルにブロックを設置\n");
}

void Navigator::moveB2C()
{
  moveStraight.moveTo(186, 30);
  printf("ブロックサークルから交点サークルへの移動\n");
}

void Navigator::moveB2M()
{
  moveStraight.moveTo(145, 30);
  printf("ブロックサークルから中点への移動\n");
}
