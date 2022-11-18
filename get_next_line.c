/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:43:58 by eholzer           #+#    #+#             */
/*   Updated: 2022/11/18 12:19:48 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cut_if_newline(char *reserve, char **ptr_reserve)
{
	int		i;
	char	*line;
	int		len_new_reserve;
	char	*new_reserve;
	int		i_start_reserve;

	i = 0;
	len_new_reserve = 0;
	while (reserve[i])
	{
		if (reserve[i] == '\n')
		{
			line = malloc(sizeof(char) * (i + 1));
			ft_memcpy(line, reserve, i);
			line[i + 1] = '\0';
			i_start_reserve = i + 1;
			i++;
			while (reserve[i])
			{
				len_new_reserve++;
				i++;
			}
			new_reserve = malloc(sizeof(char) * (len_new_reserve + 1));
			ft_memcpy(new_reserve, reserve + i_start_reserve, len_new_reserve);
			new_reserve[len_new_reserve] = '\0';
			free(reserve);
			*ptr_reserve = new_reserve;
			return (line);
		}
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	static char	*reserve;
	char		*line;

	if (!reserve)
		reserve = "";
	printf("\n---debug:reserve=%s---\n", reserve);
	line = NULL;
	line = cut_if_newline(reserve, &reserve);
	if (line)
		return (line);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		if (ret == BUFFER_SIZE)
		{
			buf[ret] = '\0';
			reserve = ft_strjoin(reserve, buf);
			line = cut_if_newline(reserve, &reserve);
			if (line)
				break ;
			ret = read(fd, buf, BUFFER_SIZE);
		}
		else
		{
			buf[ret] = '\0';
			reserve = ft_strjoin(reserve, buf);
			line = reserve;
			ret = 0;
		}
	}
	return (line);
} 

int	main()
{
	int	fd;
	int	i;

	fd = open("text2.txt", O_RDONLY);
	i = 1;
	if (fd == -1)
		return (1);
	while (i <= 7)
	{
		printf("\nline %d: %s\n", i, get_next_line(fd));
		i++;
	}
	if (close(fd) == -1)
		return (1);
}
