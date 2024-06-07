/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:58:52 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/07 10:30:58 by xriera-c         ###   ########.fr       */
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
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <signal.h>
# include <sys/wait.h>

# define RED "\e[0;91m"
# define END "\e[0m"

# define SYNTAX_ERROR "syntax error near unexpected token"

# define MAX_FD 256
# define MAX_ARGS 262144
# define INT_MAX 2147483647

extern int	g_num;

typedef enum e_token_type
{
	R_INPUT,
	R_OUTPUT,
	VALID_HD,
	SKIP_HD,
	APPEND,
	AMB_RD,
	CMD,
}	t_token_type;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_lex
{
	t_token_type	token;
	int				fd;
	char			**cmd_arr;
}	t_lex;

typedef struct s_env
{
	char	**env_arr;
	char	*env_path;
	char	**path_arr;
	int		shlvl;
	int		var_len;
	char	*home;
}	t_env;

typedef struct s_sh
{
	t_env			*env;
	t_lex			***lex_arr;
	char			**pipe_arr;
	int				tok_count;
	int				pipes;
	int				processes;
	int				count;
	t_bool			error;
	char			*buffer;
	char			*var;
	int				buf_len;
	int				max_len;
	int				hd_fd[16][2];
	int				exit_code;
	int				exit_code_flag;
	char			*cmd;
	struct termios	old;
	struct termios	new;
	int				valid_hd;
	int				flag;
}	t_sh;

void	get_input(t_sh *msh);

//INITIALISE
t_sh	*init_msh(char **ev);
void	init_lex(t_sh *msh);
t_lex	**init_token(t_sh *msh);
void	init_env(t_env *env);
char	**init_cmd_arr(t_sh *msh);

//ENVIRONMENT 
void	get_path(t_sh *msh, t_env *env, char **ev, int i);
void	get_lvl(t_sh *msh, char **temp, int i);
int		cur_lvl(char *ev);
void	ft_envcpy(t_sh *msh, t_env *env, char **ev);
int		env_memory(t_sh *msh);
void	load_termios(t_sh *msh);
char	*tcsetreadline(t_sh *msh, int n);
void	get_home(t_sh *msh, char **env);
void	new_pwd(t_sh *msh, t_env *env_s);

//TOKENS
void	lexer(char *input, t_sh *msh);
void	assign_token(t_sh *msh, t_lex **lex_arr, char *cmd, int proc);
char	*deref_env_var(t_sh *msh, char *input);
void	is_token(t_sh *msh, char *str);
void	count_pipes(t_sh *msh, char *input);
int		tokenise_cmd(t_sh *msh, t_lex *lex, char *cmd, int j);
int		tokenise_op(t_sh *msh, t_lex *lex, char *cmd, int j);
void	token_type(t_lex *lex, char *cmd, int j);

//SYNTAX
void	check_str(t_sh *msh, char *temp);
char	*choose_op(char *c);
char	*syntax_check(t_sh *msh, char *temp);
char	*check_op_syntax(t_sh *msh, char *str);
int		current_op(char *str);

// HEREDOC
void	heredoc(t_sh *msh, char *str);
t_bool	check_heredoc(char *cmd, int j);
int		check_delim(char c);
t_bool	check_heredoc(char *cmd, int j);
t_bool	is_hd_valid(char *cmd, int j);
int		is_eof(char *str, int i);
int		heredoc_cleaning(int *fd, int stdin_cpy, char *delim, char *input);
int		find_hd(char *str);

//ERROR/FREE/CLOSE
void	exit_error(t_sh *msh, char *msg, int status);
void	free_all(t_sh *msh);
void	free_lex(t_lex ***lex);
void	free_env(t_env *env);
void	free_msh(t_sh *msh);
void	close_hd_fd(int fd);
void	close_all_hd_fd(t_sh *msh);
void	free_var(t_sh *msh);
int		error_cmd_not_found(char *str);
int		generic_error(char *str, char *cmd);
int		non_perror(char *str, char *cmd);
void	exit_child(t_sh *msh);

//TOOLS
int		find_quote(char *str, char q, int i);
t_bool	ft_isspace(char str);
t_bool	is_op(char *str, int i);
void	count_quotes(t_sh *msh, char *str);
char	set_quote(char	*str, int i);
int		is_file(t_sh *msh, char *str, int i);
int		find_space(char *str, int i);
int		find_op(char *str, int i);
char	*remove_quotes(t_sh *msh, char *str, int i);
int		quote_search(char *str);
char	*find_quote_ptr(char *str, char q);
int		skip_quotes(char *str, int i);

//ENVIRONMENT VARIABLES
char	*fetch_exit_code(t_sh *msh, char *ptr);
char	*expand_env(t_sh *msh, char *str);
char	*check_env_var(t_sh *msh, t_env *env, char *var);
char	*extract_var(t_sh *msh, char *start, int len);
char	*handle_dquote(t_sh *msh, char *ptr);
char	*handle_squote(t_sh *msh, char *ptr);
char	*deref_var(t_sh *msh, char *ptr);
char	*env_var_type_check(char *ptr);
void	handle_expansion(t_sh *msh, char *cmd);
int		redirect_check(char *ptr);
char	*cpy_og_var(t_sh *msh, char *ptr, int hd_flag);
char	*amb_redirect_check(t_sh *msh, char *ptr);
char	*deref_home(t_sh *msh, char *ptr);
int		valid_home_deref(char *ptr);

//EXECUTION
int		execute(t_lex *lex, t_env *env);
int		r_input(char **cmd_arr);
int		r_output(char **cmd_arr);
int		r_append(char **cmd_arr);
int		r_heredoc(t_lex *lex);
int		execution_branch(t_sh *sh);
int		pipe_management(t_sh *sh, int index, int in, int fd[]);
int		close_pipes(int in, int fda, int fdb);

//BUILTINS
int		builtin_check(char **cmd, t_env *env);
int		run_builtin(t_sh *sh_data, char **cmd);
int		ft_echo(char **arr, char **env);
int		ft_cd(char *str, t_env *env_s);
int		ft_pwd(t_env *env);
int		ft_env(char **env);
int		ft_export(t_env *env_s, char **cmd, int arg);
int		ft_unset(t_env *env_s, char **cmd, int arg);
int		ft_exit(t_sh *msh, char **cmd);

//EXECUTION UTILS
char	*ft_getenv(const char *name, char **env);
size_t	array_size(char **arr);
int		new_path_arr(t_env *env_s, char *str);
char	*get_name(char *str);
int		find_equal_sign(char *str);
char	*return_ptr_cwd(t_env *env_s);

//SIGNALS

void	rl_replace_line(const char *text, int clear_undo);
void	receive_signal(int val);
void	when_sigint(t_sh *msh, int *fd, int stdin_cpy);

#endif
