/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:38:43 by dufama            #+#    #+#             */
/*   Updated: 2026/03/01 16:13:27 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_texture(t_game *game, char *to_check)
{
	int		fd;
	char	*dot;

	dot = ft_strrchr(to_check, '.');
	if (!dot || ft_strncmp(dot, ".xpm", 4) != 0 || ft_strlen(dot) != 4)
		exit_error(game, "Texture must be .xpm");
	fd = open(to_check, O_RDONLY);
	if (fd == -1)
		exit_error(game, "Invalid path texture");
	close(fd);
}

static void	trim_one(t_game *game, char **path)
{
	char	*str_trim;

	str_trim = ft_strtrim(*path, "\n");
	if (!str_trim)
		exit_error(game, "Memory allocation failed");
	free(*path);
	*path = str_trim;
}

static void	trim_texture(t_game *game)
{
	trim_one(game, &game->textures.north);
	trim_one(game, &game->textures.south);
	trim_one(game, &game->textures.west);
	trim_one(game, &game->textures.east);
}

void	check_all_elements(t_game *game)
{
	if (!game->textures.south)
		exit_error(game, "Missing texture south");
	if (!game->textures.north)
		exit_error(game, "Missing texture north");
	if (!game->textures.east)
		exit_error(game, "Missing texture east");
	if (!game->textures.west)
		exit_error(game, "Missing texture west");
	trim_texture(game);
	check_texture(game, game->textures.north);
	check_texture(game, game->textures.south);
	check_texture(game, game->textures.east);
	check_texture(game, game->textures.west);
	if (!game->textures.set_floor)
		exit_error(game, "Missing floor color");
	if (!game->textures.set_ceiling)
		exit_error(game, "Missing ceiling color");
}


