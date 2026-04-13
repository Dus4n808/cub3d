/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaroni <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:04:33 by dufama            #+#    #+#             */
/*   Updated: 2026/04/13 17:36:02 by lubaroni         ###   ########.fr       */
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

/*
** FIX: Added strafe left (A key).
*/
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	char	c;

	new_x = game->player.x + game->player.dir_y * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_x * MOVE_SPEED;
	c = game->map.grid[(int)game->player.y][(int)new_x];
	if (c != '1' && c != ' ')
		game->player.x = new_x;
	c = game->map.grid[(int)new_y][(int)game->player.x];
	if (c != '1' && c != ' ')
		game->player.y = new_y;
}

/*
** FIX: Added strafe right (D key).
*/
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	char	c;

	new_x = game->player.x - game->player.dir_y * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_x * MOVE_SPEED;
	c = game->map.grid[(int)game->player.y][(int)new_x];
	if (c != '1' && c != ' ')
		game->player.x = new_x;
	c = game->map.grid[(int)new_y][(int)game->player.x];
	if (c != '1' && c != ' ')
		game->player.y = new_y;
}
