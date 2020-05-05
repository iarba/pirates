#include "viewer/alias.h"

void *alias_t::get(void *what)
{
  auto it = map.find(what);
  if(it != map.end())
  {
    it -> second.dirt = dirt_index;
    return it -> second.entry.what;
  }
  return NULL;
}

aliased_t alias_t::get_identifier(void *what)
{
  auto it = map.find(what);
  if(it != map.end())
  {
    it -> second.dirt = dirt_index;
    return it -> second.entry;
  }
  return {NULL, 0};
}

void alias_t::put(void *where, void *what, int identifier)
{
  map[where] = {{what, identifier}, dirt_index};
}

std::map<void *, aliased_t> alias_t::get_clean()
{
  std::map<void *, aliased_t> ret;
  for(auto it : map)
  {
    if(it.second.dirt != dirt_index)
    {
      ret[it.first] = it.second.entry;
    }
  }
  return ret;
}

void alias_t::clean()
{
  dirt_index++;
}

void alias_t::remove(void *where)
{
  map.erase(where);
}

alias_t alias;
