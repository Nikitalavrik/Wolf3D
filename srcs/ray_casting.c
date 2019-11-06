/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:27:14 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/03 18:26:54 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	choose_step_ray(t_player *player, double ray_x, double ray_y, int x, int y)
{
	player->step_x = ray_x < 0 ? -1 : 1;
	player->len_ray_x = ray_x < 0 ? (player->x - x) * player->delta_x :\
									(x + 1.0 - player->x) * player->delta_x;
	player->step_y = ray_y < 0 ? -1 : 1;
	player->len_ray_y = ray_y < 0 ? (player->y - y) * player->delta_y :\
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
		}
		else
		{
			player->len_ray_y += player->delta_y;
			map->y += player->step_y;
			map->z = 1;
		}
		if (coords[map->y][map->x].texture > 0)
			hit = 1;
	}
}

void	mage(t_wolf3d *wolf3d, double ray_x, double ray_y, int x)
{
	t_coords	line;
	t_coords	map;
	double		dist;
	int			linedist;
	int			colors[5] = {0xf9ed69, 0xf08a5d, 0xb83b5e, 0x6a2c70};

	map.x = (int)wolf3d->player->x;
	map.y = (int)wolf3d->player->y;
	wolf3d->player->delta_x = fabs(1 / ray_x);
	wolf3d->player->delta_y = fabs(1 / ray_y);
	choose_step_ray(wolf3d->player, ray_x, ray_y, map.x, map.y);	
	cast_ray(wolf3d->player, wolf3d->coords, &map);
	dist = map.z == 1 ? (map.y - wolf3d->player->y + (1 - wolf3d->player->step_y) / 2) / ray_y :\
					(map.x - wolf3d->player->x + (1 - wolf3d->player->step_x) / 2) / ray_x;
	linedist = (int)floor(WALL_HEIGHT / dist);
	line.x = WALL_HEIGHT / 2 - linedist / 2;
	line.x = line.x < 0 ? 0 : line.x;
	line.y = WALL_HEIGHT / 2 + linedist / 2;
	line.y = line.y >= WALL_HEIGHT ? WALL_HEIGHT - 1 : line.y;
	draw_line(wolf3d, x, line, colors[wolf3d->coords[map.y][map.x].texture]);
}

void	draw_surface(t_wolf3d *wolf3d)
{
	double	cX;
	double	ray_x;
	double	ray_y;
	int x;

	x = 0;
	while (x < WIDTH)
	{
		cX = 2.0 * x / (double)WIDTH - 1.0;
		ray_x = wolf3d->player->dir_x + wolf3d->player->plane_x * cX;
		ray_y = wolf3d->player->dir_y + wolf3d->player->plane_y * cX;
		mage(wolf3d, ray_x, ray_y, x);
		x++;
	}
}
