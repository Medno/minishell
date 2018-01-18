/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:31:11 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/18 18:32:03 by pchadeni         ###   ########.fr       */
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

void	move_dir(char *cmd, t_stat sb, char *p)
{
	(void)p;
	(void)sb;
	/*
	   if (p && ft_strchr(p, 'P') && (sb.st_mode & S_IFMT) == S_IFLNK)
	   {
	//	char	str[10000];
	   ft_bzero(str, sizeof(str));
	   readlink(cmd, str, 10000);
	   chdir(ft_strjoin("/", str));
	   }
	   else
	   */
	chdir(cmd);
}
/*
int		check_fold(char *cmd, t_line *pwd, t_line *oldpwd, char *p)
{
	t_stat	sb;
	int		minus;

	minus = (ft_strcmp(cmd, "-") == 0) ? 1 : 0;
	if (access(cmd, F_OK) == 0 || minus)
	{
		lstat(cmd, &sb);
		if ((sb.st_mode & S_IFMT) == S_IFDIR ||(sb.st_mode & S_IFMT) == S_IFLNK || minus)
		{
			if (access(cmd, R_OK) == 0 || minus)
			{
				(minus == 0) ? move_dir(cmd, sb, p) : chdir(oldpwd->value);
				ft_strdel(&(oldpwd->value));
				oldpwd->value = ft_strdup(pwd->value);
				return (1);
			}
			return (error("cd", cmd, 2));
		}
		return (error("cd", cmd, 6));
	}
	return (error("cd", cmd, 3));
}
*/

uint8_t	slash_del(char **tab, int i)
{
	if ((tab[i + 1] && tab[i] && ft_strequ(tab[i + 1], "..") &&
				!ft_strequ(tab[i], "..")) || ft_strequ(tab[i], ".")
			|| ((!tab[i + 1] || (tab[i + 1] && ft_strequ(tab[i], ".."))) && ft_strequ(tab[i], "..")))
		return (1);
	return (0);
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

uint8_t	check_path(char *str)
{
	t_stat	sb;

	if (access(str, F_OK) == 0)
	{
		lstat(str, &sb);
		if (ft_isdir(sb) || ft_islink(sb))
			if (access(str, R_OK) == 0)
				return (1);
			return (error("cd", str, 2));
		return (error("cd", str, 6));
	}
	return (error("cd", str, 3));
}

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
		if (check_path(del) == 0)
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
	if (check_path(tmp))
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
	if (!step_8(tmp, pwd, oldpwd))
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
		if (check_path(gap))
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
		if (check_path(curpath))
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
