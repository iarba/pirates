#ifndef MODEL_BIND_H
#define MODEL_BIND_H

#include <boost/property_tree/ptree.hpp>
#include "model/obj.h"

class binder
{
public:
  binder(oid_t target, oid_t origin, double lash_length);
  binder(boost::property_tree::ptree node);
  boost::property_tree::ptree serialise();
  oid_t target;
  oid_t origin;
  double lash_length;
  bool operator==(const binder &other) const;
  bool operator<(const binder &other) const;
};

#endif // MODEL_BIND_H
