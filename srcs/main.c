#include "cub3d.h"

int main()
{
	t_game game;
	ft_memset(&game, 0, sizeof(t_game));
	parse_file(&game, "map/map1.cub");
	printf("player: x=%f y=%f dir=%c\n", game.player.x, game.player.y, game.player.dir);
	printf("rows=%d cols=%d\n", game.map.rows, game.map.cols);
	printf("line0 len=%zu\n", ft_strlen(game.map.grid[0]));
	map_is_playable(&game);
	init_player_pos(&game.player);
	init_game(&game);
	render(&game);
	mlx_loop(game.mlx);
	free_element(&game);
}
