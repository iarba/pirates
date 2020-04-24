#ifndef VIEWER_VIEWER_H
#define VIEWER_VIEWER_H

#include <scppr.h>
#include "model/sea.h"

class viewer_t
{
public:
  void init(std::string path);
  void destroy();
  void draw(sea *s);
  bool is_open();
private:
  scppr::scppr *renderer;
  std::string path;
};

extern viewer_t viewer;

#endif // VIEWER_VIEWER_H
