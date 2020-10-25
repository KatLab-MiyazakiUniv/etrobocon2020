/**
 *  @file   MotionSequencerTest.cpp
 *  @brief  MotionSequencerクラスのテストファイル
 *  @author Arima Kaoru
 */
#include "MotionSequencer.h"
#include <gtest/gtest.h>

namespace etrobocon2020_test {
  TEST(MotionSequencer, route2MotionCommand)
  {
    // Controller controller;
    // bool isLeftCourse = true;
    // BlockBingoData blockBingoData(controller, isLeftCourse);
    // blockBingoData.initBlockBingoData();
    // MotionSequencer motionSequencer(blockBingoData);

    // // (2,6)の青ブロックを(4,4)に設置
    // vector<Coordinate> route = { { 2, 6 }, { 3, 6 }, { 4, 6 }, { 5, 5 } };
    // vector<MotionCommand> expected = { MotionCommand::RT, MotionCommand::RT, MotionCommand::CM,
    //                                    MotionCommand::MC, MotionCommand::RF, MotionCommand::SC };
    // vector<MotionCommand> actual;
    // Direction nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::NEast, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);
    // blockBingoData.setBlock(route.front(), Block(Color::none));
    // blockBingoData.setBlock(route.back(), Block(Color::blue));

    // // (4,4)の黄色ブロックを取得
    // route = { { 4, 6 }, { 4, 5 }, { 4, 4 } };
    // expected = { MotionCommand::RF, MotionCommand::CM, MotionCommand::MC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::North, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);

    // // (4,4)の黄色ブロックを(1,1)に設置
    // route = { { 4, 4 }, { 4, 3 }, { 4, 2 }, { 4, 1 }, { 3, 0 }, { 2, 0 }, { 1, 1 } };
    // expected = { MotionCommand::CM, MotionCommand::MC, MotionCommand::CM,
    //              MotionCommand::RF, MotionCommand::MM, MotionCommand::RF,
    //              MotionCommand::MC, MotionCommand::RF, MotionCommand::SC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::SWest, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);
    // blockBingoData.setBlock(route.front(), Block(Color::none));
    // blockBingoData.setBlock(route.back(), Block(Color::yellow));

    // // (0,0)の青ブロック取得
    // route = { { 2, 0 }, { 1, 0 }, { 0, 0 } };
    // expected = { MotionCommand::RT, MotionCommand::CM, MotionCommand::MC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::West, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);

    // // (0,0)の青ブロックを(1,3)に設置
    // route = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 3 } };
    // expected = { MotionCommand::RF, MotionCommand::RF, MotionCommand::CM,
    //              MotionCommand::MC, MotionCommand::RF, MotionCommand::SC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::SEast, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);
    // blockBingoData.setBlock(route.front(), Block(Color::none));
    // blockBingoData.setBlock(route.back(), Block(Color::blue));

    // // (2,2)の緑ブロックを取得
    // route = { { 0, 2 }, { 1, 2 }, { 2, 2 } };
    // expected = { MotionCommand::RF, MotionCommand::CM, MotionCommand::MC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::East, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);

    // // (2,2)の緑ブロックを(3,1)に運ぶ
    // route = { { 2, 2 }, { 3, 1 } };
    // expected = { MotionCommand::RF, MotionCommand::SC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::NEast, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);
    // blockBingoData.setBlock(route.front(), Block(Color::none));
    // blockBingoData.setBlock(route.back(), Block(Color::green));

    // // (6,2)の赤ブロックを取得
    // route = { { 2, 2 }, { 3, 2 }, { 4, 2 }, { 5, 2 }, { 6, 2 } };
    // expected = { MotionCommand::RT, MotionCommand::CM, MotionCommand::MC, MotionCommand::CM,
    //              MotionCommand::MC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::East, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);

    // // (6,2)の赤ブロックを(5,1)に設置
    // route = { { 6, 2 }, { 5, 1 } };
    // expected = { MotionCommand::RF, MotionCommand::RF, MotionCommand::RF, MotionCommand::SC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::NWest, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);
    // blockBingoData.setBlock(route.front(), Block(Color::none));
    // blockBingoData.setBlock(route.back(), Block(Color::red));

    // // (4,0)の数字カード黒ブロックを取得
    // route = { { 6, 2 }, { 6, 1 }, { 6, 0 }, { 5, 0 }, { 4, 0 } };
    // expected = { MotionCommand::RT, MotionCommand::CM, MotionCommand::MC, MotionCommand::RF,
    //              MotionCommand::RF, MotionCommand::CM, MotionCommand::MC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::West, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);

    // // (4,0)の数字カード黒ブロックを(5,1)に設置
    // route = { { 4, 0 }, { 5, 1 } };
    // expected = { MotionCommand::RF, MotionCommand::RF, MotionCommand::RF, MotionCommand::SC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::SEast, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);
    // blockBingoData.setBlock(route.front(), Block(Color::none));
    // blockBingoData.setBlock(route.back(), Block(Color::black));

    // // (3,5)の緑ブロックを取得
    // route = { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 3, 5 } };
    // expected = { MotionCommand::RT, MotionCommand::CM, MotionCommand::MC, MotionCommand::CM,
    //              MotionCommand::MC, MotionCommand::RT, MotionCommand::GC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::SWest, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);

    // // (3,5)の緑ブロックを(1,5)に設置
    // route = { { 3, 5 }, { 2, 5 }, { 1, 5 } };
    // expected = { MotionCommand::RT, MotionCommand::BM, MotionCommand::SM };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::West, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);
    // blockBingoData.setBlock(route.front(), Block(Color::none));
    // blockBingoData.setBlock(route.back(), Block(Color::green));

    // // (0,4)の赤ブロックを取得
    // route = { { 2, 5 }, { 2, 4 }, { 1, 4 }, { 0, 4 } };
    // expected = { MotionCommand::RT, MotionCommand::RT, MotionCommand::MC, MotionCommand::RF,
    //              MotionCommand::RF, MotionCommand::CM, MotionCommand::MC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::West, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);

    // // (0,4)の赤ブロックを(3,5)に設置
    // route = { { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 5 } };
    // expected = { MotionCommand::RF, MotionCommand::RF, MotionCommand::RF, MotionCommand::RF,
    //              MotionCommand::CM, MotionCommand::MC, MotionCommand::RT, MotionCommand::SC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::SEast, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(Direction::SEast);
    // blockBingoData.setBlock(route.front(), Block(Color::none));
    // blockBingoData.setBlock(route.back(), Block(Color::red));

    // // ガレージ停止開始座標(0,6)に移動
    // route = { { 2, 4 }, { 2, 5 }, { 2, 6 }, { 1, 6 }, { 0, 6 } };
    // expected = { MotionCommand::RT, MotionCommand::CM, MotionCommand::MC, MotionCommand::RT,
    //              MotionCommand::RT, MotionCommand::CM, MotionCommand::MC };
    // actual.clear();
    // nextDirection = motionSequencer.route2MotionCommand(route, actual);
    // ASSERT_EQ(Direction::West, nextDirection);
    // ASSERT_EQ(expected.size(), actual.size());
    // for(int i = 0; i < expected.size(); i++) {
    //   ASSERT_EQ(expected[i], actual[i]);
    // }
    // blockBingoData.setDirection(nextDirection);
  }
}  // namespace etrobocon2020_test
