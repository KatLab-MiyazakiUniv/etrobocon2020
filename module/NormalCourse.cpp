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
  constexpr int arraySize = 15;
  constexpr int baseSpeed = 100;
  constexpr std::array<NormalCourseProperty, arraySize> normalCoursePropertyL
      /**
       * 詳しく見たいならLineTracer.hを見てね．
       * 進む距離，目標スピード，曲率，ターンpid
       * 曲率は、直進のとき0.0を指定する
       */
      = { {
          { 730, baseSpeed, 0.0, { 0.5, 0.005, 0.2 } },             // 第1区間
          { 1000, baseSpeed, 0.003226, { 0.55, 0.005, 1.5 } },      // 第2区間
          { 290, baseSpeed, 0.0, { 0.2, 0.005, 0.01 } },            // 第3区間
          { 1000, baseSpeed, -0.002941, { 0.55, 0.005, 0.55 } },    // 第4区間
          { 530, baseSpeed, 0.0, { 0.25, 0.005, 0.05 } },           // 第5区間
          { 350, baseSpeed - 30, -0.004167, { 0.48, 0.33, 0.6 } },  // 第6区間
          { 490, baseSpeed, 0.0, { 0.25, 0.005, 0.7 } },            // 第7区間
          { 630, baseSpeed, 0.002439, { 0.65, 0.02, 1.5 } },        // 第8区間
          { 175, baseSpeed, 0.0, { 0.35, 0.05, 0.7 } },             // 第9区間]
          { 585, baseSpeed, 0.002439, { 0.55, 0.02, 0.8 } },        // 第10区間
          { 390, baseSpeed, 0.0, { 0.2, 0.005, 0.4 } },             // 第11区間
          { 620, baseSpeed, 0.002778, { 0.5, 0.02, 1.5 } },         // 第12区間
          { 1410, baseSpeed, 0.0, { 0.25, 0.0, 0.4 } },             // 第13区間
          { 520, baseSpeed - 30, -0.004167, { 0.48, 0.00, 0.5 } },  // 第14区間
          { 740, baseSpeed, 0.0, { 0.2, 0.01, 0.4 } },              //進入ライン
      } };
  constexpr std::array<NormalCourseProperty, arraySize> normalCoursePropertyR
      /**
       * 詳しく見たいならLineTracer.hを見てね．
       * 進む距離，目標スピード，曲率，ターンpid
       * 曲率は、直進のとき0.0を指定する
       */
      = { {
          { 720, baseSpeed, 0.0, { 0.4, 0.005, 0.2 } },            // 第1区間
          { 950, baseSpeed, -0.003226, { 0.55, 0.005, 1.5 } },     // 第2区間
          { 350, baseSpeed, 0.0, { 0.2, 0.005, 0.01 } },           // 第3区間
          { 1030, baseSpeed, 0.002941, { 0.55, 0.005, 0.55 } },    // 第4区間
          { 560, baseSpeed, 0.0, { 0.25, 0.005, 0.05 } },          // 第5区間
          { 370, baseSpeed - 30, 0.004167, { 0.48, 0.33, 0.6 } },  // 第6区間
          { 480, baseSpeed, 0.0, { 0.25, 0.005, 0.5 } },           // 第7区間
          { 620, baseSpeed, -0.002439, { 0.65, 0.02, 1.5 } },      // 第8区間
          { 150, baseSpeed, 0.0, { 0.35, 0.05, 0.7 } },            // 第9区間]
          { 580, baseSpeed, -0.002439, { 0.55, 0.02, 0.8 } },      // 第10区間
          { 390, baseSpeed, 0.0, { 0.2, 0.005, 0.4 } },            // 第11区間
          { 630, baseSpeed, -0.002778, { 0.5, 0.02, 1.5 } },       // 第12区間
          { 1410, baseSpeed, 0.0, { 0.25, 0.0, 0.4 } },            // 第13区間
          { 510, baseSpeed - 30, 0.004167, { 0.48, 0.00, 0.5 } },  // 第14区間
          { 740, baseSpeed, 0.0, { 0.2, 0.01, 0.4 } },
      } };

  // LコースならLコースのPID値を採用する。RコースならRコースのPID値を採用する。
  const std::array<NormalCourseProperty, arraySize> normalCourseProperty
      = isLeftCourse ? normalCoursePropertyL : normalCoursePropertyR;
  LineTracer lineTracer(controller, targetBrightness, isLeftCourse);
  for(const auto& ncp : normalCourseProperty) {
    lineTracer.run(ncp);
  }
  Rotation rotation(controller);
  rotation.rotate(90, isLeftCourse);
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
