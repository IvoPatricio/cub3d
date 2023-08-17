#include "../../includes/cub3d.h"

char	*give_mem_char(char *dest, char *src)
{
	int	len;
	int	i;

	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
	{
		free(dest);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

void	rgb_path_parse2(t_data *data)
{
	if (ft_strncmp(data->f, "F", 1) != 0)
		printf_error(data, "Invalid Floor RGB");
	if (ft_strncmp(data->c, "C", 1) != 0)
		printf_error(data, "Invalid Roof RGB");
	rgb_path_parse3(data);
}

void	rgb_path_parse1(t_data *data, char *b, int i)
{
	if (i == 0)
		data->no = give_mem_char(data->no, b);
	else if (i == 1)
		data->so = give_mem_char(data->so, b);
	else if (i == 2)
		data->we = give_mem_char(data->we, b);
	else if (i == 3)
		data->ea = give_mem_char(data->ea, b);
	else if (i == 5)
		data->f = give_mem_char(data->f, b);
	else if (i == 6)
		data->c = give_mem_char(data->c, b);
}
