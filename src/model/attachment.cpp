#include "model/attachment.h"

void attachment::init(boost::property_tree::ptree namer_node)
{
}

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
