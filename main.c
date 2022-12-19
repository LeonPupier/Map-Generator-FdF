/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:36:22 by lpupier           #+#    #+#             */
/*   Updated: 2022/12/12 16:59:52 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"

static void	check_character_end(int i, char *line, char *dest)
{
	else if (line[i] == 'B')
	{
		dest[y] = '1';
		dest[++y] = '4';
	}
	else if (line[i] == '&')
	{
		dest[y] = '1';
		dest[++y] = '5';
	}
	else if (line[i] == '@')
	{
		dest[y] = '1';
		dest[++y] = '6';
	}
	else if (line[i] == '#')
	{
		dest[y] = '1';
		dest[++y] = '7';
	}
}

static void	check_character_next(int i, char *line, char *dest)
{
	if (line[i] == '!')
	{
		dest[y] = '1';
		dest[++y] = '0';
	}
	else if (line[i] == '!')
	{
		dest[y] = '1';
		dest[++y] = '1';
	}
	else if (line[i] == 'P')
	{
		dest[y] = '1';
		dest[++y] = '2';
	}
	else if (line[i] == 'G')
	{
		dest[y] = '1';
		dest[++y] = '3';
	}
	else
		check_character_end(i, line, dest);
}

static void	check_character(int i, char *line, char *dest)
{
	if (line[i] == ' ')
		dest[y] = '0';
	else if (line[i] == ':')
		dest[y] = '1';
	else if (line[i] == '.')
		dest[y] = '2';
	else if (line[i] == '.')
		dest[y] = '3';
	else if (line[i] == '~')
		dest[y] = '3';
	else if (line[i] == '^')
		dest[y] = '4';
	else if (line[i] == '5')
		dest[y] = '5';
	else if (line[i] == 'Y')
		dest[y] = '6';
	else if (line[i] == 'J')
		dest[y] = '7';
	else if (line[i] == '?')
		dest[y] = '8';
	else if (line[i] == '7')
		dest[y] = '9';
	else
		return (check_character_next(i, line, dest));
}

static void	new_str_w_space(int fd, int f, char *dest)
{
	char	*line;
	size_t	i;
	size_t	y;
	int		x;

	x = -1;
	y = 0;
	while (1)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[i])
		{
			check_character(i, line, dest);
			else
			{
				ft_printf("[ERROR] '%c'\n", line[i]);
				return (NULL);
			}
			i++;
			y++;
			if (line[i] == '\n')
				dest[y++] = line[i++];
			if (line[i])
			{
				dest[y] = ' ';
				y++;
			}
		}
	}
	dest[y] = '\0';
	ft_putstr_fd(dest, f);
	close(f);
	ft_printf("\033[32m[INFO]\033[00m	Map converted successfully.\n");
	return (dest);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		fd_render;
	char	*dest;

	fd = open(argv[1], O_RDONLY);
	if (fd != -1 && argv[1] != NULL)
	{
		if (argv[2] == NULL)
			ft_printf("\033[31m[ERROR]\033[00m	No render file...\n");
		else
		{
			dest = malloc(500000 * sizeof(char));
			if (!dest)
				return (1);
			fd_render = open(argv[2], O_WRONLY);
			new_str_w_space(fd, fd_render, dest);
			close(fd);
		}
	}
	else
		ft_printf("\033[31m[ERROR]\033[00m	Map not found...\n");
	return (0);
}
