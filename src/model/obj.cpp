#include "model/obj.h"

obj::obj(int layer, namer_t name)
{
  this -> layer = layer;
  this -> name = name;
}

obj::~obj()
{
  for(auto it : children)
  {
    delete it.second;
  }
}
