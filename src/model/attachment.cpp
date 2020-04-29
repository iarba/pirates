#include "model/attachment.h"

attachment::attachment(namer_t attachment_namer):obj(3, attachment_namer)
{
}

attachment::~attachment()
{
}

boost::property_tree::ptree attachment::serialise()
{
  return obj::serialise();
}
