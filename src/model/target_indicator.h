#ifndef MODEL_TARGET_INDICATOR_H
#define MODEL_TARGET_INDICATOR_H

#include "model/attachment.h"

extern namer_t target_indicator_namer;

class target_indicator : public attachment
{
public:
  target_indicator();
  boost::property_tree::ptree serialise();
};

#endif // MODEL_TARGET_INDICATOR_H
