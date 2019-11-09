/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:12:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/09 17:15:39 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

double	add_double(double number1, double number2)
{
	return (number1 + number2);
}

double	sub_double(double number1, double number2)
{
	return (number1 - number2);
}

void	move_up_down(t_wolf3d *wolf3d, double f(double, double))
{
	t_dcoords	tmp;
	t_coords	limit;

	tmp.x = f(wolf3d->player->x, wolf3d->player->dir_x * wolf3d->speed);
	tmp.y = f(wolf3d->player->y, wolf3d->player->dir_y * wolf3d->speed);
	limit.x = f(wolf3d->player->x, wolf3d->player->dir_x * 0.5);
	limit.y = f(wolf3d->player->y, wolf3d->player->dir_y * 0.5);
	if (limit.x < wolf3d->width && limit.x > 0 &&\
	!wolf3d->coords[(int)(wolf3d->player->y)][limit.x].texture)
		wolf3d->player->x = tmp.x;
	if (limit.y < wolf3d->height && limit.y > 0 &&\
	!wolf3d->coords[limit.y][(int)(wolf3d->player->x)].texture)
		wolf3d->player->y = tmp.y;
}
