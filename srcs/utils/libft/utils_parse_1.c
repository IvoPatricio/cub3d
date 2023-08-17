/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:24:05 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 19:27:15 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = c;
		i++;
	}
	return (b);
}

size_t	ft_lenspace(const char *str)
{
	size_t	i;
	size_t	s;

	i = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			s++;
		i++;
	}
	i = i - s;
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && i < (n - 1) && (s1[i]) && (s2[i]))
	{
		i++;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - ((unsigned char)s2[i]));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	rest;

	neg = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' \
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	rest = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rest = (rest * 10);
		rest = rest + (str[i] - 48);
		i++;
	}
	return (rest * neg);
}
