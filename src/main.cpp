#include "log.h"
#include "model/sea.h"
#include "controller/slicer.h"

#define forever while(true)

int main()
{
  log_init("server");
  sea *s = new sea();
  forever
  {
    slicer.tick(s);
  }
  delete s;
  return 0;
}
