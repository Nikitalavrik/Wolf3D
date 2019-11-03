/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:33:00 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/02 19:33:12 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

int				split_len(char **splited)
{
	int	count;

	count = 0;
	while (splited[count])
		count++;
	return (count);
}

void			free_splited(char **splited, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_memdel((void **)&splited[i]);
		i++;
	}
	ft_memdel((void **)&splited);
}
