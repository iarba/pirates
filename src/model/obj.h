#ifndef MODEL_OBJ_H
#define MODEL_OBJ_H

#include <map>
#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>

typedef int namer_t;
typedef int oid_t;

class obj
{
public:
  static obj *deserialise(boost::property_tree::ptree node);
  obj(int layer, namer_t name);
  obj(boost::property_tree::ptree node);
  ~obj();
  virtual boost::property_tree::ptree serialise();
  oid_t add(obj *child);
  std::vector<oid_t> find_id(namer_t namer);
  void erase_id(oid_t id);
  int layer;
  namer_t name;
  std::map<oid_t, obj*> children;
  bool expired = false;
  double lifespan = -10; // infinite
  bool focused = false;
  obj *parent = NULL;
private:
  oid_t counter = 0;
};

#endif // MODEL_OBJ_H
