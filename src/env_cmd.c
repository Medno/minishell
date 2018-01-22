/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 13:54:05 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/16 18:17:51 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

void	env_null(t_line *env, char **cmd, int i)
{
	pid_t	fath;
	char	**del;
	t_line	*path;

	path = get_smtg(env, "PATH");
	if (!(del = (char **)malloc(sizeof(char *) + 1)))
		return ;
	del[0] = NULL;
	fath = fork();
	if (fath == 0 && cmd + i)
	{
		(path != NULL) ? check_bin(del, cmd + i, path->value) : 0;
		execve(cmd[i], cmd + i, del);
		error("env", cmd[i], 3);
		exit(0);
	}
	if (fath > 0)
	   wait(&fath);
	ft_tabdel(del);
}

void	n_env(t_line *env, char **cmd)
{
	char	*p;
	int		i;
	int		opt;

	i = 1;
	p = ft_getopt(cmd, &i);
	opt = ft_checkopt(p, "iu", 2);
	if (!p && opt == 0)
		p_line(env, 0, "");
	else if (opt == 0)
	{
		if (ft_strchr(p, 'i') && cmd[i])
			env_null(env, cmd, i);
		else if (ft_strchr(p, 'u') && cmd[i])
			p_line(env, 1, cmd[i]);
		ft_strdel(&p);
	}
	else
		usage("env", "iu", opt, 1);
	ft_strdel(&p);
}
