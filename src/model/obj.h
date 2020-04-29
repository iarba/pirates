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
  obj(int layer, namer_t name);
  ~obj();
  virtual boost::property_tree::ptree serialise();
  int layer;
  std::string name;
  std::map<oid_t, obj*> children;
  bool expired = false;
  double lifespan = -10; // infinite
  bool focused = false;
};

#endif // MODEL_OBJ_H
