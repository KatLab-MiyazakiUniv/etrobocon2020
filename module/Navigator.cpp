/**
 *  @file  Navigator.cpp
 *  @brief 動作命令に従ってブロックビンゴエリアを走行する
 *  @author sugaken0528, arimakaoru
 */

#include "Navigator.h"

Navigator::Navigator(Controller& controller_, bool isLeftCourse_)
  : controller(controller_),
    isLeftCourse(isLeftCourse_),
    moveStraight(controller_),
    lineTracer(controller_, controller_.getTargetBrightness(), isLeftCourse_),
    rotation(controller_)
{
}

void Navigator::enterStraight()
{
  controller.keepArm();
  controller.resetMotorCount();
  lineTracer.runToColor(30, 0.3, 0.005, 0.01, 0.0);
}

void Navigator::enterLeft()
{
  controller.keepArm();
  moveStraight.moveTo(50);
  changeDirection(40, false, 100, false);
  moveStraight.moveTo(260, 30);
  lineTracer.setIsLeftEdge(true);
}

void Navigator::enterRight()
{
  controller.keepArm();
  moveStraight.moveTo(50);
  changeDirection(40, true, 100, false);
  moveStraight.moveTo(240, 30);
  lineTracer.setIsLeftEdge(false);
}

void Navigator::changeDirection(unsigned int rotationAngle, bool clockwise, int pwm,
                                bool needCorrection)
{
  int correction = 0;
  if(needCorrection) {
    int correction
        = (clockwise || lineTracer.getIsLeftEdge()) && (!clockwise || !lineTracer.getIsLeftEdge())
              ? 5
              : -5;
  }
  rotation.rotate(rotationAngle + correction, clockwise, pwm);
  if(rotationAngle == 180) {
    lineTracer.setIsLeftEdge(!lineTracer.getIsLeftEdge());
  }
}

void Navigator::changeDirectionWithBlock(unsigned int rotationAngle, bool clockwise)
{
  if(rotationAngle == 0) {
    moveStraight.moveTo(180, 30);
  } else if(rotationAngle == 90) {
    rotation.pivotTurn(rotationAngle, clockwise, 30);
    lineTracer.setIsLeftEdge(!clockwise);
  } else if(rotationAngle == 180) {
    moveStraight.moveTo(40, 30);
    rotation.rotate(rotationAngle, clockwise, 10);
    lineTracer.setIsLeftEdge(!lineTracer.getIsLeftEdge());
  } else {
    // 何もしない
  }
  // rotation.rotate(rotationAngle, clockwise, 15);
}

void Navigator::moveC2M()
{
  lineTracer.run({ 175, 30, 0.0, { 0.3, 0.005, 0.01 } });
}

void Navigator::moveC2MWithBlock()
{
  lineTracer.run({ 100, 30, 0.0, { 0.3, 0.005, 0.01 } });
}

void Navigator::getBlockFromC()
{
  moveStraight.moveTo(255, 30);
}

void Navigator::setBlockFromC(int rotationAngle, bool clockwise)
{
  if(rotationAngle == 45) {
    moveStraight.moveTo(50, 30);
    rotation.pivotTurnArm(45, clockwise, 60);
    lineTracer.setIsLeftEdge(!clockwise);
  } else if(rotationAngle == 135) {
    rotation.pivotTurn(180, clockwise, 30);
    rotation.pivotTurnBack(90, !clockwise, 30);
    moveStraight.moveTo(-50, 30);
    lineTracer.setIsLeftEdge(!clockwise);
  } else {
    // なし
  }
}

void Navigator::moveM2C()
{
  lineTracer.runToColor(30, 0.3, 0.005, 0.01, 0.0);
  moveStraight.moveTo(90, 30);
}

void Navigator::moveM2CWithBlock()
{
  lineTracer.runToColor(30, 0.3, 0.005, 0.01, 0.0);
}

void Navigator::moveM2M()
{
  moveStraight.moveTo(247, 30);
}

void Navigator::getBlockFromM()
{
  moveStraight.moveTo(145, 30);
}

void Navigator::setBlockFromM()
{
  moveStraight.moveTo(125, 30);
  controller.tslpTsk(500000);
  moveStraight.moveTo(-125, 30);
}

void Navigator::moveB2C()
{
  moveStraight.moveTo(186, 30);
}

void Navigator::moveB2M()
{
  moveStraight.moveTo(135, 30);
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
