#include "../../inc/minishell.h"

void	ft_echo(char **arr);

int	main(void)
{
	char	*input;
	char	**arr;

	while (1)
	{
		input = readline("\e[0;32mminishell>\e[0;37m");
		if (input == NULL)
			break ;
		if (!ft_strncmp(input, "exit", 4))
		{
			free(input);
			return (0);
		}
		if (!ft_strncmp(input, "echo", 4))
		{
			arr = ft_split(input, ' ');
			ft_echo(arr);
			ft_free_array(arr);
		}
		free(input);
	}
	return (0);
}
