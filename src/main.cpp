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
  std::string directory = path.substr(0, path.find_last_of('/')) + "/../scppr/assets/";
  sea *s = new sea();
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
