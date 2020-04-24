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
  viewer.init(directory);
  sea *s = new sea();
  while(viewer.is_open())
  {
    slicer.tick(s);
    viewer.draw(s);
  }
  delete s;
  return 0;
}
