/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:58:52 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/16 11:24:16 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/includes/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>

# define GRN "\e[0;92m"
# define BLK "\e[0;90m"
# define RED "\e[0;91m"
# define END "\e[0m"

# define SYNTAX_ERROR "syntax error near unexpected token"

# define MAX_FD 256

typedef enum e_token_type
{
	R_INPUT,
	R_OUTPUT,
	HEREDOC,
	APPEND,
	STATUS,
	CMD,
	NOT_DEF,
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
	char	**pipe_arr;
	int		tok_count;
	int		pipes;
	int		processes;
	int		count;
	int		quotes;
	t_bool	error;
	char	*buffer;
	char	*var;
	int		buf_len;
}	t_sh;

void	get_input(t_sh *msh);

//initialise sturcts

t_sh	*init_msh(char **ev);
t_lex	***init_lex(t_sh *msh);
t_lex	**init_token(t_sh *msh);
void	init_env(t_env *env);
char	**init_cmd_arr(t_sh *msh);

//environment 
void	get_path(t_sh *msh, t_env *env, char **ev, int i);
void	get_lvl(t_sh *msh, char **temp, int i);
int		cur_lvl(char *ev);
void	ft_envcpy(t_sh *msh, t_env *env, char **ev);

//tokens
void	lexer(char *input, t_sh *msh);
void	assign_token(t_sh *msh, t_lex **lex_arr, char *cmd);
char	*deref_env_var(t_sh *msh, char *input);
void	is_token(t_sh *msh, char *str);
void	count_pipes(t_sh *msh, char *input);
int		tokenise_cmd(t_sh *msh, t_lex *lex, char *cmd, int j);
int		tokenise_op(t_sh *msh, t_lex *lex, char *cmd, int j);
void	token_type(t_sh *msh, t_lex *lex, char *cmd, int j);

//syntax

void	check_str(t_sh *msh, char *temp);
void	check_pipes(t_sh *msh, char *input);
char	*choose_op(char *c);
char	*syntax_check(t_sh *msh, char *temp);
char	*check_op_syntax(t_sh *msh, char *str);
int		current_op(char *str);

//errors and free

void	exit_error(t_sh *msh, char *msg, int status);
void	free_all(t_sh *msh);
void	free_lex(t_sh *msh, t_lex ***lex);
void	free_env(t_env *env);
void	free_msh(t_sh *msh);

//tools

int		find_quote(char *str, char q, int i);
t_bool	ft_isspace(char str);
t_bool	is_op(char *str, int i);
void	count_quotes(t_sh *msh, char *str);
char	set_quote(char	*str, int i);
int		is_file(t_sh *msh, char *str, int i);
int		find_space(char *str, int i);
int		find_op(char *str, int i);
char	*remove_quotes(t_sh *msh, char *str);
int		quote_search(char *str);
char	*find_quote_ptr(char *str, char q);

//environment variables

char	*check_exit_code(t_sh *msh, char *str, int i);
char	*expand_env(t_sh *msh, char *str);
char	*check_env_var(t_sh *msh, t_env *env, char *var);
char	*extract_var(t_sh *msh, char *start, int len);

//ERROR HANDLING
void 	error_exit(void);
void 	error_cmd_not_found(char *str);
int		generic_error(char *str, char *cmd);


//EXECUTION
int		execute(t_lex *lex, t_env *env);
void	r_input(char **cmd_arr);
void	r_output(char **cmd_arr);
void	r_append(char **cmd_arr);
void	r_heredoc(char **cmd_arr);
int		execution_branch(t_sh *sh_data);
int 	pipe_management(t_sh *sh_data, int index, int pipefd[][2]);
int 	close_pipes(int pipefd[][2], int index, t_sh *sh_data);

//BUILTINS
int	builtin_check(char **cmd, t_env *env);
int	run_builtin(t_sh *sh_data, char **cmd);
int	ft_echo(char **arr, char **env);
int	ft_cd(char *str, t_env *env_s);
int	ft_pwd(void);
int	ft_env(char **env);
int	ft_export(t_env *env_s, char **cmd, int arg);
int	ft_unset(t_env *env_s, char **cmd, int arg);

//EXECUTION UTILS
char	*ft_getenv(const char *name, char **env);
size_t	array_size(char **arr);
int		new_path_arr(t_env *env_s, char *str);
char	*get_name(char *str);
size_t	find_equal_sign(char *str);


//TESTING TO BE DELETED

void    print_arr(char **str);

#endif
