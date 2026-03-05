/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:08:57 by dufama            #+#    #+#             */
/*   Updated: 2026/03/05 16:29:42 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_one(t_game *game, t_tex_img *tex, char *filename)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, filename, &tex->width, &tex->height);
	if (!tex->img)
		exit_error(game, "Failed to load texture");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
}

void	load_tex(t_game *game)
{
	init_one(game, &game->tex[NORTH], game->textures.north);
	init_one(game, &game->tex[SOUTH], game->textures.south);
	init_one(game, &game->tex[EAST], game->textures.east);
	init_one(game, &game->tex[WEST], game->textures.west);
}

static int	get_tex_index(t_ray *ray)
{
	if (ray->side == 1 && ray->dir_y < 0)
		return (NORTH);
	if (ray->side == 1 && ray->dir_y > 0)
		return (SOUTH);
	if (ray->side == 0 && ray->dir_x > 0)
		return (EAST);
	return (WEST);
}

void	init_text(t_game *game, t_ray *ray, t_draw_tex *draw)
{
	draw->tex = &game->tex[get_tex_index(ray)];
	if (ray->side == 0)
		draw->wall_x = game->player.y + ray->perp * ray->dir_y;
	else
		draw->wall_x = game->player.x + ray->perp * ray->dir_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * draw->tex->width);
	draw->step = 1.0 * draw->tex->height / ray->line_height;
	draw->tex_pos = (ray->draw_start - WIN_HEIGTH / 2 + ray->line_height / 2) * draw->step;
}


