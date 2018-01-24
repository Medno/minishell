/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 13:54:05 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/24 18:11:50 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

void	env_i(t_line *env, char **cmd, int i)
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
	t_line	*cpy_env;
	t_line	*add;

	i = 1;
	p = ft_getopt(cmd, &i);
	opt = ft_checkopt(p, "iu", 2);
	cpy_env = (p && ft_strchr(p, 'i')) ? init_line(NULL, NULL, NULL) : dup_line(env);
	if (p && ft_strchr(p, 'p'))
	{
		while (cmd[i] && ft_strchr(cmd[i], '='))
		{
			s_env(&cpy_env, &cmd[i]);
			i++;
		}
	}
	else if (p && ft_strchr(p, 'u') && cmd[i])
	{
		uns_env(cpy_env, &cmd[i]);
		i++;
	}
	if (cmd[i])
	{
		execute_cmd(&cpy_env, cmd[i]);
	}
	else if (opt == 0)
		p_line(cpy_env, 0, "");
	else
		usage("env", "iu", opt, 1);
	del_line(&cpy_env);
	ft_strdel(&p);
}
