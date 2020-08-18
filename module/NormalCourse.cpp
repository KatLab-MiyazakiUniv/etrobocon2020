/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author sugaken0528
 */
#include "NormalCourse.h"

/** コンストラクタ
 *  @param controller [コントローラのインスタンス]
 *  @param isLeftCourse_ [エッジがどっちかtrueがLeftコース]
 *  @param targetBrightness_ [カラーセンサーの目標値]
 */
NormalCourse::NormalCourse(Controller& controller_, bool isLeftCourse_, int targetBrightness_)
  : controller(controller_), isLeftCourse(isLeftCourse_), targetBrightness(targetBrightness_)
{
}

/**
 * 左エッジ，右エッジを切り替える．
 * @param isLeftCourse_ [Leftコースである場合True]
 */
void NormalCourse::setIsLeftCourse(bool isLeftCourse_)
{
  isLeftCourse = isLeftCourse_;
}

/**
 * 実際にNormalコースを走る．
 * ここにパラメータを頑張って書く．
 */
void NormalCourse::runNormalCourse()
{
  printf("runNormalCourse\n");
  // 配列の個数
  constexpr int arraySize = 1;
  constexpr int baseSpeed = 100;
  constexpr std::array<NormalCourseProperty, arraySize> normalCoursePropertyL
      /**
       * 詳しく見たいならLineTracer.hを見てね．
       * 進む距離，目標スピード，曲率，ターンpid
       * 曲率は、直進のとき0.0を指定する
       */
      = { {
          //{ 820, baseSpeed, 0.0, { 0.1, 0.005, 0.01 } },            // 第1区間
          //{ 1195, baseSpeed, 0.003226, { 0.375, 0.005, 0.0125 } },  // 第2区間
          //{ 320, baseSpeed, 0.0, { 0.1, 0.005, 0.01 } },            // 第3区間
          //{ 1310, baseSpeed, -0.002941, { 0.373, 0.005, 0.009 } },  // 第4区間
          //{ 620, baseSpeed, 0.0, { 0.1, 0.005, 0.01 } },            // 第5区間
          //{ 500, baseSpeed, -0.004167, { 0.45, 0.005, 0.011 } },    // 第6区間
          //{ 590, baseSpeed, 0.0, { 0.1, 0.005, 0.01 } },            // 第7区間
          //{ 710, baseSpeed, 0.002439, { 0.356, 0.002, 0.008 } },    // 第8区間
          //{ 163, baseSpeed, 0.0, { 0.1, 0.005, 0.01 } },            // 第9区間
          //{ 740, baseSpeed, 0.002439, { 0.356, 0.002, 0.008 } },    // 第10区間
          //{ 520, baseSpeed, 0.0, { 0.1, 0.005, 0.01 } },            // 第11区間
          //{ 680, baseSpeed, 0.002778, { 0.358, 0.002, 0.008 } },    // 第12区間
          //{ 1613, baseSpeed, 0.0, { 0.1, 0.005, 0.03 } },           // 第13区間
          //{ 530, baseSpeed, -0.004167, { 0.45, 0.005, 0.025 } },    // 第14区間
          { 355, 70, 0.0, { 0.1, 0.005, 0.02 } },  //進入ライン
      } };
  constexpr std::array<NormalCourseProperty, arraySize> normalCoursePropertyR
      /**
       * 詳しく見たいならLineTracer.hを見てね．
       * 進む距離，目標スピード，曲率，ターンpid
       * 曲率は、直進のとき0.0を指定する
       */
      = { {
          //{ 820, baseSpeed + 10, 0.0, { 0.10, 0.005, 0.01 } },  // 第1区間
          //{ 1160, baseSpeed, -0.00322, { 0.4, 0.0, 0.02 } },    // 第2区間
          //{ 330, baseSpeed, 0.0, { 0.10, 0.0, 0.01 } },         // 第3区間
          //{ 1320, baseSpeed, 0.00294, { 0.5, 0.005, 0.01 } },   // 第4区間
          //{ 650, baseSpeed, 0.0, { 0.12, 0.005, 0.01 } },       // 第5区間
          //{ 500, baseSpeed, 0.00416, { 0.65, 0.005, 0.02 } },   // 第6区間
          //{ 550, baseSpeed, 0.0, { 0.1, 0.005, 0.01 } },        // 第7区間
          //{ 1650, baseSpeed, -0.00243, { 0.4, 0.005, 0.02 } },  // 第8区間
          //{ 480, baseSpeed, 0.0, { 0.1, 0.005, 0.01 } },        // 第9区間
          //{ 650, baseSpeed, -0.00277, { 0.35, 0.005, 0.02 } },  // 第10区間
          //{ 1640, baseSpeed, 0.0, { 0.2, 0.005, 0.01 } },       // 第11区間
          //{ 470, baseSpeed, 0.00416, { 0.68, 0.005, 0.03 } },   // 第12区間
          //{ 1700, baseSpeed, 0.0, { 0.2, 0.005, 0.01 } },       // 第13区間
          //{ 2085, 1 + 10, 0.0, { 0.4, 0.005, 0.03 } },          // 第14区間
          { 355, 70, 0.0, { 0.1, 0.005, 0.02 } },  // 進入ライン
      } };

  // LコースならLコースのPID値を採用する。RコースならRコースのPID値を採用する。
  const std::array<NormalCourseProperty, arraySize> normalCourseProperty
      = isLeftCourse ? normalCoursePropertyL : normalCoursePropertyR;
  LineTracer lineTracer(controller, targetBrightness, isLeftCourse);
  for(const auto& ncp : normalCourseProperty) {
    lineTracer.run(ncp);
  }
  Rotation rotation(controller);
  rotation.pivotTurn(90, isLeftCourse, 50);
}

/**
 * 現在のisLeftCourse（エッジ）を返すゲッター
 */
bool NormalCourse::getIsLeftCourse() const
{
  return isLeftCourse;
}

/**
 * targetBrightness（カラーセンサの目標値）を返すゲッター
 */
int NormalCourse::getTargetBrightness() const
{
  return targetBrightness;
}