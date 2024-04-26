NAME	:= minishell

#Compiler options#

CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -lreadline -g #-fsanitize=address

INC_DIR  := ./inc
SRC_DIR  := ./src
OBJ_DIR  := .

LIBFT_DIR := ./lib/libft/
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS	:= 	$(SRC_DIR)/main.c $(SRC_DIR)/initialise.c $(SRC_DIR)/free.c $(SRC_DIR)/error.c $(SRC_DIR)/pipes.c\
			$(SRC_DIR)/parse_env.c $(SRC_DIR)/tokens.c $(SRC_DIR)/quotes.c $(SRC_DIR)/tokens_two.c\
			$(SRC_DIR)/expand_env.c $(SRC_DIR)/random_utils.c $(SRC_DIR)/syntax.c $(SRC_DIR)/syntax_two.c
OBJS	:= ${SRCS:.c=.o}

HEADERS := -I ./inc
LIBS	:= -lm $(LIBFT)

all: $(LIBFT) $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
	
		
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean: clean
	rm -rf $(LIBFT)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libft
