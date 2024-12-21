/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:12:13 by ayel-arr          #+#    #+#             */
/*   Updated: 2024/11/21 11:12:16 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*nb;

	i = 0;
	nb = (char *)b;
	while (i < len)
	{
		nb[i] = c;
		i++;
	}
	return ((void *)nb);
}

char	*line_in_last(char **last, char *buff, int fd)
{
	char	*new;

	new = last[fd];
	last[fd] = ft_strdup(last[fd] + isin(last[fd],
				ft_strlen(last[fd]), '\n') + 1);
	new[isin(new, ft_strlen(new), '\n') + 1] = '\0';
	free(buff);
	return (new);
}

void	fff(char **new)
{
	if (*new != NULL && **new == '\0')
	{
		free(*new);
		*new = NULL;
	}
}

char	*line_in_lastbuffer(char **last, char *buffer, int byte, int fd)
{
	char	*new;

	if (byte == 0)
	{
		new = last[fd];
		last[fd] = NULL;
		fff(&new);
		free(buffer);
		return (new);
	}
	new = last[fd];
	last[fd] = ft_strjoin(last[fd], buffer);
	free(new);
	new = last[fd];
	if (isin(new, ft_strlen(new), '\n') > -1)
	{
		last[fd] = ft_strdup(last[fd] + isin(last[fd],
					ft_strlen(last[fd]), '\n') + 1);
		new[isin(new, ft_strlen(new), '\n') + 1] = '\0';
	}
	else if (isin(new, ft_strlen(new), '\n') == -1 && new[0] != '\0')
		last[fd] = NULL;
	free(buffer);
	return (new);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*last[OPEN_MAX];
	char			*tmp;
	int				byte;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = malloc((long long)BUFFER_SIZE + 1);
	if (buffer == NULL || read(fd, buffer, 0) == -1)
		return (free(buffer), NULL);
	while (1)
	{
		if (last[fd] != NULL && isin(last[fd], ft_strlen(last[fd]), '\n') > -1)
			return (line_in_last(last, buffer, fd));
		ft_memset(buffer, '\0', (long long)BUFFER_SIZE + 1);
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte < BUFFER_SIZE)
			return (line_in_lastbuffer(last, buffer, byte, fd));
		tmp = last[fd];
		last[fd] = ft_strjoin(last[fd], buffer);
		free(tmp);
	}
	return (last[fd]);
}
