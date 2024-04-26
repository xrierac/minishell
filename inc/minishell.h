/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/04/03 15:34:27 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/24 17:53:19 by tcampbel         ###   ########.fr       */
=======
/*   Created: 2024/03/26 16:58:52 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/24 17:19:40 by xriera-c         ###   ########.fr       */
>>>>>>> a6a4aeae7e2605c1a5007d28e96446c3f67c5fe4
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/includes/libft.h"

# define GRN "\e[0;92m"
# define BLK "\e[0;90m"
# define RED "\e[0;91m"
# define END "\e[0m"

# define SYNTAX_ERROR "syntax error near unexpected token"

typedef enum e_token_type
{
	R_INPUT, //<
	R_OUTPUT, //>
	HEREDOC, //<<
	APPEND, //>>
	ENV, //$
	STATUS, //!?
	INFILE, //< str The string after r_input is always considered an infile 
	OUTFILE, //> str The string after r_output is always considered an outfile
	CMD, //str
	ARG, //"str" Any string after a cmd.
	FLAG, // -str Any string preceded by a '-' and following a str
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
	char			**cmd_arr;
}	t_lex;

typedef struct s_env
{
	char	**env_arr;
	char	*env_path;
	char	**path_arr;
	int		shlvl;
	int		var_len;
}	t_env;

typedef struct s_sh
{
	t_env	*env;
	t_lex	***lex_arr;
	int		tok_count;
	int		pipes;
	int		len;
	int		quotes; //Should probably delete
	int		count; //Should probably delete
	t_bool	error;
}	t_sh;

void	get_input(t_sh *msh);

//initialise sturcts

t_sh	*init_msh(char **ev);
t_lex	***init_lex(t_sh *msh);
void	init_token(t_sh *msh, t_lex **lex_arr);
void	init_env(t_env *env);

//environment 
void	get_path(t_sh *msh, t_env *env, char **ev, int i);
void	get_lvl(t_sh *msh, char **temp, int i);
int		cur_lvl(char *ev);
void	ft_envcpy(t_sh *msh, t_env *env, char **ev);

//tokens
void	get_token(t_sh *msh, t_lex *lex_arr, char *str);
void	lexer(char *input, t_sh *msh);
void	assign_token(t_sh *msh, t_lex *lex_arr, char **pipe_arr);
char	*deref_env_var(t_sh *msh, char *input);
void	is_token(t_sh *msh, char *str);
void	count_pipes(t_sh *msh, char *input);

//syntax

void	check_r_input(t_sh *msh, char *str, int i);
void	check_str(t_sh *msh, char *temp);
void	check_r_output(t_sh *msh, char *str, int i);
void	check_heredoc(t_sh *msh, char *str, int i);
void	check_append(t_sh *msh, char *str, int i);
char	*choose_op(char c);
char	*syntax_check(t_sh *msh, char *temp);

//errors and free

void	exit_error(t_sh *msh, char *msg, int status);
void	free_all(t_sh *msh);
void	free_lex(t_lex **lex);
void	free_env(t_env *env);

//tools

int		find_quote(char *str, char q, int i);
t_bool	ft_isspace(char str);
char	*redirect_in(t_sh *msh, char *input);
t_bool	ft_isspace(char str);
int		iter_str(char *str, int i);
t_bool	is_op(char *str, int i);
void	count_quotes(t_sh *msh, char *str);
char	set_quote(char	*str);
int		is_file(t_sh *msh, char *str, int i);

//environment variables

<<<<<<< HEAD
char	*update_str(t_sh *msh, char *var, char *str);
char	*insert_str(char *var, char *str, char *temp, int end);
char	*check_exit_code(t_sh *msh, char *str, int i);
char	*expand_env(t_sh *msh, char *str);

=======
>>>>>>> a6a4aeae7e2605c1a5007d28e96446c3f67c5fe4
#endif
