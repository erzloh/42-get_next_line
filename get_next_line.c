/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:43:58 by eholzer           #+#    #+#             */
/*   Updated: 2022/11/28 08:45:01 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Remove a line from the reserve

void	update_reserve(char *reserve, char **ptr_reserve, int line_len)
{
	int		i;
	char	*new_reserve;

	i = 0;
	while (reserve[line_len + i])
		i++;
	new_reserve = malloc(sizeof(char) * (i + 1));
	ft_memcpy(new_reserve, reserve + line_len, i);
	new_reserve[i] = '\0';
	free(reserve);
	*ptr_reserve = new_reserve;
}

// Take the reserve and its address as arguments and return a line if a '\n' was
// found and remove the line from the reserve to keep only what is following the
// '\n'. Return NULL if no '\n' was found.

char	*get_trimmed_line(char *reserve, char **ptr_reserve)
{
	int		i;
	char	*line;

	i = 0;
	while (reserve[i])
	{
		if (reserve[i] == '\n')
		{
			line = malloc(sizeof(char) * (i + 1 + 1));
			if (!line)
				return (NULL);
			ft_memcpy(line, reserve, i + 1);
			line[i + 1] = '\0';
			update_reserve(reserve, ptr_reserve, i + 1);
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

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0) // Check errors
	{
		free(reserve);
		return (reserve = NULL);
	}
	if (!reserve) // Create an empty string if reserve is NULL
	{
		reserve = malloc(sizeof(char) * 1);
		if (!reserve)
			return (NULL);
		*reserve = 0;
	}
	//printf("\n---reserve=%s---\n", reserve);
	line = get_trimmed_line(reserve, &reserve); // Check if there's a newline in the reserve
	if (line)
		return (line);
	char_read = read(fd, buf, BUFFER_SIZE);
	while (char_read)
	{
		buf[char_read] = '\0';
		reserve = ft_strjoin(reserve, buf);
		line = get_trimmed_line(reserve, &reserve);
		if (line)
			return (line);
		if (char_read == BUFFER_SIZE)
			char_read = read(fd, buf, BUFFER_SIZE);
		else
		{
			line = reserve;
			reserve = NULL;
			return (line);
			break ;
		}
	}
	if (!char_read && !*reserve) // Check there is nothing to read and the reserve is empty
	{
		free(reserve);
		return (reserve = NULL);
	}
	if (!char_read)
	{
		line = reserve;
		reserve = NULL;
		return (line);
	}
	return (line);
}

/* int	main()
{
	int	fd;
	int	i;

	fd = open("texts/text.txt", O_RDONLY);
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
	return (0);
} */
