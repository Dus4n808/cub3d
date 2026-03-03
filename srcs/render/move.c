/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:04:33 by dufama            #+#    #+#             */
/*   Updated: 2026/03/03 17:24:22 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	char	c;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	c = game->map.grid[(int)game->player.y][(int)new_x];
	if (c != '1' && c != ' ')
		game->player.x = new_x;
	c = game->map.grid[(int)new_y][(int)game->player.x];
	if (c != '1' && c != ' ')
		game->player.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	char	c;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	c = game->map.grid[(int)game->player.y][(int)new_x];
	if (c != '1' && c != ' ')
		game->player.x = new_x;
	c = game->map.grid[(int)new_y][(int)game->player.x];
	if (c != '1' && c != ' ')
		game->player.y = new_y;
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_fov_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED)
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED)
		+ game->player.dir_y * cos(ROT_SPEED);
	old_fov_x = game->player.fov_x;
	game->player.fov_x = game->player.fov_x * cos(ROT_SPEED)
		- game->player.fov_y * sin(ROT_SPEED);
	game->player.fov_y = old_fov_x * sin(ROT_SPEED)
		+ game->player.fov_y * cos(ROT_SPEED);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_fov_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED)
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ game->player.dir_y * cos(-ROT_SPEED);
	old_fov_x = game->player.fov_x;
	game->player.fov_x = game->player.fov_x * cos(-ROT_SPEED)
		- game->player.fov_y * sin(-ROT_SPEED);
	game->player.fov_y = old_fov_x * sin(-ROT_SPEED)
		+ game->player.fov_y * cos(-ROT_SPEED);
}
