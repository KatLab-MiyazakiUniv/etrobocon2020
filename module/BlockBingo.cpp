/**
 *  @file   BlockBingo.cpp
 *  @brief ビンゴエリアのデータ構造を管理する
 *  @author mutotaka0426, sugaken0528, Takahiro55555
 */
#include "BlockBingo.h"

/** コンストラクタ
 *  @param 引数名 [引数の説明]
 */
BlockBingo::BlockBingo() {}

int BlockBingo::init_block_circle(int x, int y, BlockCircle block_circle)
{
  //ブロックサークルの色のエラー処理
  if(block_circle.block_circle_color == Color::black) {
    // printf("[ERROR] Unexpected color\n");
    return 1;
  }

  // サークルナンバーのエラー処理
  if(block_circle.circle_number < 1 || MAX_BLOCK_CIRCLE_NUMBER < block_circle.circle_number) {
    // -1は数字がないとき
    if(block_circle.circle_number != -1) {
      // printf("[ERROR] Unecpected block circle number\n");
      return 1;
    }
  }

  // ブロック数字のエラー処理
  if(block_circle.block.block_number < 1 || MAX_BLOCK_NUMBER < block_circle.block.block_number) {
    //-1は数字がないとき
    if(block_circle.block.block_number != -1) {
      // printf("[ERROR] Unecpected block number\n");
      return 1;
    }
  }

  // 座標指定のエラー処理
  if((x >= 0) && (x < BLOCK_CIRCLE_SIZE) && (y >= 0) && (y < BLOCK_CIRCLE_SIZE)) {
    block_circle_coordinate[x][y] = block_circle;
    return 0;
  } else {
    // printf("ERROR  Unexpected coordinate\n");
    return 1;
  }
}

int BlockBingo::init_cross_circle(int x, int y, CrossCircle cross_circle)
{
  //交点サークルの色のエラー処理
  if(cross_circle.cross_circle_color == Color::none
     || cross_circle.cross_circle_color == Color::black) {
    // printf("[ERROR] Unexpected color\n");
    return 1;
  }

  // ブロック数字のエラー処理
  if(cross_circle.block.block_number < 1 || MAX_BLOCK_NUMBER < cross_circle.block.block_number) {
    // -1は数字がないとき
    if(cross_circle.block.block_number != -1) {
      // printf("[ERROR] Unecpected block number\n");
      return 1;
    }
  }

  // 座標指定のエラー処理
  if((x >= 0 && x < CROSS_CIRCLE_SIZE) && (y >= 0 && y < CROSS_CIRCLE_SIZE)) {
    cross_circle_coordinate[x][y] = cross_circle;
    return 0;
  } else {
    // printf("[ERROR] Unexpected coordinate\n");
    return 1;
  }
}

BlockCircle BlockBingo::get_block_circle(int x, int y)
{
  return block_circle_coordinate[x][y];
}

CrossCircle BlockBingo::get_cross_circle(int x, int y)
{
  return cross_circle_coordinate[x][y];
}
