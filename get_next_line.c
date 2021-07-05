/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 19:30:27 by smago             #+#    #+#             */
/*   Updated: 2020/06/06 21:21:23 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		clear_gnl(char **string, char **line)
{
	if (*string)
	{
		free(*string);
		*string = NULL;
	}
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (-1);
}

int		check_gnl(int fd, char **line, int *ret)
{
	char c;

	*ret = 0;
	if (line == NULL)
		return (1);
	if ((read(fd, &c, 0)) < 0)
		return (1);
	return (0);
}

char	*check_string(char **string, char **line)
{
	char *slash;

	slash = NULL;
	if (*string)
	{
		if ((slash = ft_strchr(*string, '\n')))
		{
			*line = ft_strdup(*string);
			ft_strlcpy(*string, slash, (ft_strlen(slash) + 1));
		}
		else
		{
			*line = ft_strdup(*string);
			free(*string);
			*string = NULL;
		}
	}
	else
	{
		if (!(*line = (char*)malloc(sizeof(char) * 1)))
			return (NULL);
		**line = '\0';
	}
	return (slash);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		buff[BUFFER_SIZE + 1];
	static char	*string = NULL;
	char		*slash;
	char		*tmp;

	if ((check_gnl(fd, line, &ret)) == 1 || BUFFER_SIZE < 1)
		return (-1);
	slash = check_string(&string, line);
	while (!slash && *line != NULL && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((slash = ft_strchr(buff, '\n')))
		{
			if (!(string = ft_strdup(slash)))
				return (clear_gnl(&string, line));
		}
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp);
	}
	if (*line == NULL || ret < 0)
		return (clear_gnl(&string, line));
	return (ret || string) ? 1 : 0;
}
