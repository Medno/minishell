/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:49:53 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/29 17:32:20 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*get_pwd(t_line **env, char *str)
{
	t_line *pwd;

	pwd = NULL;
	if (*env)
	{
		pwd = *env;
		while (pwd)
		{
			if (ft_strequ(pwd->var, str))
				return (pwd);
			pwd = pwd->next;
		}
	}
	pwd = init_line(env, "");
	pwd->var = ft_strdup(str);
	pwd->value = getcwd(pwd->value, 0);
	return (pwd);
}

t_line	*get_smtg(t_line *env, char *str)
{
	t_line	*path;

	path = env;
	while (path)
	{
		if (ft_strcmp(path->var, str) == 0)
			return (path);
		path = path->next;
	}
	return (NULL);
}
