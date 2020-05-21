#ifndef MODEL_PSEUDO_SHADOW_H
#define MODEL_PSEUDO_SHADOW_H

#include "model/attachment.h"

extern namer_t pseudo_shadow_namer;

class pseudo_shadow : public attachment
{
public:
  static void init(boost::property_tree::ptree namer_node);
  pseudo_shadow();
  boost::property_tree::ptree serialise();
};

#endif // MODEL_PSEUDO_SHADOW_H
