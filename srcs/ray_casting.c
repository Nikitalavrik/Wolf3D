/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:27:14 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/09 16:30:02 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	choose_step_ray(t_player *player, int x, int y)
{
	player->step_x = player->ray_x < 0 ? -1 : 1;
	player->len_ray_x = player->ray_x < 0 ? (player->x - x) * player->delta_x :\
									(x + 1.0 - player->x) * player->delta_x;
	player->step_y = player->ray_y < 0 ? -1 : 1;
	player->len_ray_y = player->ray_y < 0 ? (player->y - y) * player->delta_y :\
									(y + 1.0 - player->y) * player->delta_y;
}

void	cast_ray(t_player *player, t_coords **coords, t_coords *map)
{
	int		hit;

	hit = 0;
	map->z = 1;
	while (!hit)
	{
		if (player->len_ray_x < player->len_ray_y)
		{
			player->len_ray_x += player->delta_x;
			map->x += player->step_x;
			map->z = 0;
			if (player->ray_x < 0)
				map->z = 2;
		}
		else
		{
			player->len_ray_y += player->delta_y;
			map->y += player->step_y;
			map->z = 1;
			if (player->ray_y < 0)
				map->z = 3;
		}
		if (coords[map->y][map->x].texture > 0)
			hit = 1;
	}
}

void	draw_all(t_wolf3d *wolf3d, t_dcoords dist, t_coords map,
													t_player *player)
{
	t_coords	line;
	int			linedist;

	linedist = (int)floor(WALL_HEIGHT / dist.x);
	line.x = WALL_HALF_HEIGHT - (linedist / 2);
	line.x = line.x < 0 ? 0 : line.x;
	line.y = WALL_HALF_HEIGHT + (linedist / 2);
	line.y = line.y >= WALL_HEIGHT ? WALL_HEIGHT - 1 : line.y;
	dist.y = (map.z == 1 || map.z == 3) ? player->x + dist.x *\
	player->ray_x : player->y + dist.x * player->ray_y;
	dist.y -= floor(dist.y);
	line.z = dist.y * 64;
	if (((!map.z || map.z == 2) && player->ray_x > 0) ||\
	((map.z == 1 || map.z == 3) && player->ray_y < 0))
		line.z = 64 - line.z - 1;
	line.texture = wolf3d->coords[map.y][map.x].texture - 1;
	if (wolf3d->txt)
	{
		draw_textures(wolf3d, line, linedist, map.z);
		draw_floor(wolf3d, dist, map, line.y);
	}
	else
		draw_line(wolf3d, wolf3d->x, line, map.z);
}

void	mage(t_wolf3d *wolf3d, t_player *player)
{
	t_coords	map;
	t_dcoords	dist;

	map.x = (int)player->x;
	map.y = (int)player->y;
	player->delta_x = fabs(1 / player->ray_x);
	player->delta_y = fabs(1 / player->ray_y);
	choose_step_ray(player, map.x, map.y);
	cast_ray(player, wolf3d->coords, &map);
	dist.x = (map.z == 1 || map.z == 3) ? (map.y - player->y + ((1 -\
	player->step_y) >> 1)) / player->ray_y : (map.x - player->x + ((1 -\
	player->step_x) >> 1)) / player->ray_x;
	if (dist.x > 0)
		draw_all(wolf3d, dist, map, player);
}

void	draw_surface(t_wolf3d *wolf3d)
{
	double	cx;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		cx = (x << 1) / (double)WIDTH - 1.0;
		wolf3d->player->ray_x = wolf3d->player->dir_x +\
		wolf3d->player->plane_x * cx;
		wolf3d->player->ray_y = wolf3d->player->dir_y +\
		wolf3d->player->plane_y * cx;
		wolf3d->x = x;
		mage(wolf3d, wolf3d->player);
		x++;
	}
}
