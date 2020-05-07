#include "model/sea.h"

namer_t sea_namer = 0;

sea::sea():obj(0, sea_namer)
{
}

sea::sea(boost::property_tree::ptree node):obj(node)
{
}

sea::~sea()
{
}

boost::property_tree::ptree sea::serialise()
{
  return obj::serialise();
}
