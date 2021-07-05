/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 19:30:27 by smago             #+#    #+#             */
/*   Updated: 2020/06/08 02:50:39 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clear_gnl(t_list **lst, t_list **tmp, char **string)
{
	t_list *tmp2;

	if (*string)
	{
		free(*string);
		*string = NULL;
	}
	if (*lst == *tmp)
		*lst = (*lst)->next;
	else
	{
		tmp2 = *lst;
		while (tmp2->next != *tmp)
			tmp2 = tmp2->next;
		tmp2->next = (*tmp)->next;
	}
	free(*tmp);
}

int		check_gnl(int fd, char **line, t_list **lst)
{
	char c;

	if (line == NULL || (read(fd, &c, 0)) < 0)
		return (1);
	if (*lst == NULL)
	{
		if (!(*lst = (t_list*)malloc(sizeof(t_list))))
			return (1);
		(*lst)->fd = fd;
		(*lst)->string = NULL;
		(*lst)->next = NULL;
	}
	return (0);
}

char	*check_string(char **string, char **line)
{
	char *slash;

	slash = NULL;
	if (*string)
	{
		if ((slash = ft_strchr(*string, '\n')))
			if (!(*line = ft_strdup(*string)))
				free(*string);
			else
				ft_strlcpy(*string, slash, (ft_strlen(slash) + 1));
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

int		get_next_line2(int fd, char **line, char **string)
{
	int			ret;
	char		buff[BUFFER_SIZE + 1];
	char		*slash;
	char		*tmp;

	ret = 0;
	slash = check_string(string, line);
	while (!slash && *line != NULL && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((slash = ft_strchr(buff, '\n')))
		{
			if (!(*string = ft_strdup(slash)))
			{
				free(*line);
				return (-1);
			}
		}
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp);
	}
	if (*line == NULL || ret < 0)
		return (-1);
	return (ret || *string) ? 1 : 0;
}

int		get_next_line(int fd, char **line)
{
	static t_list	*lst;
	t_list			*tmp;
	int				i;

	if (BUFFER_SIZE < 1 || (check_gnl(fd, line, &lst)) == 1)
		return (-1);
	tmp = lst;
	while (tmp->fd != fd && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->fd != fd && tmp->next == NULL)
	{
		check_gnl(fd, line, &tmp->next);
		tmp = tmp->next;
	}
	if ((i = get_next_line2(tmp->fd, line, &tmp->string)) != 1)
		clear_gnl(&lst, &tmp, &tmp->string);
	return (i);
}
