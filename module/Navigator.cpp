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
  lineTracer.runToColor(30, 0.25, 0.005, 0.01, 0.0);
  printf("ビンゴエリアにまっすぐ進入\n");
}

void Navigator::enterLeft()
{
<<<<<<< HEAD
  controller.resetMotorCount();
  lineTracer.run({ 70, 30, 0.0, { 0.25, 0.005, 0.01 } });
=======
  controller.keepArm();
  moveStraight.moveTo(70);
>>>>>>> 3877747a92e24cf6de781c5d9d8b8ec029e233ba
  changeDirection(45, false, 100, false);
  moveStraight.moveTo(250, 30);
  printf("ビンゴエリアに左から進入\n");
}

void Navigator::enterRight()
{
<<<<<<< HEAD
  controller.resetMotorCount();
  lineTracer.run({ 70, 30, 0.0, { 0.25, 0.005, 0.01 } });
=======
  controller.keepArm();
  moveStraight.moveTo(70);
>>>>>>> 3877747a92e24cf6de781c5d9d8b8ec029e233ba
  changeDirection(45, true, 100, false);
  moveStraight.moveTo(250, 30);
  printf("ビンゴエリアに右から進入\n");
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
    rotationAngle += correction;
  }
  rotation.rotate(rotationAngle, clockwise, pwm);
  // printf("方向転換 %d° clockwise:%d\n", rotationAngle, clockwise);
}

void Navigator::changeDirectionWithBlock(unsigned int rotationAngle, bool clockwise)
{
  if(rotationAngle == 0) {
    moveStraight.moveTo(250, 30);
    // printf("方向転換withBlock %d° %d\n", rotationAngle, clockwise);
  } else if(rotationAngle == 90) {
    rotation.pivotTurn(rotationAngle, clockwise, 30);
    lineTracer.setIsLeftEdge(!clockwise);
    // printf("方向転換withBlock %d° %d\n", rotationAngle, clockwise);
  } else if(rotationAngle == 180) {
    moveStraight.moveTo(40, 30);
    rotation.rotate(rotationAngle, clockwise, 10);
    // printf("方向転換withBlock %d° %d\n", rotationAngle, clockwise);
    lineTracer.setIsLeftEdge(!lineTracer.getIsLeftEdge());
  } else {
    // 何もしない
  }
  // rotation.rotate(rotationAngle, clockwise, 15);
}

void Navigator::moveC2M()
{
<<<<<<< HEAD
  
  lineTracer.run({ 175, 30, 0.0, { 0.25, 0.005, 0.01 } });
=======
  lineTracer.run({ 175, 30, 0.0, { 0.3, 0.005, 0.01 } });
>>>>>>> 3877747a92e24cf6de781c5d9d8b8ec029e233ba
  // printf("交点サークルから中点への移動\n");
}

void Navigator::moveC2MWithBlock()
{
<<<<<<< HEAD
  
  lineTracer.run({ 100, 30, 0.0, { 0.25, 0.005, 0.01 } });
=======
  lineTracer.run({ 100, 30, 0.0, { 0.3, 0.005, 0.01 } });
>>>>>>> 3877747a92e24cf6de781c5d9d8b8ec029e233ba
  // printf("交点サークルから中点への移動withBlock\n");
}

void Navigator::getBlockFromC()
{
  moveStraight.moveTo(270, 30);
  // printf("交点サークルからブロックサークルのブロックを取得\n");
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
  // printf("交点サークルからブロックサークルにブロックを設置 angle:%d clockwise:%d\n",
  // rotationAngle,
  //  clockwise);
}

void Navigator::moveM2C()
{
<<<<<<< HEAD
  
  lineTracer.runToColor(30, 0.25, 0.005, 0.01, 0.0);
=======
  lineTracer.runToColor(30, 0.3, 0.005, 0.01, 0.0);
>>>>>>> 3877747a92e24cf6de781c5d9d8b8ec029e233ba
  moveStraight.moveTo(90, 30);
  // printf("中点から交点サークルへの移動\n");
}

void Navigator::moveM2CWithBlock()
{
<<<<<<< HEAD
  
  lineTracer.runToColor(30, 0.25, 0.005, 0.01, 0.0);
=======
  lineTracer.runToColor(30, 0.3, 0.005, 0.01, 0.0);
>>>>>>> 3877747a92e24cf6de781c5d9d8b8ec029e233ba
  // printf("中点から交点サークルへの移動withBlock\n");
}

void Navigator::moveM2M()
{
  moveStraight.moveTo(247, 30);
  // printf("中点から中点への移動\n");
}

void Navigator::getBlockFromM()
{
  moveStraight.moveTo(145, 30);
  // printf("中点からブロックサークルのブロックを取得\n");
}

void Navigator::setBlockFromM()
{
  moveStraight.moveTo(125, 30);
  controller.tslpTsk(500000);
  moveStraight.moveTo(-125, 30);
  // printf("中点からブロックサークルにブロックを設置\n");
}

void Navigator::moveB2C()
{
  moveStraight.moveTo(186, 30);
  // printf("ブロックサークルから交点サークルへの移動\n");
}

void Navigator::moveB2M()
{
  moveStraight.moveTo(145, 30);
  // printf("ブロックサークルから中点への移動\n");
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
