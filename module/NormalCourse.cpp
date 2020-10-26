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
  // printf("runNormalCourse\n");
  // 配列の個数
  constexpr int arraySize = 18;
  constexpr int baseSpeed = 100;
  constexpr std::array<NormalCourseProperty, arraySize> normalCoursePropertyL
      /**
       * 詳しく見たいならLineTracer.hを見てね．
       * 進む距離，目標スピード，曲率，ターンpid
       * 曲率は、直進のとき0.0を指定する
       */
      = {{
          { 250, baseSpeed - 40, 0.0, { 0.25, 0.005, 0.03 } },         // 第1区間
          { 355, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },               // 第1区間
          { 1050, baseSpeed - 30, 0.003226, { 0.6, 0.005, 0.05 } },     // 第2区間
          { 325, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },               // 第3区間
          { 1180, baseSpeed - 30, -0.002941, { 0.6, 0.005, 0.05 } },  // 第4区間
          { 530, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },               // 第5区間
          { 500, baseSpeed - 30, -0.004167, { 0.6, 0.005, 0.05 } },  // 第6区間
          { 500, baseSpeed, 0.0, { 0.4, 0.005, 0.03 } },              // 第7区間
          { 730, baseSpeed - 30, 0.002439, { 0.6, 0.005, 0.05} },     // 第8区間
          { 125, baseSpeed, 0.0, { 0.5, 0.005, 0.05 } },                // 第9区間
          { 650, baseSpeed - 30, 0.002439, { 0.6, 0.005, 0.05 } },     // 第10区間
          { 380, baseSpeed, 0.0, { 0.4, 0.005, 0.03 } },               // 第11区間
          { 750, baseSpeed - 30, 0.002778, { 0.6, 0.005, 0.05 } },     // 第12区間
          { 1520, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },               // 第13区間
          { 620, baseSpeed - 30, -0.004167, { 0.6, 0.005, 0.05 } },   // 第14区間
          { 870, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },                //進入ライン
          { 850, baseSpeed - 30, -0.00204081, { 0.6, 0.005, 0.05 } },  // ゴール後 カーブ
          { 305, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },                // ゴール後 第3区間
      } };
  constexpr std::array<NormalCourseProperty, arraySize> normalCoursePropertyR
      /**
       * 詳しく見たいならLineTracer.hを見てね．
       * 進む距離，目標スピード，曲率，ターンpid
       * 曲率は、直進のとき0.0を指定する
       */
    = { {
          { 250, baseSpeed - 40, 0.0, { 0.25, 0.005, 0.03 } },         // 第1区間
          { 355, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },               // 第1区間
          { 1050, baseSpeed - 30, -0.003226, { 0.6, 0.005, 0.05 } },     // 第2区間
          { 325, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },               // 第3区間
          { 1180, baseSpeed - 30, 0.002941, { 0.6, 0.005, 0.05 } },  // 第4区間
          { 530, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },               // 第5区間
          { 500, baseSpeed - 30, 0.004167, { 0.6, 0.005, 0.05 } },  // 第6区間
          { 500, baseSpeed, 0.0, { 0.4, 0.005, 0.03 } },              // 第7区間
          { 730, baseSpeed - 30, -0.002439, { 0.6, 0.005, 0.05} },     // 第8区間
          { 125, baseSpeed, 0.0, { 0.5, 0.005, 0.05 } },                // 第9区間
          { 650, baseSpeed - 30, -0.002439, { 0.6, 0.005, 0.05 } },     // 第10区間
          { 380, baseSpeed, 0.0, { 0.4, 0.005, 0.03 } },               // 第11区間
          { 750, baseSpeed - 30, -0.002778, { 0.6, 0.005, 0.05 } },     // 第12区間
          { 1520, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },               // 第13区間
          { 620, baseSpeed - 30, 0.004167, { 0.6, 0.005, 0.05 } },   // 第14区間
          { 870, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },                //進入ライン
          { 850, baseSpeed - 30, 0.00204081, { 0.6, 0.005, 0.05 } },  // ゴール後 カーブ
          { 305, baseSpeed, 0.0, { 0.25, 0.005, 0.03 } },                // ゴール後 第3区間
      } };

  // LコースならLコースのPID値を採用する。RコースならRコースのPID値を採用する。
  const std::array<NormalCourseProperty, arraySize> normalCourseProperty
      = isLeftCourse ? normalCoursePropertyL : normalCoursePropertyR;
  LineTracer lineTracer(controller, targetBrightness, isLeftCourse);
  MoveStraight movestraight(controller);
  Rotation rotation(controller);
  for(const auto& ncp : normalCourseProperty) {
    lineTracer.run(ncp);
  }

  // ブロックビンゴエリア手前の黄色サークルまで移動する
  lineTracer.runToSpecifiedColor(Color::yellow, 20, 0.15, 0.0, 0.005, 0.0);

  // 位置を微調整し、機体をブロックビンゴエリアの方向へ向かせる
  movestraight.moveTo(50);
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
