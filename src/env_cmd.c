/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 13:54:05 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/15 17:22:42 by pchadeni         ###   ########.fr       */
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
	(fath > 0) ? wait(NULL) : 0;
	if (fath == 0 && cmd[i])
	{
		(path != NULL) ? check_bin(del, cmd + i, path->value) : 0;
		execve(cmd[i], cmd + i, del);
		error("env", cmd[i], 3);
		exit(0);
	}
	ft_tabdel(del);
}

void	n_env(t_line *env, char **cmd)
{
	char	*p;
	char	valid[2];
	int		i;

	i = 1;
	ft_strcpy(valid, "iu");
	p = ft_getopt(cmd, &i);
	if (!p)
		p_line(env, 0, NULL);
	else
	{
		if (ft_strchr(p, 'i') && cmd[i])
			env_null(env, cmd, i);
		else if (ft_strchr(p, 'u') && cmd[i])
			p_line(env, 1, cmd[i]);
		ft_strdel(&p);
	}
}
