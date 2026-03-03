#include "cub3d.h"

int main()
{
	t_game game;
	ft_memset(&game, 0, sizeof(t_game));
	parse_file(&game, "map/map1.cub");
	map_is_playable(&game);
	init_player_pos(&game.player);
	init_game(&game);
	floor_and_ceiling(&game);
	raycasting(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
	mlx_loop(game.mlx);
	free_element(&game);
}
