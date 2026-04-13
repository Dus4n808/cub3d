/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaroni <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:19:00 by dufama            #+#    #+#             */
/*   Updated: 2026/04/13 18:31:37 by lubaroni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** FIX: Added render_hook as the mlx_loop_hook callback.
**      mlx_loop_hook fires on every iteration of the mlx event loop,
**      giving a continuous render loop independent of key events.
**      close_game moved to utils.c
*/
int	render_hook(void *param)
{
	render((t_game *)param);
	return (0);
}

void	render(t_game *game)
{
	floor_and_ceiling(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

/*
** FIX: Removed render(game) call from key_press.
**      Keys now only update player state; rendering is driven by
**      render_hook via mlx_loop_hook.
*/
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_W)
		move_forward(game);
	if (keycode == KEY_S)
		move_backward(game);
	if (keycode == KEY_A)
		move_left(game);
	if (keycode == KEY_D)
		move_right(game);
	if (keycode == KEY_LEFT)
		rotate_left(game);
	if (keycode == KEY_RIGHT)
		rotate_right(game);
	return (0);
}

/*
** FIX: Added mlx_loop_hook to register render_hook as the continuous
**      render callback. This replaces the per-keypress render call and
**      makes the game loop run at the display's refresh rate.
*/
void	set_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, render_hook, game);
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
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	load_tex(game);
	set_hooks(game);
	return (0);
}
