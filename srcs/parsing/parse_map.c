/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:03:25 by dufama            #+#    #+#             */
/*   Updated: 2026/02/26 17:18:01 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void fill_map(t_game *game, char **lines)
{
	int	i;

	game->map.grid = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!game->map.grid)
		exit_error(game, "Memory allocation failed");
	i = 0;
	while (lines[i])
	{
		game->map.grid[i] = ft_strdup(lines[i]);
		if (!game->map.grid[i])
			exit_error(game, "Memory allocation failed");
		i++;
	}
	game->map.grid[i] = NULL;
}

int	parse_map(t_game *game, char **lines)
{
	int		i;
	char	**start_map;

	i = 0;
	while (lines[i] && !is_map(lines[i]))
		i++;
	if (!lines[i])
		exit_error(game, "No map found in file");
	start_map = lines + i;
	game->map.rows = 0;
	while (start_map[game->map.rows])
		game->map.rows++;
	fill_map(game, start_map);
	return (0);
}
