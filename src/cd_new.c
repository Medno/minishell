/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:31:11 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/29 17:23:43 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

char	*copy_home(t_line *env, char *path)
{
	t_line	*home;
	char	*tmp;

	home = get_smtg(env, "HOME");
	if (home)
	{
		tmp = ft_strdup(home->value);
		tmp = ft_strjoinfree(tmp, "/");
		tmp = (path && path[0] == '~' && path[1]) ?
			ft_strjoinfree(tmp, &path[2]) : tmp;
		ft_strdel(&path);
		path = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
		ft_strdel(&path);
	return (path);
}

uint8_t	go_oldpwd(t_line **env)
{
	t_line	*pwd;
	t_line	*oldpwd;
	char	*tmp;

	if ((oldpwd = get_smtg(*env, "OLDPWD")))
	{
		pwd = get_pwd(env, "PWD");
		tmp = ft_strdup(pwd->value);
		ft_strdel(&pwd->value);
		pwd->value = ft_strdup(oldpwd->value);
		ft_strdel(&oldpwd->value);
		oldpwd->value = ft_strdup(tmp);
		ft_strdel(&tmp);
		chdir(pwd->value);
		ft_putendl(pwd->value);
		return (0);
	}
	else
	{
		error("cd", "OLDPWD", 7);
		return (7);
	}
}

int		p_cd(t_line **env, char **cmd)
{
	char	*path;
	char	*p;
	int		err;
	int		i;

	i = 1;
	get_pwd(env, "OLDPWD");
	p = ft_getopt(cmd, &i);
	(!ft_checkopt(p, "LP", 2) || !(i - 1)) ? 0 : i--;
	err = (cmd[i] && cmd[i + 1]) ? 1 : 0;
	path = (cmd[i]) ? ft_strdup(cmd[i]) : NULL;
	if (path && ft_strequ(path, "-"))
		err = go_oldpwd(env);
	else
	{
		path = ((!path || path[0] == '~')) ? copy_home(*env, path) : path;
		err = (!path) ? error("cd", "HOME", 7) : check_fold(path, env, p);
	}
	(err && err != 7) ? error("cd", cmd[i], err) : 0;
	ft_strdel(&path);
	ft_strdel(&p);
	return (err);
}
