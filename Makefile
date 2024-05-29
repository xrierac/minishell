NAME	:= minishell

#Compiler options#

CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror 
LFLAGS	:= -l readline -L /Users/$(USER)/.brew/opt/readline/lib
DFLAGS	:= -g -fsanitize=address,undefined

INC_DIR  := ./inc -I /Users/$(USER)/.brew/opt/readline/include
SRC_DIR  := ./src
OBJ_DIR  := .

LIBFT_DIR := ./lib/libft/
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS	:= 	$(SRC_DIR)/main.c $(SRC_DIR)/parsing/initialise.c $(SRC_DIR)/error_handling/free.c $(SRC_DIR)/error_handling/error.c \
			$(SRC_DIR)/parsing/parse_env.c $(SRC_DIR)/parsing/tokens.c $(SRC_DIR)/parsing/quotes.c $(SRC_DIR)/parsing/tokens_two.c \
			$(SRC_DIR)/parsing/expand_env.c $(SRC_DIR)/parsing/random_utils.c $(SRC_DIR)/parsing/syntax.c $(SRC_DIR)/parsing/syntax_two.c \
			$(SRC_DIR)/parsing/heredoc.c $(SRC_DIR)/parsing/heredoc_syntax.c $(SRC_DIR)/parsing/quotes_two.c\
			$(SRC_DIR)/exec/execute.c $(SRC_DIR)/exec/execution_branch.c $(SRC_DIR)/exec/pipe_management.c\
			$(SRC_DIR)/exec/redirect.c $(SRC_DIR)/exec/utils.c $(SRC_DIR)/parsing/pipes.c $(SRC_DIR)/exec/exit.c \
			$(SRC_DIR)/builtins/ft_cd.c $(SRC_DIR)/builtins/ft_echo.c \
			$(SRC_DIR)/builtins/ft_env.c $(SRC_DIR)/builtins/ft_pwd.c $(SRC_DIR)/builtins/builtin_check.c  $(SRC_DIR)/builtins/ft_exit.c\
			$(SRC_DIR)/builtins/ft_export.c $(SRC_DIR)/builtins/ft_unset.c $(SRC_DIR)/exec/signals.c $(SRC_DIR)/parsing/load_termios.c
	
OBJS	:= ${SRCS:.c=.o}

HEADERS := -I ./inc
LIBS	:= -lm $(LIBFT)

all: $(LIBFT) $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
	
		
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

debug: CFLAGS += $(DFLAGS)
debug: clean all

clean:
	make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean: clean
	rm -rf $(LIBFT)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libft, debug
