/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:29:52 by dufama            #+#    #+#             */
/*   Updated: 2026/03/02 17:51:44 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_player(t_game *game)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	count = 0;
	while (game->map.grid[x])
	{
		y = 0;
		while (game->map.grid[x][y])
		{
			if (game->map.grid[x][y] == 'N' || game->map.grid[x][y] == 'S'
			|| game->map.grid[x][y] == 'E' || game->map.grid[x][y] == 'W')
			{
				count++;
				game->player.x = (double)x;
				game->player.y = (double)y;
				game->player.dir = game->map.grid[x][y];
			}
			y++;
		}
		x++;
	}
	if (count != 1)
		exit_error(game, "Map must have exactly one player");
}

static void	check_borders(t_game *game)
{
	int	x;
	int	len;

	x = 0;
	while (x < game->map.rows)
	{
		len = (int)ft_strlen(game->map.grid[x]);
		if (len > 0 && game->map.grid[x][0] != '1'
			&& game->map.grid[x][0] != ' ')
			exit_error(game, "Map is not closed");
		if (len > 0 && game->map.grid[x][len - 1] != '1'
			&& game->map.grid[x][len - 1] != ' ')
			exit_error(game, "Map is not closed");
		x++;
	}
	x = -1;
	while (++x < (int)ft_strlen(game->map.grid[0]))
		if (game->map.grid[0][x] != '1' && game->map.grid[0][x] != ' ')
			exit_error(game, "Map is not closed");
	x = -1;
	while (++x < (int)ft_strlen(game->map.grid[game->map.rows - 1]))
		if (game->map.grid[game->map.rows - 1][x] != '1'
			&& game->map.grid[game->map.rows - 1][x] != ' ')
			exit_error(game, "Map is not closed");
}

static void	flood_fill(t_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.rows || y >= (int)ft_strlen(map[x]))
		exit_error(game, "Map is not closed");
	if (map[x][y] == '1' || map[x][y] == 'F')
		return ;
	if (map[x][y] == ' ')
		exit_error(game, "Map is not closed");
	map[x][y] = 'F';
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
	flood_fill(game, map, x + 1, y + 1);
	flood_fill(game, map, x + 1, y - 1);
	flood_fill(game, map, x - 1, y + 1);
	flood_fill(game, map, x - 1, y - 1);
}

static void	check_map_closed(t_game *game)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!copy)
		exit_error(game, "Memory allocation failed");
	i = 0;
	while (i < game->map.rows)
	{
		copy[i] = ft_strdup(game->map.grid[i]);
		if (!copy[i])
			exit_error(game, "Memory allocation failed");
		i++;
	}
	copy[i] = NULL;
	flood_fill(game, copy, (int)game->player.x, (int)game->player.y);
	free_lines(copy);
}

void	map_is_playable(t_game *game)
{
	check_player(game);
	check_borders(game);
	check_map_closed(game);
}
