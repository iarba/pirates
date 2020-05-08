#include "test/serialisation.h"
#include "test/suite.h"
#include "model/sea.h"
#include "model/ship.h"
#include "model/island.h"
#include "misc_utils.h"
#include "loader.h"

void test_serialisation()
{
  floater_material_t floater_sand = loader::name_registry.get_namer("sand");
  floater_material_t floater_dirt = loader::name_registry.get_namer("dirt");
  floater_material_t floater_stone = loader::name_registry.get_namer("stone");
  floater_material_t floater_grass = loader::name_registry.get_namer("grass");
  TEST("TESTING SERIALISATION");
  ship *f1 = new ship(5, 5);
  f1 -> pp.position = {0, 0};
  f1 -> grid.at(1, 1) -> collidable = true;
  f1 -> grid.at(1, 2) -> collidable = true;
  f1 -> grid.at(1, 3) -> collidable = true;
  f1 -> grid.at(2, 1) -> collidable = true;
  f1 -> grid.at(2, 2) -> collidable = true;
  f1 -> grid.at(2, 3) -> collidable = true;
  f1 -> grid.at(3, 1) -> collidable = true;
  f1 -> grid.at(3, 2) -> collidable = true;
  f1 -> grid.at(3, 3) -> collidable = true;
  f1 -> focused = true;
  f1 -> targeted = true;
  island *f2 = new island(5, 5);
  f2 -> pp.position = {2.5, 2.5};
  f2 -> grid.at(1, 1) -> collidable = true;
  f2 -> grid.at(1, 1) -> material = floater_sand;
  f2 -> grid.at(1, 2) -> collidable = true;
  f2 -> grid.at(1, 2) -> material = floater_sand;
  f2 -> grid.at(1, 3) -> collidable = true;
  f2 -> grid.at(1, 3) -> material = floater_sand;
  f2 -> grid.at(2, 1) -> collidable = true;
  f2 -> grid.at(2, 1) -> material = floater_sand;
  f2 -> grid.at(2, 2) -> collidable = true;
  f2 -> grid.at(2, 2) -> material = floater_grass;
  f2 -> grid.at(2, 3) -> collidable = true;
  f2 -> grid.at(2, 3) -> material = floater_sand;
  f2 -> grid.at(3, 1) -> collidable = true;
  f2 -> grid.at(3, 1) -> material = floater_sand;
  f2 -> grid.at(3, 2) -> collidable = true;
  f2 -> grid.at(3, 2) -> material = floater_sand;
  f2 -> grid.at(3, 3) -> collidable = true;
  f2 -> grid.at(3, 3) -> material = floater_sand;
  sea *s = new sea();
  s -> children[1] = f1;
  s -> children[2] = f2;
  sea *ss = new sea(s -> serialise());
  delete s;
  f1 = static_cast<ship *>(ss -> children[1]);
  f2 = static_cast<island *>(ss -> children[2]);
  std::string reason;
  if(f1 -> name != ship_namer)
  {
    reason = "mismatched name in first floater";
    FAIL_REASON(reason);
    goto test_serialisation_end;
  }
  if(f2 -> name != island_namer)
  {
    reason = "mismatched name in second floater";
    FAIL_REASON(reason);
    goto test_serialisation_end;
  }
  if(f2 -> grid.at(2, 2) -> material != floater_grass)
  {
    reason = "mismatched material in second floater";
    FAIL_REASON(reason);
    goto test_serialisation_end;
  }
  if(f1 -> grid.at(1, 3) -> collidable != true)
  {
    reason = "mismatched collision status in first floater";
    FAIL_REASON(reason);
    goto test_serialisation_end;
  }
  PASS;
test_serialisation_end:
  delete ss;
}
