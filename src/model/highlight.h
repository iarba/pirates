#ifndef MODEL_HIGHLIGHT_H
#define MODEL_HIGHLIGHT_H

#include "model/attachment.h"

extern namer_t highlight_namer;

class highlight : public attachment
{
public:
  static void init(boost::property_tree::ptree namer_node);
  highlight();
  boost::property_tree::ptree serialise();
};

#endif // MODEL_HIGHLIGHT_H
