NAME	:= minishell

#Compiler options#

CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror 
LFLAGS	:= -l readline -L /Users/xriera-c/.brew/opt/readline/lib
DFLAGS	:= -g -fsanitize=address,undefined

INC_DIR  := ./inc -I /Users/xriera-c/.brew/opt/readline/include
SRC_DIR  := ./src
OBJ_DIR  := .

LIBFT_DIR := ./lib/libft/
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS	:= 	$(SRC_DIR)/main.c $(SRC_DIR)/initialise.c $(SRC_DIR)/free.c $(SRC_DIR)/error.c \
			$(SRC_DIR)/parse_env.c $(SRC_DIR)/tokens.c $(SRC_DIR)/quotes.c $(SRC_DIR)/tokens_two.c \
			$(SRC_DIR)/expand_env.c $(SRC_DIR)/random_utils.c $(SRC_DIR)/syntax.c $(SRC_DIR)/syntax_two.c \
			$(SRC_DIR)/exec/execute.c $(SRC_DIR)/exec/execution_branch.c $(SRC_DIR)/exec/pipe_management.c\
			$(SRC_DIR)/exec/redirect.c $(SRC_DIR)/exec/utils.c $(SRC_DIR)/pipes.c $(SRC_DIR)/exec/exit.c \
			$(SRC_DIR)/builtins/ft_cd.c $(SRC_DIR)/builtins/ft_echo.c \
			$(SRC_DIR)/builtins/ft_env.c $(SRC_DIR)/builtins/ft_pwd.c $(SRC_DIR)/builtins/builtin_check.c \
			$(SRC_DIR)/builtins/ft_export.c $(SRC_DIR)/builtins/ft_unset.c $(SRC_DIR)/exec/signals.c
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
