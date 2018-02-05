/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_opt_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:15:10 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/05 14:21:17 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

static int	step_8(char *tmp, t_line *pwd, t_line *oldpwd)
{
	int	check;

	clean_path(&tmp);
	check = check_path(tmp, 0);
	if (check == 0)
	{
		ft_strdel(&(oldpwd->value));
		oldpwd->value = ft_strdup(pwd->value);
		ft_strdel(&(pwd->value));
		pwd->value = ft_strdup(tmp);
		chdir(pwd->value);
	}
	ft_strdel(&tmp);
	return (check);
}

static int	comp_path(t_list **first, t_list **list, t_list **prev, char **tmp)
{
	int8_t	check;

	check = 0;
	if (*list && (check = check_access_fold(*list, *tmp)) == -1)
	{
		if (*list == *first)
			*first = (*list)->next->next;
		else
			(*prev)->next = ((*list)->next) ? (*list)->next->next : NULL;
		ft_lstdelone(&(*list)->next, ft_lstclean);
		ft_lstdelone(list, ft_lstclean);
		ft_strdel(tmp);
		*tmp = ft_strdup("/");
		*list = *first;
		*prev = *list;
	}
	else if (*list && check == 0)
	{
		*tmp = ft_strjoinfree(*tmp, (char *)(*list)->content);
		*tmp = ft_strjoinfree(*tmp, "/");
	}
	*prev = *list;
	*list = ((*list) && check != -1) ? (*list)->next : *list;
	return (check);
}

static void	epur_lst(t_list **first)
{
	t_list	*tmp;
	t_list	*prev;

	while (*first && ft_strequ((*first)->content, "."))
	{
		tmp = (*first);
		(*first) = tmp->next;
		ft_lstdelone(&tmp, ft_lstclean);
	}
	tmp = (*first);
	prev = tmp;
	while (tmp)
	{
		if (ft_strequ(tmp->content, "."))
		{
			prev->next = tmp->next;
			ft_lstdelone(&tmp, ft_lstclean);
			tmp = prev->next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

static int	final_curpath(char *str, t_line *pwd, t_line *oldpwd)
{
	t_list	*list;
	t_list	*first;
	t_list	*prev;
	char	*tmp;
	int8_t	check;

	first = ft_lstsplit(str, '/');
	check = 0;
	list = first;
	prev = list;
	tmp = ft_strdup("/");
	epur_lst(&first);
	while (list && check != 3)
		check = comp_path(&first, &list, &prev, &tmp);
	(first) ? ft_lstdel(&first, ft_lstclean) : 0;
	if (check != -1 && check != 0)
		ft_strdel(&tmp);
	else
		check = step_8(tmp, pwd, oldpwd);
	check = (check < 0) ? 0 : check;
	return (check);
}

int			opt_l(char *curpath, t_line **env)
{
	char	*tmp;
	int		res;
	t_line	*pwd;
	t_line	*oldpwd;

	pwd = get_smtg(*env, "PWD");
	oldpwd = get_pwd(env, "OLDPWD");
	if (curpath[0] != '/')
	{
		tmp = ft_strdup(pwd->value);
		if (ft_lastchar(pwd->value) != '/')
			tmp = ft_strjoinfree(tmp, "/");
		tmp = ft_strjoinfree(tmp, curpath);
	}
	else
		tmp = ft_strdup(curpath);
	res = final_curpath(tmp, pwd, oldpwd);
	ft_strdel(&tmp);
	return (error("cd", curpath, res));
}
