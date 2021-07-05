/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:40:57 by smago             #+#    #+#             */
/*   Updated: 2020/06/05 20:28:40 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int ch)
{
	char *tmp;

	while (*str != (char)ch && *str != '\0')
	{
		str++;
	}
	if (*str == (char)ch)
	{
		tmp = (char*)str;
		*tmp = '\0';
		str++;
		return ((char*)str);
	}
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		len;
	char	*str2;

	len = ft_strlen(str);
	if (!(str2 = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str2[len] = '\0';
	while (len-- > 0)
	{
		str2[len] = str[len];
	}
	return (str2);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t len;

	len = ft_strlen(src);
	if (n == 0)
		return (len);
	while ((--n > 0) && (*src != '\0'))
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (len);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(str = malloc(sizeof(char) * len)))
		return (NULL);
	ft_strlcpy(str, s1, len);
	len2 = ft_strlen(str);
	i = len2;
	while (s2[len2 - i] != '\0' && len2 < len)
	{
		str[len2] = s2[len2 - i];
		len2++;
	}
	str[len2] = '\0';
	return (str);
}
