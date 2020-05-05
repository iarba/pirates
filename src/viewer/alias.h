#ifndef VIEWER_ALIAS_H
#define VIEWER_ALIAS_H

#include <map>
#include <set>
#include <vector>

struct aliased_t
{
  void *what;
  int identifier;
};

struct record_t
{
  aliased_t entry;
  int dirt;
};

class alias_t
{
public:
  void *get(void *what);
  aliased_t get_identifier(void *what);
  void put(void *where, void *what, int identifier);
  std::map<void *, aliased_t> get_clean();
  void clean();
  void remove(void *where);
private:
  std::map<void *, record_t> map;
  int dirt_index = 0;
};

extern alias_t alias;

#endif // VIEWER_ALIAS_H
