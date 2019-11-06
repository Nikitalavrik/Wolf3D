/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:14 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/06 17:22:06 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	load_textures(t_wolf3d *wolf3d)
{
	wolf3d->textures[0] = IMG_Load("textures/Bookshell.png");
	wolf3d->textures[1] = IMG_Load("textures/MultibrickD.png");
	wolf3d->textures[2] = IMG_Load("textures/wallbrick.png");
	wolf3d->textures[3] = IMG_Load("textures/wallbrick2.png");
	wolf3d->textures[4] = IMG_Load("textures/floor.png");
	// ft_printf("w = %i h = %i\n", wolf3d->textures[0]->w, wolf3d->textures[0]->h);
	// exit(0);
}