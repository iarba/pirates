#ifndef MODEL_CANNONBALL_H
#define MODEL_CANNONBALL_H

#include "model/attachment.h"

extern namer_t cannonball_namer;

class cannonball : public attachment
{
public:
  static void init(boost::property_tree::ptree namer_node);
  cannonball(double ttl);
  boost::property_tree::ptree serialise();
};

#endif // MODEL_CANNONBALL_H
