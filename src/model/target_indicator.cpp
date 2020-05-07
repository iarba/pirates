#include "model/target_indicator.h"

namer_t target_indicator_namer = "target_indicator";

target_indicator::target_indicator() : attachment(target_indicator_namer)
{
}

boost::property_tree::ptree target_indicator::serialise()
{
  boost::property_tree::ptree node;
  return node;
}
