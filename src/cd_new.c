/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:31:11 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/19 13:57:21 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*get_pwd(t_line **env, char *str)
{
	t_line *pwd;

	if (*env)
	{
		pwd = *env;
		while (pwd && pwd->next)
		{
			if (ft_strcmp(pwd->var, str) == 0)
				return (pwd);
			pwd = pwd->next;
		}
	}
	pwd = init_line();
	pwd->var = ft_strdup(str);
	pwd->value = getcwd(pwd->value, 0);
	line_pushback(env, pwd);
	return (pwd);
}

t_line	*get_home(t_line *env)
{
	t_line	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "HOME") == 0)
		{
			if (access(tmp->value, F_OK) == 0)
				return (tmp);
			else
			{
				ft_putstr("cd: no such file or directory: ");
				ft_putendl(tmp->value);
				return (NULL);
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	go_home(t_line **env, char **cmd, t_line *pwd, t_line *oldpwd)
{
	t_line	*home;

	home = get_home(*env);
	ft_strdel(&(oldpwd->value));
	oldpwd->value = ft_strdup(pwd->value);
	if (cmd[1] && cmd[1][0] == '~' && cmd[1][1])
		chdir(ft_strjoin((home->value), &cmd[1][1]));
	else
		chdir(home->value);
	ft_strdel(&pwd->value);
	pwd->value = ft_strdup(home->value);
}


uint8_t	slash_del(char **tab, int i)
{
	if ((tab[i + 1] && tab[i] && ft_strequ(tab[i + 1], "..") &&
				!ft_strequ(tab[i], "..")) || ft_strequ(tab[i], ".")
			|| ((!tab[i + 1] || (tab[i + 1] && ft_strequ(tab[i], ".."))) && ft_strequ(tab[i], "..")))
		return (1);
	return (0);
}

uint8_t	check_path(char *str, uint8_t i)
{
	t_stat	sb;

	if (lstat(str, &sb) == 0)
	{
		ft_putendl(str);
		ft_putendl("a");
		if (i == 1)
			return (1);
		if (ft_isdir(sb) || ft_islink(sb))
			if (access(str, R_OK) == 0)
				return (1);
			return (error("cd", str, 2));
		return (error("cd", str, 6));
	}
	return (error("cd", str, 3));
}

char	**clean_slash(char **slash, int j)
{
	char	**tmp;
	int		i;
	int		k;

	if (!(tmp = (char **)malloc(sizeof(char *) * j + 1)))
		return (NULL);
	i = 0;
	k = 0;
	while (slash[k])
	{
		if (!slash_del(slash, k))
		{
			tmp[i] = ft_strdup(slash[k]);
			i++;
		}
		k++;
	}
	tmp[i] = NULL;
	return (tmp);
}

uint8_t	checkpath(t_list *list, char *tmp)
{
	t_stat	sb;

	if (lstat(tmp, &sb) == 0)
	{
		if (access(tmp, R_OK) == -1)
		{
			if (list->next && ft_strequ(list->next->content, "..") && !ft_strequ(list->content, ".."))
				return (1);
			return (0);
		}
		ft_putendl("oui");
		return (1);
	}
	return (3);
}

int	final_curpath(char *cmd, t_line *pwd, t_line *oldpwd)
{
	t_list	*list;
	char	*tmp;
	uint8_t	check;

	list = ft_lstsplit(cmd + 1, '/');
	(void)pwd;
	(void)oldpwd;
	tmp = ft_strdup("/");
	while (list)
	{
		if ((check = checkpath(list, tmp)) == 1)
		{
			tmp = ft_strjoinfree(tmp, (char *)list->content);
			tmp = ft_strjoinfree(tmp, "/");
		}
		else
			break ;
		list = list->next;
	}
	ft_putendl(tmp);
	ft_putnbr(check);
	if (check != 1 && list->next)
		ft_putendl("ERROOR");
	return (1);
}
/*
int	step_8(char *tmp, t_line *pwd, t_line *oldpwd)
{
	char	*del;
	char	**epur;
	char	**slash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((del = ft_strlgap(tmp, '/', i)))
	{
		if (check_path(del, 1) == 0)
		{
			ft_strdel(&del);
			return (0);
		}
		ft_strdel(&del);
		i++;
	}
	slash = ft_strsplit(tmp, '/');
	i = 0;
	while (slash[i])
	{
		if (slash_del(slash, i) == 0)
			j++;
		i++;
	}
	ft_strdel(&tmp);
	epur = clean_slash(slash, j);
	tmp = ft_strdup("/");
	i = 0;
	while (epur && epur[i])
	{
		tmp = ft_strjoinfree(tmp, epur[i]);
		if (epur[i + 1])
			tmp = ft_strjoinfree(tmp, "/");
		i++;
	}
	if (check_path(tmp, 0))
	{
		ft_strdel(&(oldpwd->value));
		oldpwd->value = ft_strdup(pwd->value);
		ft_strdel(&(pwd->value));
		pwd->value = ft_strdup(tmp);
		chdir(tmp);
	}
	ft_strdel(&tmp);
	ft_tabdel(slash);
	ft_tabdel(epur);
	return (1);
}
*/
int	opt_l(char *curpath, t_line *pwd, t_line *oldpwd)
{
	char	*tmp;

	if (curpath[0] != '/')
	{
		tmp = ft_strdup(pwd->value);
		if (ft_lastchar(pwd->value) != '/')
			tmp = ft_strjoinfree(tmp, "/");
		tmp = ft_strjoinfree(tmp, curpath);
	}
	else
		tmp = curpath;
//	if (!step_8(tmp, pwd, oldpwd))
	if (!final_curpath(tmp, pwd, oldpwd))
		return (0);
	return (1);
}

char	*concat_cdpath(char *cmd, char *path)
{
	char	*gap;
	int		i;

	i = 1;
	while ((gap = ft_strgap(path, ':', i)))
	{
		gap = ft_strjoinfree(gap, cmd);
		if (check_path(gap, 0))
			return (gap);
		ft_strdel(&gap);
		i++;
	}
	return (NULL);
}

int		check_fold(char *cmd, t_line **env, char *p)
{
	char	*curpath;
	t_line	*cdpath;
	t_line	*pwd;
	char	str[10000];
	t_stat	sb;

	pwd = get_pwd(env, "PWD");
	if (cmd[0] != '/' && !ft_isdot(cmd))
	{
		if ((cdpath = get_smtg(*env, "CDPATH")))
			curpath = concat_cdpath(cmd, cdpath->value);
		else
			curpath = ft_strdup(cmd);
	}
	else if (ft_isdot(cmd) || cmd[0] == '/')
		curpath = ft_strdup(cmd);
	if (p && ft_strchr(p, 'P'))
	{
		if (check_path(curpath, 0))
		{
			lstat(curpath, &sb);
			if (ft_islink(sb))
			{
	  			ft_bzero(str, sizeof(str));
	   			readlink(cmd, str, 10000);
				chdir(ft_strjoin("/", str));
				ft_strdel(&(pwd->value));
				pwd->value = ft_strjoin("/", str);
			}
			else
			{
				chdir(curpath);
				ft_strdel(&(pwd->value));
				pwd->value = curpath;
			}
		}
	}
	else if (!p || (p && ft_strchr(p, 'L')))
		if (!opt_l(curpath, pwd, get_pwd(env, "OLDPWD")))
			return (0);
	return (1);
}

int		p_cd(t_line **env, char **cmd)
{
	t_line	*pwd;
	t_line	*oldpwd;
	char	*p;
	int		i;

	pwd = get_pwd(env, "PWD");
	oldpwd = get_pwd(env, "OLDPWD");
	i = 1;
	p = ft_getopt(cmd, &i);
	(!ft_checkopt(p, "LP", 2) || !ft_strcmp(cmd[i], "-") || !(i - 1)) ? 0 : i--;
	if (cmd[i] && cmd[i + 1])
		return (error("cd", cmd[i], 1));
	if ((!cmd[i] || cmd[i][0] == '~') && get_home(*env))
		go_home(env, cmd, pwd, oldpwd);
	else if (cmd[i] && cmd[i][0] != '~')
		if (check_fold(cmd[i], env, p) == 0)
			return (0);
	ft_strdel(&p);
	return (1);
}
