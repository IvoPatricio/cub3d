/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:58:12 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/16 01:55:15 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*give_buffer_text(char *buffer, char *line, int i)
{
	int	i_buf;
	int	i_rest;

	i_buf = 0;
	i_rest = -1;
	while (buffer[i_buf] != 0)
	{
		if (i_rest == -1)
		{
			line[i++] = buffer[i_buf];
			if (buffer[i_buf] == '\n')
				i_rest = 0;
		}
		else
			buffer[i_rest++] = buffer[i_buf];
		buffer[i_buf++] = 0;
	}
	return (line);
}

char	*next_line(char *line, char *buffer, int size_line)
{
	char	*temp;
	int		i;

	i = 0;
	temp = line;
	line = malloc(sizeof(char) * (size_line + 1));
	if (line == 0)
		return (0);
	line[size_line] = '\0';
	while (temp != 0 && temp[i] != '\0')
	{
		line[i] = temp[i];
		i++;
	}
	line = give_buffer_text(buffer, line, i);
	if (temp != 0)
		free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			read_size;
	int			size;
	int			isline;

	isline = 1;
	read_size = 0;
	size = 0;
	line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (isline == 1)
	{
		read_size = 1;
		if (buffer[0] == 0)
			read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size <= 0)
			return (line);
		size = size + get_size_line(buffer);
		if (isline == 1 && read_size > 0)
			isline = check(buffer);
		line = next_line(line, buffer, size);
	}
	return (line);
}
/*
int main(void)
{
	int fd;
	char *b;

	fd = open("Txt.txt", O_RDONLY);
	b = get_next_line(fd);
	while (b)
	{
		printf("(%s)", b);
		if (b)
		{
			free(b);
			b = 0;
		}
		b = get_next_line(fd);
	}
}*/