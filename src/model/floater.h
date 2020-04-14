#ifndef MODEL_FLOATER_H
#define MODEL_FLOATER_H

#include "model/obj.h"
#include "model/physical_properties.h"

extern namer_t floater_namer;

class floater : public obj
{
public:
  floater();
  ~floater();
  physical_properties pp;
};

#endif // MODEL_FLOATER_H
