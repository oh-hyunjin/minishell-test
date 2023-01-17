PARSING_DIR = ./parsing
PARSING_NAME =  parsing.c 
PARSING =  ${addprefix $(PARSING_DIR)/, $(PARSING_NAME)}
PARSING_OBJS = $(PARSING:.c=.o)

LIBFT_DIR = ./libft
LIBFT = ft


NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -rcs

$(SRCS_DIR)/%.o : %.c
	$(CC) -g3 $(CFLAGS) -c $<  -I$(LIBFT_DIR) -I$(PARSING_DIR)


all : $(NAME)

$(NAME) : $(PARSING_OBJS)
	$(MAKE) -C $(LIBFT_DIR) bonus
	
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT) $^ -o $@


clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(PARSING_OBJS)

fclean :
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(PARSING_OBJS)
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
