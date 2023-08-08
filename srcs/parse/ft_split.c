/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:25:17 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/08 22:55:06 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	delimiter(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] == c)
	{
		i++;
	}
	return (i);
}

static int	n_palavras(char *s, char c, int i)
{
	int	x;

	x = 0;
	while (s[i] != 0 && s[i] != c)
	{
		i++;
		x++;
	}
	return (x);
}

int	n_array(char *s, char c)
{
	int	i;
	int	x;

	x = 0;
	i = delimiter(s, c);
	while (s[i] != 0)
	{
		while (s[i] != c && s[i] != 0)
		{
			i++;
		}
		while (s[i] == c && s[i] != 0)
		{
			i++;
		}
		x++;
	}
	return (x);
}

char	**junction_strs(char *s, char c, int i)
{
	int		array;
	int		string;
	char	**dest;

	dest = (char **)malloc(sizeof(char *) * (n_array(s, c) + 1));
	if (dest == NULL )
		return (NULL);
	string = 0;
	while (s[i] != '\0')
	{
		array = 0;
		dest[string] = (char *)malloc(sizeof(char) * (n_palavras(s, c, i) + 1));
		if (dest[string] == NULL)
			return (NULL);
		while (s[i] != c && s[i] != '\0')
		{
			dest[string][array++] = s[i++];
		}
		dest[string++][array] = '\0';
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	dest[string] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	*l;
	char	**dest;

	l = (char *)s;
	if (!s)
		return (NULL);
	i = delimiter(l, c);
	dest = junction_strs(l, c, i);
	return (dest);
}

/*
int	main(void)
{
	char *a;
	char **dest;
	int	i;

	i = 0;
	a = "123,32,0\n";
	dest = ft_split(a, ',');

	if(dest)
	{
		while(dest[i])
		{
			free(dest[i]);
			i++;
		}
		free(dest);	
	}
	
}*/