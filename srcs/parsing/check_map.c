/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:29:52 by dufama            #+#    #+#             */
/*   Updated: 2026/03/03 16:59:36 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_player(t_game *game)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'N' || game->map.grid[y][x] == 'S'
			|| game->map.grid[y][x] == 'E' || game->map.grid[y][x] == 'W')
			{
				count++;
				game->player.x = (double)x + 0.5;
				game->player.y = (double)y + 0.5;
				game->player.dir = game->map.grid[y][x];
			}
			x++;
		}
		y++;
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

static void	flood_fill(t_game *game, char **map, int y, int x)
{
	if (y < 0 || x < 0 || y >= game->map.rows || x >= (int)ft_strlen(map[y]))
		exit_error(game, "Map is not closed");
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == ' ')
		exit_error(game, "Map is not closed");
	map[y][x] = 'F';
	flood_fill(game, map, y + 1, x);
	flood_fill(game, map, y - 1, x);
	flood_fill(game, map, y, x + 1);
	flood_fill(game, map, y, x - 1);
	flood_fill(game, map, y + 1, x + 1);
	flood_fill(game, map, y + 1, x - 1);
	flood_fill(game, map, y - 1, x + 1);
	flood_fill(game, map, y - 1, x - 1);
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
	flood_fill(game, copy, (int)game->player.y, (int)game->player.x);
	free_lines(copy);
}

void	map_is_playable(t_game *game)
{
	check_player(game);
	check_borders(game);
	check_map_closed(game);
}
