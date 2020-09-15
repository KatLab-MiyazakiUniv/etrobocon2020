/**
 *  @file   BlockBingoData.h
 *  @brief	ビンゴエリアのデータ構造を管理する
 *  @author mutotaka0426,sugaken0528,Takahiro55555
 */
#ifndef BLOCK_BINGO_DATA_H
#define BLOCK_BINGO_DATA_H

#include "Controller.h"

struct Block {
  Color blockColor;
  int blockNumber;

  Block(Color blockColor_ = Color::none, int blockNumber_ = -1)
    : blockColor(blockColor_), blockNumber(blockNumber_)
  {
  }
};

struct BlockCircle {
  Color blockCircleColor;
  int circleNumber;
  Block block;
};

struct CrossCircle {
  Color crossCircleColor;
  Block block;
};

enum class Direction { North, NEast, East, SEast, South, SWest, West, NWest };

class BlockBingoData {
 public:
  /** コンストラクタ
   *  @param controller_ [Controller]
   *  @param isLeftCourse_ [Bool]
   */
  BlockBingoData(Controller& controller_, bool isLeftCourse_);

  /**
   *  @brief ブロックサークル情報をセットする
   *  @param x [x座標(0~6)]
   *  @param y [y座標(0~6)]
   *  @param blockCircle [データ設定済みのBlockCircle構造体]
   *  @return 成功判定 [trueでセット成功]
   */
  bool setBlockCircle(int x, int y, BlockCircle blockCircle);

  /**
   *  @brief 交点サークル情報をセットする
   *  @param x [x座標(0~6)]
   *  @param y [y座標(0~6)]
   *  @param crossCircle [データ設定済みのCrossCircle構造体]
   *  @return 成功判定 [trueでセット成功]
   */
  bool setCrossCircle(int x, int y, CrossCircle crossCircle);

  /**
   *  @brief ブロックサークルの情報を取得する
   *  @param x [x座標(0~6)]
   *  @param y [y座標(0~6)]
   *  @return ブロックサークル情報[BlockCircle構造体]
   */
  BlockCircle getBlockCircle(int x, int y);

  /**
   *  @brief 交点サークルの情報を取得する
   *  @param x [x座標(0~6)]
   *  @param y [y座標(0~6)]
   *  @return 交点サークル情報[CrossCircle構造体]
   */
  CrossCircle getCrossCircle(int x, int y);

  /**
   *  @brief 数字カード情報を取得する
   *  @return カードの数字
   */
  int getCardNumber(void);

  /**
   *  @brief 走行体の向きをセットする
   *  @param セットする向き
   */
  void setDirection(Direction direction_);

  /**
   *  @brief 現在の走行体の向きを取得する
   *  @return 現在の走行体の向き
   */
  Direction getDirection(void);

  /**
   *  @brief ビンゴエリアの情報を初期化する
   */
  void initBlockBingoData(void);

  /**
   *  @brief ブロックサークルの色情報を取得する
   *  @param circleNumber [ブロックサークルの数字]
   *  @return ブロックサークルの色情報
   */
  Color getBlockCircleColor(int circleNumber);

  /**
   *  @brief 交点サークルの色情報を取得する
   *  @param x [x座標(0~6)]
   *  @param y [y座標(0~6)]
   *  @return 交点サークルの色情報
   */
  Color getCrossCircleColor(int x, int y);

 private:
  Controller& controller;
  bool isLeftCourse;
  int cardNumber;                                  // 数字カード
  struct BlockCircle blockCircleCoordinate[3][3];  // ブロックサークル情報
  struct CrossCircle crossCircleCoordinate[4][4];  // 交点サークル情報
  Direction direction = Direction::North;          // 走行体の向き

  // Lコースのブロックサークルの色情報
  Color blockCircleColorL[8] = { Color::yellow, Color::green, Color::red, Color::blue,
                                 Color::yellow, Color::green, Color::red, Color::blue };
  // Rコースのブロックサークルの色情報
  Color blockCircleColorR[8] = { Color::red,  Color::green, Color::yellow, Color::yellow,
                                 Color::blue, Color::blue,  Color::red,    Color::green };
  // Lコースの交点サークルの色情報
  Color crossCircleColorL[4][4] = { { Color::red, Color::red, Color::blue, Color::blue },
                                    { Color::red, Color::red, Color::blue, Color::blue },
                                    { Color::yellow, Color::yellow, Color::green, Color::green },
                                    { Color::yellow, Color::yellow, Color::green, Color::green } };
  // Rコースの交点サークルの色情報
  Color crossCircleColorR[4][4] = { { Color::blue, Color::blue, Color::red, Color::red },
                                    { Color::blue, Color::blue, Color::red, Color::red },
                                    { Color::green, Color::green, Color::yellow, Color::yellow },
                                    { Color::green, Color::green, Color::yellow, Color::yellow } };

  /**
   *  @brief 数字カードを初期化する
   *  @param cardNumber [カードの数字]
   */
  void initCardNumber(int cardNumber);

  /**
   *  @brief ブロック情報を初期化する
   *  @param initColor [初期化する色情報]
   *  @param coordinate [APIから受けとったブロックの位置情報]
   */
  void initBlock(Color initColor, int coordinate);
};

#endif
