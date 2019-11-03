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

t_coords	cast_ray(t_player *player, t_coords **coords, t_coords map)
{
	int		hit;

	hit = 0;
	map.z = 0;
	while (!hit)
	{
		if (player->len_ray_x < player->len_ray_y)
		{
			player->len_ray_x += player->delta_x;
			map.x += player->step_x;
			map.z = 0;
		}
		else
		{
			player->len_ray_y += player->delta_y;
			map.y += player->step_y;
			map.z = 1;
		}
		if (coords[map.y][map.x].texture > 0)
			hit = 1;
	}
	return (map);
}

void	mage(t_wolf3d *wolf3d, double ray_x, double ray_y, int x)
{
	t_coords	line;
	t_coords	map;
	double		dist;

	map.x = (int)wolf3d->player->x;
	map.y = (int)wolf3d->player->y;
	wolf3d->player->delta_x = fabs(1 / wolf3d->player->dir_x);
	wolf3d->player->delta_y = fabs(1 / wolf3d->player->dir_y);
	choose_step_ray(wolf3d->player, ray_x, ray_y, map.x, map.y);	
	// ft_printf("map x = %i y = %i\n", map.x, map.y);
	map = cast_ray(wolf3d->player, wolf3d->coords, map);
	// ft_printf("after cast map x = %i y = %i\n", map.x, map.y);
	dist = map.z ? ((map.y - wolf3d->player->y) + (1 - wolf3d->player->step_y) / 2) / ray_y :\
					((map.x - wolf3d->player->x) + (1 - wolf3d->player->step_x) / 2) / ray_x;
	dist = (int)(WALL_HEIGHT / dist);
	line.x = WALL_HEIGHT / 2 - dist / 2;
	line.x = line.x < 0 ? 0 : line.x;
	line.y = WALL_HEIGHT / 2 + dist / 2;
	line.y = line.y >= WALL_HEIGHT ? WALL_HEIGHT - 1 : line.y;
	if (!map.z)
		ft_printf("map z = %i\n", map.z);
	// ft_printf("start = %i end = %i\n", line.x, line.y);
	draw_line(wolf3d, x, line, map.z ? 0x087f23 / 2 : 0x087f23);
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
		cX = 2 * x / (double)WIDTH - 1;
		ray_x = wolf3d->player->dir_x + wolf3d->player->plane_x * cX;
		ray_y = wolf3d->player->dir_y + wolf3d->player->plane_y * cX;
		// ft_printf("ray_x = %f ray_y = %f cx = %f\n", ray_x, ray_y, cX);
		mage(wolf3d, ray_x, ray_y, x);
		x++;
	}
	// exit(0);
}
