#ifndef MODEL_OBJ_H
#define MODEL_OBJ_H

#include <map>
#include <string>
#include <boost/property_tree/ptree.hpp>

typedef std::string namer_t;
typedef int oid_t;

class obj
{
public:
  static obj *deserialise(boost::property_tree::ptree node);
  obj(int layer, namer_t name);
  obj(boost::property_tree::ptree node);
  ~obj();
  virtual boost::property_tree::ptree serialise();
  int layer;
  namer_t name;
  std::map<oid_t, obj*> children;
  bool expired = false;
  double lifespan = -10; // infinite
  bool focused = false;
};

#endif // MODEL_OBJ_H
