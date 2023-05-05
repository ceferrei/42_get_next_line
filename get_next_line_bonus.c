/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceferrei <ceferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:30:16 by ceferrei          #+#    #+#             */
/*   Updated: 2023/01/03 14:35:25 by ceferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_remove_line(char *doc)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (doc[i] && doc[i] != '\n')
		i++;
	if (!doc[i])
	{
		free(doc);
		return (NULL);
	}
	line = malloc(((ft_strlen(doc) - i) + 1) * sizeof(char));
	i++;
	j = 0;
	while (doc[i])
		line[j++] = doc[i++];
	line[j] = '\0';
	free(doc);
	return (line);
}

char	*ft_get_line(char *doc)
{
	size_t	i;
	size_t	j;
	char	*line;

	j = 0;
	i = 0;
	if (!doc[i])
		return (NULL);
	while (doc[i] && doc[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	while (j <= i)
	{
		line[j] = doc[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_read_doc(int fd, char *doc)
{
	char	*buf;
	int		read_byte;

	if (ft_strchr(doc, '\n'))
		return (doc);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	read_byte = 1;
	while (!ft_strchr(doc, '\n') && read_byte > 0)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buf);
			free(doc);
			return (NULL);
		}
		buf[read_byte] = '\0';
		doc = ft_strjoin(doc, buf);
	}
	free(buf);
	return (doc);
}

char	*get_next_line(int fd)
{
	static char	*doc[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	doc[fd] = ft_read_doc(fd, doc[fd]);
	if (!doc[fd])
		return (NULL);
	line = ft_get_line(doc[fd]);
	doc[fd] = ft_remove_line(doc[fd]);
	return (line);
}
