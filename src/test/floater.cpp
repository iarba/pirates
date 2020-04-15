#include "test/floater.h"
#include "test/suite.h"
#include "model/floater.h"
#include "model/collider/box.h"
#include "utils.h"

void test_floater()
{
  floater *f = new floater("floater", 11, 16);
  f -> grid.at( 2,  2) -> collidable = true;
  f -> grid.at( 2,  3) -> collidable = true;
  f -> grid.at( 2,  4) -> collidable = true;
  f -> grid.at( 2,  5) -> collidable = true;
  f -> grid.at( 2,  9) -> collidable = true;
  f -> grid.at( 2, 10) -> collidable = true;
  f -> grid.at( 2, 11) -> collidable = true;

  f -> grid.at( 3,  4) -> collidable = true;
  f -> grid.at( 3,  5) -> collidable = true;
  f -> grid.at( 3,  7) -> collidable = true;
  f -> grid.at( 3,  9) -> collidable = true;
  f -> grid.at( 3, 11) -> collidable = true;
  f -> grid.at( 3, 12) -> collidable = true;

  f -> grid.at( 4,  4) -> collidable = true;
  f -> grid.at( 4,  5) -> collidable = true;
  f -> grid.at( 4,  6) -> collidable = true;
  f -> grid.at( 4,  7) -> collidable = true;
  f -> grid.at( 4,  8) -> collidable = true;
  f -> grid.at( 4,  9) -> collidable = true;
  f -> grid.at( 4, 11) -> collidable = true;

  f -> grid.at( 5,  4) -> collidable = true;
  f -> grid.at( 5,  5) -> collidable = true;
  f -> grid.at( 5,  6) -> collidable = true;
  f -> grid.at( 5,  7) -> collidable = true;
  f -> grid.at( 5,  8) -> collidable = true;
  f -> grid.at( 5,  9) -> collidable = true;
  f -> grid.at( 5, 10) -> collidable = true;
  f -> grid.at( 5, 11) -> collidable = true;
  f -> grid.at( 5, 12) -> collidable = true;
  f -> grid.at( 5, 13) -> collidable = true;

  f -> grid.at( 6,  4) -> collidable = true;
  f -> grid.at( 6,  5) -> collidable = true;
  f -> grid.at( 6,  6) -> collidable = true;
  f -> grid.at( 6,  7) -> collidable = true;
  f -> grid.at( 6,  8) -> collidable = true;
  f -> grid.at( 6,  9) -> collidable = true;
  f -> grid.at( 6, 10) -> collidable = true;
  f -> grid.at( 6, 12) -> collidable = true;

  f -> grid.at( 7,  3) -> collidable = true;
  f -> grid.at( 7,  4) -> collidable = true;
  f -> grid.at( 7,  5) -> collidable = true;
  f -> grid.at( 7,  6) -> collidable = true;
  f -> grid.at( 7,  7) -> collidable = true;
  f -> grid.at( 7,  8) -> collidable = true;
  f -> grid.at( 7,  9) -> collidable = true;
  f -> grid.at( 7, 10) -> collidable = true;

  f -> grid.at( 8,  4) -> collidable = true;
  f -> grid.at( 8,  5) -> collidable = true;
  f -> grid.at( 8,  6) -> collidable = true;
  f -> grid.at( 8,  7) -> collidable = true;
  f -> grid.at( 8,  8) -> collidable = true;
  f -> grid.at( 8,  9) -> collidable = true;
  f -> grid.at( 8, 10) -> collidable = true;

  f -> grid.at( 9,  7) -> collidable = true;
  f -> grid.at( 9,  9) -> collidable = true;

  /*             111111
   *   0123456789012345
   * 0 ................   
   * 1 ................                              
   * 2 ..xxxx...xxx....                        
   * 3 ....xx.x.x.xx...            
   * 4 ....xxxxxx.x....                        
   * 5 ....xxxxxxxxxx..                         
   * 6 ....xxxxxxx.x...                          
   * 7 ...xxxxxxxx.....                          
   * 8 ....xxxxxxx.....                       
   * 9 .......xx.......                           
   *10 ................                            
   */

  TEST("TESTING CREATION OF BOUNDING BOX");
  collider_box cb = f -> get_bounding_box();
  PASS;
  TEST("TESTING PERIMETER GENERATION");
  std::vector<glm::dvec2> v = f -> get_bounding_perimeter();
  if(v.size() != 48)
  {
    PASS;
  }
  else
  {
    std::string reason = "expected size 48 got " + std::to_string(v.size());
    FAIL_REASON(reason);
  }
  delete f;
}
