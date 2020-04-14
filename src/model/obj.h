#ifndef MODEL_OBJ_H
#define MODEL_OBJ_H

#include <map>
#include <string>

typedef std::string namer_t;
typedef int oid_t;

class obj
{
public:
  obj(int layer, namer_t name);
  ~obj();
  int layer;
  std::string name;
  std::map<oid_t, obj*> children;
};

#endif // MODEL_OBJ_H
