#include "Controller.h"

// #include "Bluetooth.h"

// std::array<char, 256> Bluetooth::commands;
// bool Bluetooth::is_start = false;
std::array<Color, 10> Controller::colorBuffer = { Color::white };
int Controller::colorBufferCounter = 0;

int Controller::getCourseInfo(ETROBOC_COURSE_INFO_ID id)
{
  // ETROBOC_COURSE_INFO_BLOCK_POS_STARTは、ETROBOC_COURSE_INFO_BLOCK_POS_BLACK1と等しいので省略(switch-case文では書けない)
  // ETROBOC_COURSE_INFO_BLOCK_POS_ENDとETROBOC_COURSE_INFO_MAXは、ETROBOC_COURSE_INFO_BLOCK_POS_GREEN2に等しいので省略(switch-case文では書けない)
  switch(id) {
    case ETROBOC_COURSE_INFO_CARD_NUMBER:
      return 3;
    case ETROBOC_COURSE_INFO_BLOCK_NUMBER:
      return 4;
    case ETROBOC_COURSE_INFO_BLOCK_POS_BLACK1:
      return 67;
    case ETROBOC_COURSE_INFO_BLOCK_POS_BLACK2:
      return 83;
    case ETROBOC_COURSE_INFO_BLOCK_POS_RED1:
      return 72;
    case ETROBOC_COURSE_INFO_BLOCK_POS_RED2:
      return 74;
    case ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW1:
      return 5;
    case ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW2:
      return 76;
    case ETROBOC_COURSE_INFO_BLOCK_POS_BLUE1:
      return 65;
    case ETROBOC_COURSE_INFO_BLOCK_POS_BLUE2:
      return 81;
    case ETROBOC_COURSE_INFO_BLOCK_POS_GREEN1:
      return 70;
    case ETROBOC_COURSE_INFO_BLOCK_POS_GREEN2:
      return 7;
    default:
      return 0;
  }
}