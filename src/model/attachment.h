#ifndef MODEL_ATTACHMENT_H
#define MODEL_ATTACHMENT_H

#include "model/obj.h"
#include "model/physical_properties.h"

class attachment : public obj
{
public:
  attachment(namer_t attachment_namer);
  ~attachment();
  physical_properties pp;
  virtual boost::property_tree::ptree serialise();
};

#endif // MODEL_ATTACHMENT_H
