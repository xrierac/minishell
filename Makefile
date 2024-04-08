NAME	:= minishell

#Compiler options#

CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -lreadline -g

INC_DIR  := ./inc
SRC_DIR  := ./srcs
OBJ_DIR  := .

LIBFT_DIR := ./lib/libft/
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS	:= $(SRC_DIR)/main.c $(SRC_DIR)/initialise.c $(SRC_DIR)/free.c $(SRC_DIR)/error.c
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
