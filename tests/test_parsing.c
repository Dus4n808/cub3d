#include "test.h"
#include "cub3d.h"
#include "../srcs/parsing/read_map.c"
#include "../srcs/utils.c"

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
	TEST(".cub without name", check_extension(".cub") == 1);
	TEST("Without extension", check_extension("map") == 1);
	TEST("Path with point map.map/map.cub", check_extension("map.map/map.cub") == 0);
	printf("--- End of testing extenstion ---\n");
}

void	test_all_line(void)
{
	char	**line;
	t_game	game;
	int		i;

	ft_memset(&game, 0, sizeof(t_game));
	printf("\n--- Testing read all lines ---\n");
	line = read_all_lines("map/map1.cub");
	TEST("Valid Map return", line != NULL);
	i = 0;
	while (line[i])
		i++;
	TEST("Number of line", i == 22);
	TEST("Valid first line", ft_strncmp(line[0], "NO ", 3) == 0);
	TEST("Array is NULL-terminated", line[i] == NULL);
	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
	line = read_all_lines("lol.com");
	TEST("Wrong file", line == NULL);
	printf("--- End of testing readmap ---\n");
}
