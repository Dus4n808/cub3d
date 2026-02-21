/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:54:34 by dufama            #+#    #+#             */
/*   Updated: 2025/11/09 15:16:53 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*open_and_stock(int fd, char *buff, char **stash)
{
	ssize_t		byte;

	byte = 1;
	while (byte > 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte < 0)
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		if (byte == 0)
			break ;
		buff[byte] = '\0';
		*stash = strjoin_free(*stash, buff);
		if (!*stash)
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (*stash);
}

static char	*extract_line(char *stash)
{
	char	*c_line;
	size_t	len;
	size_t	i;

	if (!stash)
		return (NULL);
	if (stash[0] == '\0')
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	c_line = malloc(len + 1);
	if (!c_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		c_line[i] = stash[i];
		i++;
	}
	c_line[i] = '\0';
	return (c_line);
}

static void	clean_stash(char **stash)
{
	size_t	i;
	char	*next;

	i = 0;
	if (!stash || !*stash)
		return ;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
	{
		if ((*stash)[i + 1] == '\0')
		{
			free(*stash);
			*stash = NULL;
			return ;
		}
		next = ft_strdup(*stash + i + 1);
		free(*stash);
		*stash = next;
	}
	else
	{
		free(*stash);
		*stash = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buff[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = open_and_stock(fd, buff, &stash);
	if (!stash || stash[0] == '\0')
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	line = extract_line(stash);
	clean_stash(&stash);
	return (line);
}

// int main(void)
// {
// 	int fd = open("coucou.txt", O_RDONLY);
// 	if (!fd)
// 		return (0);
// 	printf("%s\n", get_next_line(fd));

// }
