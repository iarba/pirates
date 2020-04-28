#include "log.h"
#include "model/sea.h"
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
  floater *f1 = new floater("floater", 5, 5);
  f1 -> pp.position = {0, 0};
  f1 -> grid.at(1, 1) -> collidable = true;
  f1 -> grid.at(1, 2) -> collidable = true;
  f1 -> grid.at(1, 3) -> collidable = true; // this should collide
  f1 -> grid.at(2, 1) -> collidable = true;
  f1 -> grid.at(2, 2) -> collidable = true;
  f1 -> grid.at(2, 3) -> collidable = true;
  f1 -> grid.at(3, 1) -> collidable = true;
  f1 -> grid.at(3, 2) -> collidable = true;
  f1 -> grid.at(3, 3) -> collidable = true;
  floater *f2 = new floater("floater", 5, 5);
  f2 -> pp.position = {2.5, 2.5};
  f2 -> grid.at(1, 1) -> collidable = true;
  f2 -> grid.at(1, 2) -> collidable = true;
  f2 -> grid.at(1, 3) -> collidable = true;
  f2 -> grid.at(2, 1) -> collidable = true;
  f2 -> grid.at(2, 2) -> collidable = true;
  f2 -> grid.at(2, 3) -> collidable = true;
  f2 -> grid.at(3, 1) -> collidable = true; // this should collide
  f2 -> grid.at(3, 2) -> collidable = true;
  f2 -> grid.at(3, 3) -> collidable = true;
  sea *s = new sea();
  s -> children[1] = f1;
  s -> children[2] = f2;
  manipulator_t *man = viewer.init(directory, s);
  while(viewer.is_open())
  {
    man -> poll();
//    slicer.tick(s);
    viewer.draw(s);
  }
  delete man;
  viewer.destroy();
  delete s;
  return 0;
}
