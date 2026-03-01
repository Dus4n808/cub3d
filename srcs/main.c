#include "cub3d.h"


int main()
{
	t_game game;
	ft_memset(&game, 0, sizeof(t_game));
	parse_file(&game, "map/map1.cub");
	// if (game.textures.ceiling)
	// 	printf("il y a ");
	// else
	// 	printf("y a pas");
	//printf("%s", line[1]);
	free_element(&game);
}
