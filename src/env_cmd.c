/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 13:54:05 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/29 15:00:10 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

static void	exec_new_env(t_line **env, char **cmd, int opt, int i)
{
	if (cmd && cmd[i])
		execute_cmd(env, cmd[i]);
	else if (opt == 0)
		p_line(*env);
	else
		usage("env", "iu", opt, 1);
}

void		n_env(t_line *env, char **cmd)
{
	char	*p;
	int		i;
	int		opt;
	t_line	*cpy;

	i = 1;
	p = ft_getopt(cmd, &i);
	opt = ft_checkopt(p, "iu", 2);
	cpy = (p && ft_strchr(p, 'i')) ? init_line(&cpy, NULL) : dup_line(env);
	if ((p && ft_strchr(p, 'i')) || !p)
	{
		while (cmd[i] && ft_strchr(cmd[i], '='))
		{
			init_line(&cpy, cmd[i]);
			i++;
		}
	}
	else if (p && ft_strchr(p, 'u') && cmd[i])
	{
		del_one_env(&cpy, cmd[i]);
		i++;
	}
	exec_new_env(&cpy, cmd, opt, i);
	del_line(&cpy);
	ft_strdel(&p);
}
