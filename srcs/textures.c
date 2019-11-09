/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:14 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/09 16:50:32 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	load_textures(t_wolf3d *wolf3d)
{
	int	i;

	wolf3d->textures[0] = IMG_Load("textures/Bookshell.png");
	wolf3d->textures[1] = IMG_Load("textures/MultibrickD.png");
	wolf3d->textures[2] = IMG_Load("textures/wallbrick.png");
	wolf3d->textures[3] = IMG_Load("textures/wallbrick2.png");
	wolf3d->textures[4] = IMG_Load("textures/BluegreyL.png");
	wolf3d->textures[5] = IMG_Load("textures/EaglebannerrightL.png");
	wolf3d->textures[6] = IMG_Load("textures/Stonemold2D.png");
	wolf3d->textures[7] = IMG_Load("textures/WoodbrickswasD.png");
	wolf3d->textures[8] = IMG_Load("textures/floor.png");
	i = 0;
	while (i < NUMBER_OF_TEXTURES)
	{
		if (!wolf3d->textures[i])
			print_error(ft_itoa(i), " : num of textures didn`t load\n");
		i++;
	}
}
