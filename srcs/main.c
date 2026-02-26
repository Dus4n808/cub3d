#include "cub3d.h"


int main()
{
	t_game game;
	ft_memset(&game, 0, sizeof(t_game));
	parse_file(&game, "map/map1.cub");
	printf("%s", game.map.grid[0]);
	printf("%s", game.map.grid[6]);
	//printf("%s", line[1]);
}
