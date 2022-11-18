/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:43:58 by eholzer           #+#    #+#             */
/*   Updated: 2022/11/18 17:25:29 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_trimmed_line(char *reserve, char **ptr_reserve)
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
			line[i] = '\0';
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
	int			char_read;
	char		buf[BUFFER_SIZE + 1];
	static char	*reserve;
	char		*line;
	static char	last_line_checked;

	if (!reserve)
	{
		reserve = malloc(sizeof(char) * 1);
		*reserve = 0;
	}
	//printf("\n---reserve=%s---\n", reserve);
	line = NULL;
	line = get_trimmed_line(reserve, &reserve);
	if (line)
		return (line);
	char_read = read(fd, buf, BUFFER_SIZE);
	if (!char_read && *reserve && !last_line_checked)
	{
		line = reserve;
		last_line_checked = 1;
	}
	while (char_read)
	{
		if (char_read == BUFFER_SIZE)
		{
			buf[char_read] = '\0';
			reserve = ft_strjoin(reserve, buf);
			line = get_trimmed_line(reserve, &reserve);
			if (line)
				return (line);
			char_read = read(fd, buf, BUFFER_SIZE);
		}
		else
		{
			buf[char_read] = '\0';
			reserve = ft_strjoin(reserve, buf);
			line = get_trimmed_line(reserve, &reserve);
			if (line)
				return (line);
			line = reserve;
			last_line_checked = 1;
			break ;
		}
	}
	/* if (!line && reserve)
		free(reserve); */
	return (line);
} 

/* int	main()
{
	int	fd;
	int	i;

	fd = open("text.txt", O_RDONLY);
	i = 1;
	if (fd == -1)
		return (1);
	while (i <= 10)
	{
		printf("\nline %d: %s\n", i, get_next_line(fd));
		i++;
	}
	if (close(fd) == -1)
		return (1);
}
 */