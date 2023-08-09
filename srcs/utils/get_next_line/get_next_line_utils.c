/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:20:19 by ifreire-          #+#    #+#             */
/*   Updated: 2022/03/10 20:29:19 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != 0)
	{
		if (buffer[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

int	get_size_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != 0)
	{
		if (buffer[i] == '\n')
			return (++i);
		i++;
	}
	return (i);
}
