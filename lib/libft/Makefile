#---------------------------------Archive-------------------------------------#
NAME = libft.a

#---------------------------------Flags---------------------------------------#
CC = @cc
CFLAGS = -Wall -Wextra -Werror -I includes
RM = @rm -rf

#---------------------------------Directories---------------------------------#
SRC_DIR = srcs
LIBFT_DIR = srcs/libft
FT_PRINTF_DIR = srcs/ft_printf
GNL_DIR = srcs/get_next_line

#---------------------------------Source Files--------------------------------#

SRC_FLS = 	$(LIBFT_FLS)\
			$(FT_PRINTF_FLS)\
			$(GNL_FLS)

LIBFT_FLS = $(LIBFT_DIR)/ft_atoi.c $(LIBFT_DIR)/ft_atol.c $(LIBFT_DIR)/ft_isalpha.c $(LIBFT_DIR)/ft_memchr.c\
			$(LIBFT_DIR)/ft_memset.c $(LIBFT_DIR)/ft_strlcpy.c $(LIBFT_DIR)/ft_strrchr.c\
			$(LIBFT_DIR)/ft_bzero.c $(LIBFT_DIR)/ft_isascii.c $(LIBFT_DIR)/ft_memcmp.c\
			$(LIBFT_DIR)/ft_strchr.c $(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/ft_tolower.c\
			$(LIBFT_DIR)/ft_calloc.c $(LIBFT_DIR)/ft_isdigit.c $(LIBFT_DIR)/ft_memcpy.c\
			$(LIBFT_DIR)/ft_strdup.c $(LIBFT_DIR)/ft_strncmp.c $(LIBFT_DIR)/ft_toupper.c\
			$(LIBFT_DIR)/ft_isalnum.c $(LIBFT_DIR)/ft_isprint.c $(LIBFT_DIR)/ft_memmove.c\
			$(LIBFT_DIR)/ft_strlcat.c $(LIBFT_DIR)/ft_strnstr.c $(LIBFT_DIR)/ft_putstr_fd.c\
			$(LIBFT_DIR)/ft_putchar_fd.c $(LIBFT_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/ft_putnbr_fd.c\
			$(LIBFT_DIR)/ft_substr.c $(LIBFT_DIR)/ft_strjoin.c $(LIBFT_DIR)/ft_strtrim.c\
			$(LIBFT_DIR)/ft_strmapi.c $(LIBFT_DIR)/ft_striteri.c $(LIBFT_DIR)/ft_itoa.c\
			$(LIBFT_DIR)/ft_split.c $(LIBFT_DIR)/ft_lstnew.c $(LIBFT_DIR)/ft_lstadd_front.c\
			$(LIBFT_DIR)/ft_lstsize.c $(LIBFT_DIR)/ft_lstlast.c $(LIBFT_DIR)/ft_lstadd_back.c\
			$(LIBFT_DIR)/ft_lstdelone.c $(LIBFT_DIR)/ft_lstclear.c $(LIBFT_DIR)/ft_lstiter.c\
			$(LIBFT_DIR)/ft_lstmap.c $(LIBFT_DIR)/ft_free_array.c $(LIBFT_DIR)/ft_skip_split.c\
			$(LIBFT_DIR)/tripjoin.c $(LIBFT_DIR)/ft_sleep.c $(LIBFT_DIR)/ft_strtok.c $(LIBFT_DIR)/return_free_array.c

FT_PRINTF_FLS = $(FT_PRINTF_DIR)/ft_printf.c $(FT_PRINTF_DIR)/str_handler.c\
				$(FT_PRINTF_DIR)/ft_putnbr_count.c $(FT_PRINTF_DIR)/ft_putstr_count.c\
				$(FT_PRINTF_DIR)/ft_putchar_count.c $(FT_PRINTF_DIR)/ft_puthex_count.c\

GNL_FLS = 	$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c\

#---------------------------------Colours-------------------------------------#
GREEN= \033[1;32m
CYAN= \033[1;36m
PURPLE= \033[1;35m
END= \033[0m

#---------------------------------Rules---------------------------------------#
all: $(NAME)

OBJS = $(SRC_FLS:.c=.o)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "${GREEN}Libft Compiled Successfully${END}"

clean:
	$(RM) $(OBJS)
	@echo "${GREEN}Libft Cleaned${END}"
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
