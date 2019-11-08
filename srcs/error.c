/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:40:06 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/08 15:20:11 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_wolf.h"

void		error_message(char *message)
{
	int i;

	i = 0;
	while (message[i])
	{
		write(2, &(message[i]), 1);
		i++;
	}	
}

void		print_error(char *manage, char *message)
{
	error_message(manage);
	error_message(message);
	exit(0);
}
