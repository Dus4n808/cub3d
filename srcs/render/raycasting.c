/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:59:17 by dufama            #+#    #+#             */
/*   Updated: 2026/03/05 16:34:50 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.fov_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.fov_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->hit = 0;
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

void	calculs_step(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_y;
	}
}

void	dda_algo(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= game->map.rows || ray->map_x < 0 || ray->map_x >= game->map.cols)
		{
			ray->hit = 1;
			break;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculs_wall(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp = ray->side_x - ray->delta_x;
	else
		ray->perp = ray->side_y - ray->delta_y;
	ray->line_height = (int)(WIN_HEIGTH / ray->perp);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGTH / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGTH / 2;
	if (ray->draw_end >= WIN_HEIGTH)
		ray->draw_end = WIN_HEIGTH - 1;
}

void	draw_cols(t_game *game, t_ray *ray, int x)
{
	t_draw_tex	draw;
	int			y;

	init_text(game, ray, &draw);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		draw.tex_y = (int)draw.tex_pos & (draw.tex->height - 1);
		draw.tex_pos += draw.step;
		draw.colors = *(unsigned int *)(draw.tex->addr + (draw.tex_y * draw.tex->line_len + draw.tex_x * (draw.tex->bpp / 8)));
		put_pixel(&game->img, x, y, draw.colors);
		y++;
	}
}

void	print_value(t_game *game, t_ray *ray)
{
	printf("Player pos: x: %f, y: %f\n", game->player.x, game->player.y);
	printf("Player dir: dir_x: %f, dir_y: %f\n", game->player.dir_x, game->player.dir_y);
	printf("Player fov: fov_x: %f, fov_y: %f\n", game->player.fov_x, game->player.fov_y);
	printf("ray camera: camera_x: %f\n", ray->camera_x);
	printf("Ray dir: dir_x: %f, dir_y: %f\n", ray->dir_x, ray->dir_y);
	printf("Ray delta: delta_x: %f, delta_y: %f\n", ray->delta_x, ray->delta_y);
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		calculs_step(game, &ray);
		dda_algo(game, &ray);
		calculs_wall(&ray);
		draw_cols(game, &ray, x);
		x++;
	}
	print_value(game, &ray);
}
