#include "viewer/alias.h"

void *alias_t::get(void *what)
{
  auto it = map.find(what);
  if(it != map.end())
  {
    dirt.insert(what);
    return it -> second;
  }
  return NULL;
}

void alias_t::put(void *where, void *what)
{
  dirt.insert(where);
  map[where] = what;
}

std::vector<void *> alias_t::get_clean()
{
  std::vector<void *> ret;
  for(auto it : map)
  {
    if(dirt.find(it.first) == dirt.end())
    {
      ret.push_back(it.second);
    }
  }
  return ret;
}

void alias_t::clean()
{
  dirt.clear();
}

alias_t alias;
