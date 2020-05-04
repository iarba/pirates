#include "model/highlight.h"

namer_t highlight_namer = "highlight";

highlight::highlight() : attachment(highlight_namer)
{
}

boost::property_tree::ptree highlight::serialise()
{
  boost::property_tree::ptree node;
  return node;
}
