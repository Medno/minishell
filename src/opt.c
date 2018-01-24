/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:24:38 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/24 11:25:28 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

void	replace_ls(t_line *env, char **cmd)
{
	t_line	*pwd;
	t_line	*oldpwd;
	int		i;

	i = 0;
	pwd = get_smtg(env, "PWD");
	oldpwd = get_smtg(env, "OLDPWD");
	while (cmd[i])
	{
		if (ft_strequ(cmd[i], "~+") && pwd)
		{
			ft_strdel(&cmd[i]);
			cmd[i] = ft_strdup(pwd->value);
		}
		if (ft_strequ(cmd[i], "~-") && oldpwd)
		{
			ft_strdel(&cmd[i]);
			cmd[i] = ft_strdup(oldpwd->value);
		}
		i++;
	}
}
