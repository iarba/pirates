#include "log.h"
#include "model/sea.h"
#include "controller/slicer.h"
#include "test/suite.h"

#define forever while(true)

int main()
{
  log_init("pirates");
  execute_test();
  sea *s = new sea();
  forever
  {
    slicer.tick(s);
  }
  delete s;
  return 0;
}
