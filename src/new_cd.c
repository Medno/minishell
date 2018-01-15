/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 09:07:51 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/11 17:48:11 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*get_pwd(t_line *env, char *str)
{
	t_line *pwd;

	pwd = env;
	while (pwd->next)
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

void	go_home(t_line **env, char **cmd, t_line *pwd,  t_line *oldpwd)
{
	ft_strdel(&(oldpwd->value));
	oldpwd->value = ft_strdup(pwd->value);
	if (cmd[1] && cmd[1][0] == '~' && cmd[1][1])
		chdir(ft_strjoin(((get_home(*env))->value), &cmd[1][1]));
	else
		chdir((get_home(*env))->value);
}

int	check_fold(char **cmd, t_line *pwd, t_line *oldpwd)
{
	t_stat	sb;
	int		minus;

	minus = (ft_strchr(cmd[1], '-') != NULL) ? 1 : 0;
	if (access(cmd[1], F_OK) == 0 || minus)
	{
		stat(cmd[1], &sb);
		if ((sb.st_mode & S_IFMT) == S_IFDIR || minus)
		{
			if (access(cmd[1], R_OK) == 0 || minus)
			{
				(minus == 0) ? chdir(cmd[1]) : chdir(oldpwd->value);
				ft_strdel(&(oldpwd->value));
				oldpwd->value = ft_strdup(pwd->value);
				return (1);
			}
			return (error("cd", cmd[1], 2));
		}
		return (error("cd", cmd[1], 6));
	}
	return (error("cd", cmd[1], 3));
}

int	p_cd(t_line **env, char **cmd)
{
	t_line	*pwd;
	t_line	*oldpwd;

	pwd = get_pwd(*env, "PWD");
	oldpwd = get_pwd(*env, "OLDPWD");
	if (cmd[1] && cmd[2])
		return (error("cd", cmd[1], 1));
	if ((!cmd[1] || cmd[1][0] == '~') && get_home(*env))
		go_home(env, cmd, pwd, oldpwd);
	else if (cmd[1])
	{
		if (check_fold(cmd, pwd, oldpwd) == 0)
			return (0);
	}
	ft_strdel(&(pwd->value));
	pwd->value = getcwd(pwd->value, 0);
	return (1);
}
