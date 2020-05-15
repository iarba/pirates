#ifndef MODEL_SEA_H
#define MODEL_SEA_H

#include "model/obj.h"
#include "model/bind.h"
#include <set>

extern namer_t sea_namer;

class sea : public obj
{
public:
  static void init(boost::property_tree::ptree namer_node);
  sea();
  sea(boost::property_tree::ptree node);
  ~sea();
  virtual boost::property_tree::ptree serialise();
  std::set<binder> binds;
};

#endif // MODEL_SEA_H
