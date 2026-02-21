#include "cub3d.h"

int main()
{
	t_game map;

	if (fill_map(&map, "map/map1.cub"))
		perror("Echec fill map");
	int i = 0;
	while (map.map[i])
	{
		printf("%s\n", map.map[i]);
		i++;
	}
	return (0);
}
