#include "model/bind.h"

binder::binder(oid_t target, oid_t origin, double lash_length)
{
  this -> target = target;
  this -> origin = origin;
  this -> lash_length = lash_length;
}

binder::binder(boost::property_tree::ptree node)
{
  this -> target = node.get<oid_t>("target");
  this -> origin = node.get<oid_t>("origin");
  this -> lash_length = node.get<double>("ll");
}

boost::property_tree::ptree binder::serialise()
{
  boost::property_tree::ptree node;
  node.put("target", target);
  node.put("origin", origin);
  node.put("ll", lash_length);
  return node;
}

bool binder::operator==(const binder &other) const
{
  return this -> target == other.target && this -> origin == other.origin;
}

bool binder::operator<(const binder &other) const
{
  return this -> target + this -> origin < other.target + other.origin;
}
