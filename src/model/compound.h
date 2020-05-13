#ifndef MODEL_COMPOUND_H
#define MODEL_COMPOUND_H

#include "model/floater.h"

extern namer_t compound_namer;

class compound : public floater
{
public:
  static void init(boost::property_tree::ptree namer_node);
  compound(floater *f1, floater *f2);
  compound(boost::property_tree::ptree node);
  ~compound();
  boost::property_tree::ptree serialise();
};

#endif // MODEL_COMPOUND_H
