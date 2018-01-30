/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:08:36 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/30 16:48:31 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

uint8_t	check_path(char *str, uint8_t i)
{
	t_stat	sb;

	if (stat(str, &sb) == 0)
	{
		if (i == 1)
			return (1);
		if (ft_isdir(sb) || ft_islink(sb))
		{
			if (access(str, X_OK) == 0)
				return (0);
			return (2);
		}
		return (6);
	}
	return (3);
}

uint8_t	check_access_fold(t_list *list, char *tmp)
{
	char	*str;
	t_stat	sb;

	if (!list)
		return (4);
	str = ft_strjoin(tmp, list->content);
	if (lstat(str, &sb) == 0)
	{
		ft_strdel(&str);
		if (!ft_isexe(sb))
		{
			if (list->next && ft_strequ(list->next->content, "..") &&
					!ft_strequ(list->content, ".."))
				return (2);
			return (error("cd", tmp, 2));
		}
		if (list->next && ft_strequ(list->next->content, "..") &&
				!ft_strequ(list->content, ".."))
			return (2);
		return (1);
	}
	ft_strdel(&str);
	return (3);
}

char	*concat_cdpath(char *cmd, char *path)
{
	char	*gap;
	int		i;

	i = 1;
	while ((gap = ft_strgap(path, ':', i)))
	{
		if (ft_lastchar(gap) != '/')
			gap = ft_strjoinfree(gap, "/");
		gap = ft_strjoinfree(gap, cmd);
		if (!check_path(gap, 0))
			return (gap);
		ft_strdel(&gap);
		i++;
	}
	return (NULL);
}

uint8_t	isdot(char *str)
{
	if (str)
	{
		if (str[0] && str[0] == '.')
			return (1);
	}
	return (0);
}

int		check_fold(char *cmd, t_line **env, char *p)
{
	char	*curpath;
	t_line	*cdpath;
	t_line	*pwd;

	pwd = get_pwd(env, "PWD");
	if (cmd[0] != '/' && !isdot(cmd))
	{
		if ((cdpath = get_smtg(*env, "CDPATH")))
			curpath = concat_cdpath(cmd, cdpath->value);
		else
			curpath = ft_strdup(cmd);
	}
	else if (isdot(cmd) || cmd[0] == '/')
		curpath = ft_strdup(cmd);
	if (p && ft_strchr(p, 'P') && !check_path(curpath, 0))
	{
		chdir(curpath);
		ft_strdel(&(pwd->value));
		pwd->value = getcwd(pwd->value, 0);
		ft_strdel(&curpath);
	}
	else if (!p || (p && ft_strchr(p, 'L')))
		opt_l(curpath, env);
	return (0);
}
