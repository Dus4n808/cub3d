#include "test.h"
#include "cub3d.h"

void	test_open_file(void)
{
	int	fd;

	printf("\n--- Testing open_file ---\n");
	fd = open_file("map/map1.cub");
	TEST("open valid file", fd > 0);
	close(fd);
	TEST("invalid file return -1", open_file("nope.cub") == -1);
	TEST("empty string return -1", open_file("") == -1);
	TEST("NULL return -1", open_file(NULL) == -1);
	printf("--- End of open_file testing ---\n");
}

void	test_extension(void)
{
	printf("\n--- Testing extension file ---\n");
	TEST("Invalid extension .ber", check_extension("mab.ber") == 1);
	TEST("Invalid extension .txt", check_extension("map.txt") == 1);
	TEST("Invalide extension .cubcub", check_extension("map.cubcub") == 1);
	TEST("Valid extension .cub", check_extension("map.cub") == 0);
	TEST("Invalid .cub.cub", check_extension("map.cub.cub") == 1);
	printf("--- End of testing extenstion ---\n");
}

void	test_fill_map(void)
{
	int		i;
	int		res;
	char	*line;
	t_game	map;

	printf("\n--- Testing fill map ---\n");
	line = get_next_line(open_file("map/map1.cub"));
	res = fill_map(&map, "map/map1.cub");
	TEST("fill_map return 0 on valid map", res == 0);
	TEST("map is not NULL", map.map != NULL);
	TEST("fisrt line not NULL", map.map[0] != NULL);
	TEST("Null argument file", fill_map(&map, NULL) == 1);
	TEST("NULL argument struct", fill_map(NULL, "map/map1.cub") == 1);
	TEST("first line correct", ft_strncmp(map.map[0], line, ft_strlen(line)) == 0);
	i = 0;
	while (map.map[i])
		free(map.map[i++]);
	free(map.map);
	res = fill_map(&map, "blabla.cub");
	TEST("Invalid map", res == 1);
}
