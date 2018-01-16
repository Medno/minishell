/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:03:44 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/16 15:40:17 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*resize_str(char *str)
{
	char	*tmp;
	int		len;

	if (!(tmp = ft_strdup(str)))
		return (NULL);
	len = ft_strlen(tmp);
	ft_strdel(&str);
	if (!(str = ft_strnew(len + BUFF_SIZE)))
		return (NULL);
	str = ft_strcpy(str, tmp);
	ft_strdel(&tmp);
	return (str);
}

static int	empty_stat(char **line, char **stat)
{
	int	i;

	i = 0;
	if (**stat)
	{
		if (*stat != NULL && !(ft_strchr(*stat, '\n')))
		{
			*line = ft_strdup(*stat);
			ft_bzero(*stat, ft_strlen(*stat));
			return (2);
		}
		else
		{
			while ((*stat)[i] != '\n')
				i++;
			*line = ft_strsub(*stat, 0, i);
			*stat = &(*stat)[i + 1];
			return (1);
		}
	}
	return (0);
}

static int	put_in_tmp(int fd, char **tmp, char **line, char **stat)
{
	char	buff[BUFF_SIZE + 1];
	int		oct;
	int		i;

	while ((oct = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[oct] = '\0';
		if (!(ft_strchr(buff, '\n')))
		{
			*tmp = ft_strcat(*tmp, buff);
			*tmp = resize_str(*tmp);
		}
		else
		{
			i = ft_strlen(buff) - ft_strlen(ft_strchr(buff, '\n'));
			*tmp = ft_strncat(*tmp, buff, i);
			*line = ft_strsub(*tmp, 0, ft_strlen(*tmp));
			*stat = ft_strdup(&buff[i + 1]);
			free(*tmp);
			return (oct);
		}
		*line = *tmp;
	}
	return (oct);
}

static int	read_file(int fd, char **line, char **stat, int empty)
{
	int		oct;
	char	*tmp;

	if (!(tmp = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (empty == 2)
	{
		tmp = ft_strcat(tmp, *line);
		tmp = resize_str(tmp);
	}
	oct = put_in_tmp(fd, &tmp, line, stat);
	if (oct > 0)
		return (1);
	if (oct < 0)
		return (-1);
	if (!*line)
		return (0);
	if (**line)
		return ((oct == 0) ? 2 : -1);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*stat = "";
	int			readf;
	int			empty;

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	empty = empty_stat(line, &stat);
	if (empty == 1)
		return (1);
	readf = read_file(fd, line, &stat, empty);
	if (readf == 1)
	{
		free(stat);
		return (1);
	}
	if (readf == -1)
		return (-1);
	if (readf == 2 && (empty == 2 || **line))
		return (1);
	return (0);
}
