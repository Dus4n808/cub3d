/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:19:00 by dufama            #+#    #+#             */
/*   Updated: 2026/03/03 15:32:59 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	return (0);
}
void	set_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 0, close_game, game);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(game, "MLX init failed");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGTH, "cub3d");
	if (!game->win)
		exit_error(game, "Window creation failed");
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGTH);
	if (!game->img.img)
		exit_error(game, "Image creation failed");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_len, &game->img.endian);
	set_hooks(game);
	return (0);
}
