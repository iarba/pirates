#include "model/highlight.h"

namer_t highlight_namer = 0;

highlight::highlight() : attachment(highlight_namer)
{
}

boost::property_tree::ptree highlight::serialise()
{
  boost::property_tree::ptree node;
  return node;
}
