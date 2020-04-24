#ifndef VIEWER_ALIAS_H
#define VIEWER_ALIAS_H

#include <map>
#include <set>
#include <vector>

class alias_t
{
public:
  void *get(void *what);
  void put(void *where, void *what);
  std::vector<void *> get_clean();
  void clean();
private:
  std::map<void *, void *> map;
  std::set<void *> dirt;
};

extern alias_t alias;

#endif // VIEWER_ALIAS_H
