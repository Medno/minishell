/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:15:59 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/05 10:39:35 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

static uint8_t	is_built(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "setenv") == 0)
		return (1);
	else if (ft_strcmp(str, "unsetenv") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

static void		exec_built(t_line **env, char **ncmd)
{
	(ft_strcmp(ncmd[0], "echo") == 0) ? ft_echo(*env, ncmd) : 0;
	(ft_strcmp(ncmd[0], "cd") == 0) ? p_cd(env, ncmd) : 0;
	(ft_strcmp(ncmd[0], "setenv") == 0) ? s_env(env, ncmd + 1) : 0;
	(ft_strcmp(ncmd[0], "unsetenv") == 0) ? uns_env(env, ncmd + 1) : 0;
	(ft_strcmp(ncmd[0], "env") == 0) ? n_env(*env, ncmd) : 0;
}

static int		check_bin(char **tenv, char **ncmd, char *path)
{
	char	*gap;
	int		i;

	i = 1;
	while ((gap = ft_strgap(path, ':', i)))
	{
		gap = ft_strjoinfree(gap, "/");
		gap = ft_strjoinfree(gap, ncmd[0]);
		if (!access(gap, F_OK) && access(gap, X_OK) == -1)
		{
			ft_strdel(&gap);
			ft_putstr("minishell: permission denied: ");
			ft_putendl(g_process);
			return (1);
		}
		execve(gap, ncmd, tenv);
		ft_strdel(&gap);
		i++;
	}
	return (0);
}

static void		exec_bin(t_line **env, char **ncmd)
{
	char	**tenv;
	t_line	*path;

	(ft_strequ(ncmd[0], "ls")) ? replace_ls(*env, ncmd) : 0;
	path = get_smtg(*env, "PATH");
	g_fath = fork();
	tenv = line_to_tab(env);
	signal(SIGINT, (void (*)(int))kill_child);
	if (g_fath == 0)
	{
		if (path != NULL && check_bin(tenv, ncmd, path->value))
			exit(0);
		execve(ncmd[0], ncmd, tenv);
		error("", ncmd[0], 5);
		(tenv != NULL) ? ft_tabdel(tenv) : 0;
		(ncmd != NULL) ? ft_tabdel(ncmd) : 0;
		exit(0);
	}
	if (g_fath > 0)
	{
		wait(&g_fath);
		ret_fath(g_fath);
	}
	(tenv != NULL) ? ft_tabdel(tenv) : 0;
}

uint8_t			execute_cmd(t_line **env, char *cmd)
{
	char			**ncmd;
	unsigned char	res;
	uint8_t			built;

	res = 254;
	if (!*cmd || !can_access())
		return (check_fold("/", env, NULL) + res);
	while (ft_iswsp(*cmd))
		cmd++;
	g_process = cmd;
	if (!*cmd || ((ncmd = ft_splitwsp(cmd)) == NULL))
		return (res);
	if (ncmd && ft_strcmp(ncmd[0], "exit") != 0)
	{
		built = is_built(ncmd[0]);
		(built > 0) ? exec_built(env, ncmd) : exec_bin(env, ncmd);
	}
	else
		res = p_exit(ncmd);
	ft_tabdel(ncmd);
	return ((res != 254) ? res : 254);
}
