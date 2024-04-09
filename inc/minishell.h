/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:34:27 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/09 16:28:26 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/includes/libft.h"

# define HGRN "\e[0;92m"
# define HBLK "\e[0;90m"
# define HRED "\e[0;91m"
# define RESET "\e[0m"

typedef enum e_token_type
{
	S_QUOTE, //'
	D_QUOTE, //"
	R_INPUT, //<
	R_OUTPUT, //>
	HEREDOC, //<<
	APPEND, //>>
	PIPE, //|
	ENV, //$
	STATUS, //$?
	CMD,
	ARG,
	NOT_DEF
}	t_token_type;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_lex
{
	t_token_type	token;
	char			**tok_arr;
}	t_lex;

typedef struct s_env
{
	char	**env_arr;
	char	*env_path;
	char	**path_arr;
	int		shlvl;
}	t_env;

typedef struct s_sh
{
	t_env	*env;
	t_lex	**lex_arr;
	int		tok_count;
	int		pipes;
	int		len;
}	t_sh;

void	get_input(t_sh *msh);
void	ft_envcpy(t_sh *msh, t_env *env, char **ev);
t_sh	*initialise(char **ev);
void	exit_error(t_sh *msh, char *msg, int status);
void	get_path(t_sh *msh, t_env *env, char **ev, int i);
void	get_lvl(t_sh *msh, char **temp, int i);
void	free_all(t_sh *msh);
void	free_lex(t_lex **lex);
void	free_env(t_env *env);
void	lexer(char *input, t_sh *msh);
int		cur_lvl(char *ev);
void	count_tokens(char *input, t_sh *msh);
t_lex	**init_lex(t_sh *msh);
void	count_pipes(t_sh *msh, char *input);

#endif
