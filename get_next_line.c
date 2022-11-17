/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:43:58 by eholzer           #+#    #+#             */
/*   Updated: 2022/11/17 16:51:17 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* char	*get_next_line(int fd)
{
	int		fd;
	int		ret;
	char	buf[BUFFER_SIZE + 1];

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = '\0';
	if (close(fd) == -1)
		return (NULL);
} */

int	main()
{
	int		fd;
	int		ret;
	char	buf[BUFFER_SIZE + 1];
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		buf[ret] = '\0';
		line = malloc(sizeof(char) * (ret + 1));
		line = ft_strjoin(line, buf);
		line[ret] = '\0';
		printf("%d", ret);
		printf("%s", buf);
		ret = read(fd, buf, BUFFER_SIZE);
	}
	if (close(fd) == -1)
		return (1);
}
