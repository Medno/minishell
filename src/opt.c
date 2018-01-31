/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:24:38 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/31 10:09:31 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

static void	modify_one_cmd(t_line *env, char **cmd, int i)
{
	t_line	*pwd;
	t_line	*oldpwd;
	t_line	*home;

	pwd = get_smtg(env, "PWD");
	oldpwd = get_smtg(env, "OLDPWD");
	home = get_smtg(env, "HOME");
	if (ft_strequ(cmd[i], "~+") && pwd)
	{
		ft_strdel(&cmd[i]);
		cmd[i] = ft_strdup(pwd->value);
	}
	else if (ft_strequ(cmd[i], "~-") && oldpwd)
	{
		ft_strdel(&cmd[i]);
		cmd[i] = ft_strdup(oldpwd->value);
	}
	else if (ft_strequ(cmd[i], "~") && home)
	{
		ft_strdel(&cmd[i]);
		cmd[i] = ft_strdup(home->value);
	}
}

void		replace_ls(t_line *env, char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		modify_one_cmd(env, cmd, i);
		i++;
	}
}

uint8_t		can_access(void)
{
	char	*try;
	int		res;

	try = NULL;
	try = getcwd(try, 0);
	res = (access(try, F_OK) == -1) ? 0 : 1;
	ft_strdel(&try);
	return (res);
}
