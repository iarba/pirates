#include "log.h"
#include "model/sea.h"
#include "model/ship.h"
#include "model/island.h"
#include "controller/slicer.h"
#include "viewer/viewer.h"
#include "test/suite.h"

#define forever while(true)

int main(int argc, char **argv)
{
  log_init("pirates");
  execute_test();
  if(argc == 1)
  {
    return 0;
  }
  std::string path = std::string(argv[0]);
  std::string directory = path.substr(0, path.find_last_of('/')) + "/../";
  floater *f1 = new ship(5, 5);
  f1 -> pp.position = {0, 0};
  //
  // **
  // ***
  // **
  //
  f1 -> grid.at(1, 1) -> collidable = true;
  f1 -> grid.at(1, 2) -> collidable = true;
  f1 -> grid.at(2, 1) -> collidable = true;
  f1 -> grid.at(2, 2) -> collidable = true;
  f1 -> grid.at(2, 3) -> collidable = true;
  f1 -> grid.at(3, 1) -> collidable = true;
  f1 -> grid.at(3, 2) -> collidable = true;
  f1 -> focused = true;
  f1 -> targeted = true;
  floater *f2 = new island(5, 5);
  f2 -> pp.position = {5, 5};
  f2 -> grid.at(1, 1) -> collidable = true;
  f2 -> grid.at(1, 1) -> material = floater_sand;
  f2 -> grid.at(1, 2) -> collidable = true;
  f2 -> grid.at(1, 2) -> material = floater_sand;
  f2 -> grid.at(1, 3) -> collidable = true;
  f2 -> grid.at(1, 3) -> material = floater_sand;
  f2 -> grid.at(2, 1) -> collidable = true;
  f2 -> grid.at(2, 1) -> material = floater_sand;
  f2 -> grid.at(2, 2) -> collidable = true;
  f2 -> grid.at(2, 2) -> material = floater_grass;
  f2 -> grid.at(2, 3) -> collidable = true;
  f2 -> grid.at(2, 3) -> material = floater_sand;
  f2 -> grid.at(3, 1) -> collidable = true;
  f2 -> grid.at(3, 1) -> material = floater_sand;
  f2 -> grid.at(3, 2) -> collidable = true;
  f2 -> grid.at(3, 2) -> material = floater_sand;
  f2 -> grid.at(3, 3) -> collidable = true;
  f2 -> grid.at(3, 3) -> material = floater_sand;
  floater *f3 = new island(18, 26);
  f3 -> pp.position = {-15, 0};

  f3 -> grid.at(1, 6) -> collidable = true;
  f3 -> grid.at(1, 6) -> material = floater_sand;

  f3 -> grid.at(1, 10) -> collidable = true;
  f3 -> grid.at(1, 10) -> material = floater_grass;
  f3 -> grid.at(1, 11) -> collidable = true;
  f3 -> grid.at(1, 11) -> material = floater_grass;
  f3 -> grid.at(1, 12) -> collidable = true;
  f3 -> grid.at(1, 12) -> material = floater_grass;

  f3 -> grid.at( 2,  2) -> collidable = true;
  f3 -> grid.at( 2,  2) -> material = floater_sand;
  f3 -> grid.at( 2,  3) -> collidable = true;
  f3 -> grid.at( 2,  3) -> material = floater_sand;
  f3 -> grid.at( 2,  4) -> collidable = true;
  f3 -> grid.at( 2,  4) -> material = floater_sand;
  f3 -> grid.at( 2,  5) -> collidable = true;
  f3 -> grid.at( 2,  5) -> material = floater_sand;
  f3 -> grid.at( 2,  6) -> collidable = true;
  f3 -> grid.at( 2,  6) -> material = floater_sand;
  f3 -> grid.at( 2,  7) -> collidable = true;
  f3 -> grid.at( 2,  7) -> material = floater_sand;

  f3 -> grid.at( 2,  8) -> collidable = true;
  f3 -> grid.at( 2,  8) -> material = floater_grass;
  f3 -> grid.at( 2,  9) -> collidable = true;
  f3 -> grid.at( 2,  9) -> material = floater_grass;
  f3 -> grid.at( 2, 10) -> collidable = true;
  f3 -> grid.at( 2, 10) -> material = floater_grass;
  f3 -> grid.at( 2, 11) -> collidable = true;
  f3 -> grid.at( 2, 11) -> material = floater_grass;
  f3 -> grid.at( 2, 12) -> collidable = true;
  f3 -> grid.at( 2, 12) -> material = floater_grass;
  f3 -> grid.at( 2, 13) -> collidable = true;
  f3 -> grid.at( 2, 13) -> material = floater_grass;
  f3 -> grid.at( 2, 14) -> collidable = true;
  f3 -> grid.at( 2, 14) -> material = floater_grass;
  f3 -> grid.at( 2, 15) -> collidable = true;
  f3 -> grid.at( 2, 15) -> material = floater_grass;

  f3 -> grid.at( 2, 16) -> collidable = true;
  f3 -> grid.at( 2, 16) -> material = floater_sand;
  f3 -> grid.at( 2, 17) -> collidable = true;
  f3 -> grid.at( 2, 17) -> material = floater_sand;

  f3 -> grid.at( 3,  3) -> collidable = true;
  f3 -> grid.at( 3,  3) -> material = floater_sand;
  f3 -> grid.at( 3,  4) -> collidable = true;
  f3 -> grid.at( 3,  4) -> material = floater_sand;

  f3 -> grid.at( 3,  5) -> collidable = true;
  f3 -> grid.at( 3,  5) -> material = floater_grass;
  f3 -> grid.at( 3,  6) -> collidable = true;
  f3 -> grid.at( 3,  6) -> material = floater_grass;
  f3 -> grid.at( 3,  7) -> collidable = true;
  f3 -> grid.at( 3,  7) -> material = floater_grass;
  f3 -> grid.at( 3,  8) -> collidable = true;
  f3 -> grid.at( 3,  8) -> material = floater_grass;
  f3 -> grid.at( 3,  9) -> collidable = true;
  f3 -> grid.at( 3,  9) -> material = floater_grass;

  f3 -> grid.at( 3, 14) -> collidable = true;
  f3 -> grid.at( 3, 14) -> material = floater_grass;
  f3 -> grid.at( 3, 15) -> collidable = true;
  f3 -> grid.at( 3, 15) -> material = floater_grass;

  f3 -> grid.at( 3, 16) -> collidable = true;
  f3 -> grid.at( 3, 16) -> material = floater_sand;
  f3 -> grid.at( 3, 17) -> collidable = true;
  f3 -> grid.at( 3, 17) -> material = floater_sand;
  f3 -> grid.at( 3, 18) -> collidable = true;
  f3 -> grid.at( 3, 18) -> material = floater_sand;

  f3 -> grid.at( 4,  3) -> collidable = true;
  f3 -> grid.at( 4,  3) -> material = floater_sand;

  f3 -> grid.at( 4,  4) -> collidable = true;
  f3 -> grid.at( 4,  4) -> material = floater_grass;
  f3 -> grid.at( 4,  5) -> collidable = true;
  f3 -> grid.at( 4,  5) -> material = floater_grass;
  f3 -> grid.at( 4,  6) -> collidable = true;
  f3 -> grid.at( 4,  6) -> material = floater_grass;
  f3 -> grid.at( 4,  7) -> collidable = true;
  f3 -> grid.at( 4,  7) -> material = floater_grass;
  f3 -> grid.at( 4,  8) -> collidable = true;
  f3 -> grid.at( 4,  8) -> material = floater_grass;
  f3 -> grid.at( 4,  9) -> collidable = true;
  f3 -> grid.at( 4,  9) -> material = floater_grass;

  f3 -> grid.at( 4, 11) -> collidable = true;
  f3 -> grid.at( 4, 11) -> material = floater_grass;
  f3 -> grid.at( 4, 12) -> collidable = true;
  f3 -> grid.at( 4, 12) -> material = floater_grass;

  f3 -> grid.at( 5,  3) -> collidable = true;
  f3 -> grid.at( 5,  3) -> material = floater_sand;

  f3 -> grid.at( 5,  4) -> collidable = true;
  f3 -> grid.at( 5,  4) -> material = floater_grass;
  f3 -> grid.at( 5,  5) -> collidable = true;
  f3 -> grid.at( 5,  5) -> material = floater_grass;
  f3 -> grid.at( 5,  6) -> collidable = true;
  f3 -> grid.at( 5,  6) -> material = floater_grass;
  f3 -> grid.at( 5,  7) -> collidable = true;
  f3 -> grid.at( 5,  7) -> material = floater_grass;
  f3 -> grid.at( 5,  8) -> collidable = true;
  f3 -> grid.at( 5,  8) -> material = floater_grass;
  f3 -> grid.at( 5,  9) -> collidable = true;
  f3 -> grid.at( 5,  9) -> material = floater_grass;
  f3 -> grid.at( 5, 10) -> collidable = true;
  f3 -> grid.at( 5, 10) -> material = floater_grass;
  f3 -> grid.at( 5, 11) -> collidable = true;
  f3 -> grid.at( 5, 11) -> material = floater_grass;
  f3 -> grid.at( 5, 12) -> collidable = true;
  f3 -> grid.at( 5, 12) -> material = floater_grass;
  f3 -> grid.at( 5, 13) -> collidable = true;
  f3 -> grid.at( 5, 13) -> material = floater_grass;
  f3 -> grid.at( 5, 14) -> collidable = true;
  f3 -> grid.at( 5, 14) -> material = floater_grass;
  f3 -> grid.at( 5, 15) -> collidable = true;
  f3 -> grid.at( 5, 15) -> material = floater_grass;
  f3 -> grid.at( 5, 16) -> collidable = true;
  f3 -> grid.at( 5, 16) -> material = floater_grass;

  f3 -> grid.at( 5, 18) -> collidable = true;
  f3 -> grid.at( 5, 18) -> material = floater_sand;
  f3 -> grid.at( 5, 19) -> collidable = true;
  f3 -> grid.at( 5, 19) -> material = floater_sand;

  f3 -> grid.at( 6,  2) -> collidable = true;
  f3 -> grid.at( 6,  2) -> material = floater_sand;
  f3 -> grid.at( 6,  3) -> collidable = true;
  f3 -> grid.at( 6,  3) -> material = floater_sand;

  f3 -> grid.at( 6,  4) -> collidable = true;
  f3 -> grid.at( 6,  4) -> material = floater_grass;
  f3 -> grid.at( 6,  5) -> collidable = true;
  f3 -> grid.at( 6,  5) -> material = floater_grass;
  f3 -> grid.at( 6,  6) -> collidable = true;
  f3 -> grid.at( 6,  6) -> material = floater_grass;
  f3 -> grid.at( 6,  7) -> collidable = true;
  f3 -> grid.at( 6,  7) -> material = floater_grass;
  f3 -> grid.at( 6,  8) -> collidable = true;
  f3 -> grid.at( 6,  8) -> material = floater_grass;
  f3 -> grid.at( 6,  9) -> collidable = true;
  f3 -> grid.at( 6,  9) -> material = floater_grass;
  f3 -> grid.at( 6, 10) -> collidable = true;
  f3 -> grid.at( 6, 10) -> material = floater_grass;
  f3 -> grid.at( 6, 11) -> collidable = true;
  f3 -> grid.at( 6, 11) -> material = floater_grass;
  f3 -> grid.at( 6, 12) -> collidable = true;
  f3 -> grid.at( 6, 12) -> material = floater_grass;
  f3 -> grid.at( 6, 13) -> collidable = true;
  f3 -> grid.at( 6, 13) -> material = floater_grass;
  f3 -> grid.at( 6, 14) -> collidable = true;
  f3 -> grid.at( 6, 14) -> material = floater_grass;
  f3 -> grid.at( 6, 15) -> collidable = true;
  f3 -> grid.at( 6, 15) -> material = floater_grass;
  f3 -> grid.at( 6, 16) -> collidable = true;
  f3 -> grid.at( 6, 16) -> material = floater_grass;

  f3 -> grid.at( 6, 18) -> collidable = true;
  f3 -> grid.at( 6, 18) -> material = floater_sand;
  f3 -> grid.at( 6, 19) -> collidable = true;
  f3 -> grid.at( 6, 19) -> material = floater_sand;

  f3 -> grid.at( 7,  3) -> collidable = true;
  f3 -> grid.at( 7,  3) -> material = floater_sand;
  f3 -> grid.at( 7,  4) -> collidable = true;
  f3 -> grid.at( 7,  4) -> material = floater_sand;
  f3 -> grid.at( 7,  5) -> collidable = true;
  f3 -> grid.at( 7,  5) -> material = floater_sand;

  f3 -> grid.at( 7,  6) -> collidable = true;
  f3 -> grid.at( 7,  6) -> material = floater_grass;
  f3 -> grid.at( 7,  7) -> collidable = true;
  f3 -> grid.at( 7,  7) -> material = floater_grass;
  f3 -> grid.at( 7,  8) -> collidable = true;
  f3 -> grid.at( 7,  8) -> material = floater_grass;
  f3 -> grid.at( 7,  9) -> collidable = true;
  f3 -> grid.at( 7,  9) -> material = floater_grass;
  f3 -> grid.at( 7, 10) -> collidable = true;
  f3 -> grid.at( 7, 10) -> material = floater_grass;
  f3 -> grid.at( 7, 11) -> collidable = true;
  f3 -> grid.at( 7, 11) -> material = floater_grass;
  f3 -> grid.at( 7, 12) -> collidable = true;
  f3 -> grid.at( 7, 12) -> material = floater_grass;
  f3 -> grid.at( 7, 13) -> collidable = true;
  f3 -> grid.at( 7, 13) -> material = floater_grass;
  f3 -> grid.at( 7, 14) -> collidable = true;
  f3 -> grid.at( 7, 14) -> material = floater_grass;
  f3 -> grid.at( 7, 15) -> collidable = true;
  f3 -> grid.at( 7, 15) -> material = floater_grass;
  f3 -> grid.at( 7, 16) -> collidable = true;
  f3 -> grid.at( 7, 16) -> material = floater_grass;

  f3 -> grid.at( 8,  5) -> collidable = true;
  f3 -> grid.at( 8,  5) -> material = floater_grass;
  f3 -> grid.at( 8,  6) -> collidable = true;
  f3 -> grid.at( 8,  6) -> material = floater_grass;
  f3 -> grid.at( 8,  7) -> collidable = true;
  f3 -> grid.at( 8,  7) -> material = floater_grass;
  f3 -> grid.at( 8,  8) -> collidable = true;
  f3 -> grid.at( 8,  8) -> material = floater_grass;
  f3 -> grid.at( 8,  9) -> collidable = true;
  f3 -> grid.at( 8,  9) -> material = floater_grass;
  f3 -> grid.at( 8, 10) -> collidable = true;
  f3 -> grid.at( 8, 10) -> material = floater_grass;
  f3 -> grid.at( 8, 11) -> collidable = true;
  f3 -> grid.at( 8, 11) -> material = floater_grass;
  f3 -> grid.at( 8, 12) -> collidable = true;
  f3 -> grid.at( 8, 12) -> material = floater_grass;
  f3 -> grid.at( 8, 13) -> collidable = true;
  f3 -> grid.at( 8, 13) -> material = floater_grass;
  f3 -> grid.at( 8, 14) -> collidable = true;
  f3 -> grid.at( 8, 14) -> material = floater_grass;
  f3 -> grid.at( 8, 15) -> collidable = true;
  f3 -> grid.at( 8, 15) -> material = floater_grass;
  f3 -> grid.at( 8, 16) -> collidable = true;
  f3 -> grid.at( 8, 16) -> material = floater_grass;
  f3 -> grid.at( 8, 17) -> collidable = true;
  f3 -> grid.at( 8, 17) -> material = floater_grass;

  f3 -> grid.at( 8, 18) -> collidable = true;
  f3 -> grid.at( 8, 18) -> material = floater_sand;
  f3 -> grid.at( 8, 19) -> collidable = true;
  f3 -> grid.at( 8, 19) -> material = floater_sand;
  f3 -> grid.at( 8, 20) -> collidable = true;
  f3 -> grid.at( 8, 20) -> material = floater_sand;

  f3 -> grid.at( 9,  4) -> collidable = true;
  f3 -> grid.at( 9,  4) -> material = floater_grass;
  f3 -> grid.at( 9,  5) -> collidable = true;
  f3 -> grid.at( 9,  5) -> material = floater_grass;
  f3 -> grid.at( 9,  6) -> collidable = true;
  f3 -> grid.at( 9,  6) -> material = floater_grass;
  f3 -> grid.at( 9,  7) -> collidable = true;
  f3 -> grid.at( 9,  7) -> material = floater_grass;
  f3 -> grid.at( 9,  8) -> collidable = true;
  f3 -> grid.at( 9,  8) -> material = floater_grass;
  f3 -> grid.at( 9,  9) -> collidable = true;
  f3 -> grid.at( 9,  9) -> material = floater_grass;
  f3 -> grid.at( 9, 10) -> collidable = true;
  f3 -> grid.at( 9, 10) -> material = floater_grass;
  f3 -> grid.at( 9, 11) -> collidable = true;
  f3 -> grid.at( 9, 11) -> material = floater_grass;
  f3 -> grid.at( 9, 12) -> collidable = true;
  f3 -> grid.at( 9, 12) -> material = floater_grass;
  f3 -> grid.at( 9, 13) -> collidable = true;
  f3 -> grid.at( 9, 13) -> material = floater_grass;
  f3 -> grid.at( 9, 14) -> collidable = true;
  f3 -> grid.at( 9, 14) -> material = floater_grass;
  f3 -> grid.at( 9, 15) -> collidable = true;
  f3 -> grid.at( 9, 15) -> material = floater_grass;
  f3 -> grid.at( 9, 16) -> collidable = true;
  f3 -> grid.at( 9, 16) -> material = floater_grass;
  f3 -> grid.at( 9, 17) -> collidable = true;
  f3 -> grid.at( 9, 17) -> material = floater_grass;

  f3 -> grid.at( 9, 18) -> collidable = true;
  f3 -> grid.at( 9, 18) -> material = floater_sand;
  f3 -> grid.at( 9, 19) -> collidable = true;
  f3 -> grid.at( 9, 19) -> material = floater_sand;

  f3 -> grid.at(10,  5) -> collidable = true;
  f3 -> grid.at(10,  5) -> material = floater_grass;
  f3 -> grid.at(10,  6) -> collidable = true;
  f3 -> grid.at(10,  6) -> material = floater_grass;
  f3 -> grid.at(10,  7) -> collidable = true;
  f3 -> grid.at(10,  7) -> material = floater_grass;
  f3 -> grid.at(10,  8) -> collidable = true;
  f3 -> grid.at(10,  8) -> material = floater_grass;
  f3 -> grid.at(10,  9) -> collidable = true;
  f3 -> grid.at(10,  9) -> material = floater_grass;
  f3 -> grid.at(10, 10) -> collidable = true;
  f3 -> grid.at(10, 10) -> material = floater_grass;
  f3 -> grid.at(10, 11) -> collidable = true;
  f3 -> grid.at(10, 11) -> material = floater_grass;
  f3 -> grid.at(10, 12) -> collidable = true;
  f3 -> grid.at(10, 12) -> material = floater_grass;
  f3 -> grid.at(10, 13) -> collidable = true;
  f3 -> grid.at(10, 13) -> material = floater_grass;
  f3 -> grid.at(10, 14) -> collidable = true;
  f3 -> grid.at(10, 14) -> material = floater_grass;
  f3 -> grid.at(10, 15) -> collidable = true;
  f3 -> grid.at(10, 15) -> material = floater_grass;
  f3 -> grid.at(10, 16) -> collidable = true;
  f3 -> grid.at(10, 16) -> material = floater_grass;

  f3 -> grid.at(10, 17) -> collidable = true;
  f3 -> grid.at(10, 17) -> material = floater_sand;
  f3 -> grid.at(10, 18) -> collidable = true;
  f3 -> grid.at(10, 18) -> material = floater_sand;
  f3 -> grid.at(10, 21) -> collidable = true;
  f3 -> grid.at(10, 21) -> material = floater_sand;

  f3 -> grid.at(11,  5) -> collidable = true;
  f3 -> grid.at(11,  5) -> material = floater_stone;
  f3 -> grid.at(11,  6) -> collidable = true;
  f3 -> grid.at(11,  6) -> material = floater_stone;
  f3 -> grid.at(11,  7) -> collidable = true;
  f3 -> grid.at(11,  7) -> material = floater_stone;
  f3 -> grid.at(11,  8) -> collidable = true;
  f3 -> grid.at(11,  8) -> material = floater_stone;
  f3 -> grid.at(11,  9) -> collidable = true;
  f3 -> grid.at(11,  9) -> material = floater_stone;
  f3 -> grid.at(11, 10) -> collidable = true;
  f3 -> grid.at(11, 10) -> material = floater_stone;
  f3 -> grid.at(11, 11) -> collidable = true;
  f3 -> grid.at(11, 11) -> material = floater_stone;
  f3 -> grid.at(11, 12) -> collidable = true;
  f3 -> grid.at(11, 12) -> material = floater_stone;
  f3 -> grid.at(11, 13) -> collidable = true;
  f3 -> grid.at(11, 13) -> material = floater_stone;
  f3 -> grid.at(11, 14) -> collidable = true;
  f3 -> grid.at(11, 14) -> material = floater_stone;
  f3 -> grid.at(11, 15) -> collidable = true;
  f3 -> grid.at(11, 15) -> material = floater_stone;
  f3 -> grid.at(11, 16) -> collidable = true;
  f3 -> grid.at(11, 16) -> material = floater_stone;

  f3 -> grid.at(11, 17) -> collidable = true;
  f3 -> grid.at(11, 17) -> material = floater_sand;
  f3 -> grid.at(11, 18) -> collidable = true;
  f3 -> grid.at(11, 18) -> material = floater_sand;
  f3 -> grid.at(11, 19) -> collidable = true;
  f3 -> grid.at(11, 19) -> material = floater_sand;
  f3 -> grid.at(11, 20) -> collidable = true;
  f3 -> grid.at(11, 20) -> material = floater_sand;
  f3 -> grid.at(11, 21) -> collidable = true;
  f3 -> grid.at(11, 21) -> material = floater_sand;

  f3 -> grid.at(12,  5) -> collidable = true;
  f3 -> grid.at(12,  5) -> material = floater_stone;
  f3 -> grid.at(12,  6) -> collidable = true;
  f3 -> grid.at(12,  6) -> material = floater_stone;

  f3 -> grid.at(12, 11) -> collidable = true;
  f3 -> grid.at(12, 11) -> material = floater_stone;
  f3 -> grid.at(12, 12) -> collidable = true;
  f3 -> grid.at(12, 12) -> material = floater_stone;

  f3 -> grid.at(12, 17) -> collidable = true;
  f3 -> grid.at(12, 17) -> material = floater_sand;
  f3 -> grid.at(12, 18) -> collidable = true;
  f3 -> grid.at(12, 18) -> material = floater_sand;
  f3 -> grid.at(12, 19) -> collidable = true;
  f3 -> grid.at(12, 19) -> material = floater_sand;
  f3 -> grid.at(12, 20) -> collidable = true;
  f3 -> grid.at(12, 20) -> material = floater_sand;
  f3 -> grid.at(12, 21) -> collidable = true;
  f3 -> grid.at(12, 21) -> material = floater_sand;
  f3 -> grid.at(12, 22) -> collidable = true;
  f3 -> grid.at(12, 22) -> material = floater_sand;

  f3 -> grid.at(13,  5) -> collidable = true;
  f3 -> grid.at(13,  5) -> material = floater_stone;
  f3 -> grid.at(13,  6) -> collidable = true;
  f3 -> grid.at(13,  6) -> material = floater_stone;

  f3 -> grid.at(13, 11) -> collidable = true;
  f3 -> grid.at(13, 11) -> material = floater_stone;
  f3 -> grid.at(13, 12) -> collidable = true;
  f3 -> grid.at(13, 12) -> material = floater_stone;

  f3 -> grid.at(13, 19) -> collidable = true;
  f3 -> grid.at(13, 19) -> material = floater_sand;

  f3 -> grid.at(13, 22) -> collidable = true;
  f3 -> grid.at(13, 22) -> material = floater_sand;
  f3 -> grid.at(13, 23) -> collidable = true;
  f3 -> grid.at(13, 23) -> material = floater_sand;

  f3 -> grid.at(14,  5) -> collidable = true;
  f3 -> grid.at(14,  5) -> material = floater_stone;
  f3 -> grid.at(14,  6) -> collidable = true;
  f3 -> grid.at(14,  6) -> material = floater_stone;

  f3 -> grid.at(14, 11) -> collidable = true;
  f3 -> grid.at(14, 11) -> material = floater_stone;
  f3 -> grid.at(14, 12) -> collidable = true;
  f3 -> grid.at(14, 12) -> material = floater_stone;

  f3 -> grid.at(15,  5) -> collidable = true;
  f3 -> grid.at(15,  5) -> material = floater_stone;
  f3 -> grid.at(15,  6) -> collidable = true;
  f3 -> grid.at(15,  6) -> material = floater_stone;

  f3 -> grid.at(15, 11) -> collidable = true;
  f3 -> grid.at(15, 11) -> material = floater_stone;
  f3 -> grid.at(15, 12) -> collidable = true;
  f3 -> grid.at(15, 12) -> material = floater_stone;
  f3 -> grid.at(15, 13) -> collidable = true;
  f3 -> grid.at(15, 13) -> material = floater_stone;
  f3 -> grid.at(15, 14) -> collidable = true;
  f3 -> grid.at(15, 14) -> material = floater_stone;
  f3 -> grid.at(15, 15) -> collidable = true;
  f3 -> grid.at(15, 15) -> material = floater_stone;

  f3 -> grid.at(16,  5) -> collidable = true;
  f3 -> grid.at(16,  5) -> material = floater_stone;
  f3 -> grid.at(16,  6) -> collidable = true;
  f3 -> grid.at(16,  6) -> material = floater_stone;

  f3 -> grid.at(16, 11) -> collidable = true;
  f3 -> grid.at(16, 11) -> material = floater_stone;
  f3 -> grid.at(16, 12) -> collidable = true;
  f3 -> grid.at(16, 12) -> material = floater_stone;
  f3 -> grid.at(16, 13) -> collidable = true;
  f3 -> grid.at(16, 13) -> material = floater_stone;
  f3 -> grid.at(16, 14) -> collidable = true;
  f3 -> grid.at(16, 14) -> material = floater_stone;
  f3 -> grid.at(16, 15) -> collidable = true;
  f3 -> grid.at(16, 15) -> material = floater_stone;

  sea *s = new sea();
  s -> children[1] = f1;
  s -> children[2] = f2;
  s -> children[3] = f3;
  manipulator_t *man = viewer.init(directory, s);
  while(viewer.is_open())
  {
    man -> poll();
    slicer.tick(s);
    viewer.draw(s);
  }
  delete man;
  viewer.destroy();
  delete s;
  return 0;
}
