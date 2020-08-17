/**
 *  @file  Navigator.cpp
 *  @brief ビンゴエリアを走る
 *  @author sugaken0528
 */

#include "Navigator.h"

Navigator::Navigator(Controller& controller_, bool isLeftCourse_, int targetBrightness_)
  : controller(controller_), isLeftCourse(isLeftCourse_), targetBrightness(targetBrightness_)
{
}

void Navigator::traceBingoArea(bool isRightEdge)
{
  LineTracer lineTracer(controller, targetBrightness, isRightEdge);
  double pGain = 0.1;
  double iGain = 0.005;
  double dGain = 0.01;
  int basespeed = 70;
  int distance = 255;
  // 開始位置: Lコース(x: 13.43 y: z: 12.2 rot: 180)
  NormalCourseProperty property = { distance, basespeed, 0.0, { PGain, IGain, DGain } };
  lineTracer.run(property);
}
