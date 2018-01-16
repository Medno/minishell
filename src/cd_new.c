/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:31:11 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/16 18:21:07 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*get_pwd(t_line *env, char *str)
{
	t_line *pwd;

	pwd = env;
	while (pwd && pwd->next)
	{
		if (ft_strcmp(pwd->var, str) == 0)
			return (pwd);
		pwd = pwd->next;
	}
	pwd = init_line();
	pwd->var = ft_strdup(str);
	pwd->value = getcwd(pwd->value, 0);
	line_pushback(&env, pwd);
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
	ft_strdel(&(oldpwd->value));
	oldpwd->value = ft_strdup(pwd->value);
	if (cmd[1] && cmd[1][0] == '~' && cmd[1][1])
		chdir(ft_strjoin(((get_home(*env))->value), &cmd[1][1]));
	else
		chdir((get_home(*env))->value);
}

void	move_dir(char *cmd, t_stat sb, char *p)
{
	char	str[10000];

	if (p && ft_strchr(p, 'P') && (sb.st_mode & S_IFMT) == S_IFLNK)
	{
		ft_bzero(str, sizeof(str));
		readlink(cmd, str, 10000);
		chdir(str);
	}
	else
		chdir(cmd);
}

int		check_fold(char *cmd, t_line *pwd, t_line *oldpwd, char *p)
{
	t_stat	sb;
	int		minus;

	minus = (ft_strcmp(cmd, "-") == 0) ? 1 : 0;
	if (access(cmd, F_OK) == 0 || minus)
	{
		stat(cmd, &sb);
		if ((sb.st_mode & S_IFMT) == S_IFDIR || minus)
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

int		p_cd(t_line **env, char **cmd)
{
	t_line	*pwd;
	t_line	*oldpwd;
	char	*p;
	int		i;

	pwd = get_pwd(*env, "PWD");
	oldpwd = get_pwd(*env, "OLDPWD");
	i = 1;
	p = ft_getopt(cmd, &i);
	(ft_checkopt(p, "LP", 2) || !ft_strcmp(cmd[i], "-") || !(i - 1)) ? 0 : i--;
	if (cmd[i] && cmd[i + 1])
		return (error("cd", cmd[i], 1));
	if ((!cmd[i] || cmd[i][0] == '~') && get_home(*env))
		go_home(env, cmd, pwd, oldpwd);
	else if (cmd[i])
		if (check_fold(cmd[i], pwd, oldpwd, p) == 0)
			return (0);
	ft_strdel(&(pwd->value));
	pwd->value = getcwd(pwd->value, 0);
	return (1);
}
