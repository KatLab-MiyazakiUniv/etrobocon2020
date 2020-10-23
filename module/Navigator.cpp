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

void Navigator::execMotion(vector<MotionCommand> const& motionCommandList)
{
  for(unsigned int i = 0; i < motionCommandList.size(); i++) {
    controller.resetMotorCount();
    //
    int armCount;
    while((armCount = controller.getArmMotorCount()) != -45) {
      if(armCount < -45) {
        controller.setArmMotorPwm(50);
      } else {
        controller.setArmMotorPwm(-50);
      }
      controller.tslpTsk(4000);
    }
    controller.setArmMotorPwm(0);
    //

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
    controller.stopMotor();
    while(!controller.touchSensor.isPressed()) {
      controller.tslpTsk(4000);
    }
  }
}

void Navigator::enterStraight()
{
  controller.resetMotorCount();
  lineTracer.runToColor(30, 0.2, 0.005, 0.01, 0.0);
  // moveStraight.moveTo(80, 100);
  printf("ビンゴエリアにまっすぐ進入\n");
}

void Navigator::enterLeft()
{
  lineTracer.run({ 70, 30, 0.0, { 0.2, 0.005, 0.01 } });
  changeDirection(45, false);
  moveStraight.moveTo(215, 30);
}

void Navigator::enterRight()
{
  lineTracer.run({ 70, 30, 0.0, { 0.2, 0.005, 0.01 } });
  changeDirection(45, true);
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
  if(rotationAngle == 45) {
    moveStraight.moveTo(Color::black, 15);
    rotation.rotate(rotationAngle, clockwise, 15);
  } else if(rotationAngle == 90) {
    rotation.pivotTurn(rotationAngle, clockwise, 30);
    // エッジをclockwiseにする(右ピボット＝右エッジ)
  } else if(rotationAngle == 135) {
    rotation.pivotTurn(90, clockwise, 30);
    rotation.rotate(45, clockwise, 15);
  } else if(rotationAngle == 180) {
    rotation.pivotTurn(90, clockwise, 30);
    rotation.rotate(90, clockwise, 15);
    // エッジを逆にする
  }
  // rotation.rotate(rotationAngle, clockwise, 15);
  printf("方向転換 %d° %d\n", rotationAngle, clockwise);
}

void Navigator::moveC2M()
{
  moveStraight.moveTo(Color::black, 15);
  lineTracer.run({ 50, 30, 0.0, { 0.2, 0.005, 0.01 } });
  printf("交点サークルから中点への移動\n");
}

void Navigator::getBlockFromC()
{
  moveStraight.moveTo(230, 30);
  printf("交点サークルからブロックサークルのブロックを取得\n");
}

void Navigator::setBlockFromC()
{
  moveStraight.moveTo(150, 15);
  moveStraight.moveTo(-160, 15);
  printf("交点サークルからブロックサークルにブロックを設置\n");
}

void Navigator::moveM2C()
{
  lineTracer.runToColor(30, 0.2, 0.005, 0.01, 0.0);
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
  moveStraight.moveTo(100, 30);
  moveStraight.moveTo(-100, 30);
  printf("中点からブロックサークルにブロックを設置\n");
}

void Navigator::moveB2C()
{
  moveStraight.moveTo(186, 30);
  printf("ブロックサークルから交点サークルへの移動\n");
}

void Navigator::moveB2M()
{
  moveStraight.moveTo(185, 30);
  printf("ブロックサークルから中点への移動\n");
}
