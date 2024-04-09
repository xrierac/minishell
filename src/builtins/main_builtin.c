#include "../../inc/minishell.h"

void	ft_echo(char **arr, char **env);
void	ft_cd(char *str, char **env);
void	ft_pwd(void);

int	main(int argc, char *argv[], char **env)
{
	char	*input;
	char	**arr;

	while (1)
	{
		input = readline("\e[0;32mminishell>\e[0;37m");
		if (input == NULL)
			break ;
		arr = ft_split(input, ' ');
		if (!arr)
			return (0);
		if (!ft_strncmp(arr[0], "exit", ft_strlen(arr[0])))
		{
			free(input);
			ft_free_array(arr);
			return (0);
		}
		if (!ft_strncmp(arr[0], "echo", ft_strlen(arr[0])))
			ft_echo(arr, env);
		if (!ft_strncmp(arr[0], "cd", ft_strlen(arr[0])))
			ft_cd(arr[1], env);
		if (!ft_strncmp(arr[0], "pwd", ft_strlen(arr[0])))
			ft_pwd();
		ft_free_array(arr);
		free(input);
	}
	return (0);
}
