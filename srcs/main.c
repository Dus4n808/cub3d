#include "cub3d.h"

int main()
{
	t_game game;
	ft_memset(&game, 0, sizeof(t_game));
	parse_file(&game, "map/map1.cub");
	map_is_playable(&game);
	init_game(&game);
	mlx_loop(game.mlx);
	free_element(&game);
}
