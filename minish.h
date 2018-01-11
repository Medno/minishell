/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:06:46 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/11 18:32:02 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# define PROMPT "$> "
# include "./libft/libft.h"
# include <sys/stat.h>

typedef struct stat	t_stat;

typedef struct	s_line
{
	char			*var;
	char			*value;
	struct s_line	*next;
}				t_line;

t_line			*fill_line(char **env);
void			s_env(t_line **env, char **cmd);
int				uns_env(t_line **env, char **cmd);

int				p_cd(t_line **env, char **cmd);

void			ft_echo(char **cmd);

t_line			*init_line(void);
t_line			*fill_line(char **env);
void			line_pushback(t_line **first, t_line *add);
char			**line_to_tab(t_line **first);
void			p_line(t_line *line);
int				clean_line(t_line **prev, t_line *tmp);
void			del_line(t_line **first);
int				error(char *built, char *cmd, int code);

#endif
