#include "model/sea.h"

namer_t sea_namer = "Sea";

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
