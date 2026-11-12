/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgonzal <frgonzal@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 17:51:20 by username          #+#    #+#             */
/*   Updated: 2026/10/24 21:08:36 by frgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static void	delete_used(char **stash)
{
	char	*newline;
	char	*temp;

	newline = ft_strchr(*stash, '\n');
	if (!newline)
		return ;
	temp = ft_strdup(newline + 1);
	if (!temp)
		return ;
	free(*stash);
	*stash = temp;
}

static void	read_line(char **stash, int fd)
{
	char	*r;
	int		bytes_read;
	char	*line;

	r = malloc (BUFFER_SIZE + 1 * sizeof(char));
	if (!r)
		return ;
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, r, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		r[bytes_read] = '\0';
		line = ft_strjoin(*stash, r);
		if (!line)
			break ;
		free(*stash);
		*stash = line;
	}
	free(r);
}

static char	*extract_line(char **stash, int fd)
{
	char	*line;

	read_line(stash, fd);
	if (!ft_strchr(*stash, '\n'))
	{
		if (!**stash)
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	line = ft_substr(*stash, 0, (ft_strchr(*stash, '\n') - *stash + 1));
	delete_used(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || fd > 1024)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	line = extract_line(&stash, fd);
	if (!line)
		return ((NULL));
	return (line);
}
