#ifndef SCENARIO_MAP_H
#define SCENARIO_MAP_H

#include "map/point.h"

void scenario_map_init();

int scenario_map_size();

void scenario_map_init_entry_exit();

map_point scenario_map_entry();

map_point scenario_map_exit();

int scenario_map_has_river_entry();

map_point scenario_map_river_entry();

int scenario_map_has_river_exit();

map_point scenario_map_river_exit();

void scenario_map_foreach_herd_point(void (*callback)(int x, int y));

void scenario_map_foreach_fishing_point(void (*callback)(int x, int y));

int scenario_map_closest_fishing_point(int x, int y, int *fish_x, int *fish_y);

int scenario_map_has_flotsam();

#endif // SCENARIO_MAP_H
