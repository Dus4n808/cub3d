/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaroni <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:03:25 by dufama            #+#    #+#             */
/*   Updated: 2026/04/13 17:40:57 by lubaroni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_len(char **lines, int rows)
{
	int		max;
	int		len;
	int		i;
	char	*trim;

	max = 0;
	i = 0;
	while (i < rows)
	{
		trim = ft_strtrim(lines[i], "\n");
		len = (int)ft_strlen(trim);
		free(trim);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*add_padding(char *line, int max_len)
{
	char	*pad;
	int		i;

	pad = malloc(max_len + 1);
	if (!pad)
		return (NULL);
	i = 0;
	while (line[i])
	{
		pad[i] = line[i];
		i++;
	}
	while (i < max_len)
	{
		pad[i] = ' ';
		i++;
	}
	pad[i] = '\0';
	return (pad);
}

/*
** FIX: Added ft_memset after grid malloc to initialize all pointers to NULL.
*/
static void	fill_map(t_game *game, char **lines)
{
	int		i;
	int		max_len;
	char	*trim;

	max_len = get_max_len(lines, game->map.rows);
	game->map.cols = max_len;
	game->map.grid = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!game->map.grid)
		exit_error(game, "Memory allocation failed");
	ft_memset(game->map.grid, 0, sizeof(char *) * (game->map.rows + 1));
	i = 0;
	while (lines[i])
	{
		trim = ft_strtrim(lines[i], "\n");
		if (!trim)
			exit_error(game, "Memory allocation failed");
		game->map.grid[i] = add_padding(trim, max_len);
		free(trim);
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
