
NAME=minishell

CC=gcc

FLAGS=-Wall -Werror -Wextra

SRCS=	./main/signals.c \
		./main/tokenizer.c \
		./main/expander.c \
		./main/main.c \

OBJS=$(SRCS:.c=.o)

%.o:%.c
		$(CC) $(FLAGS) -c $< -o $@

LIBFT=./libft/libft.a

READLINE = -L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib \
				-I$(HOME)/.brew/opt/readline/include \

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME) $(READLINE)

$(LIBFT):
		$(MAKE) -C ./libft/

all:$(NAME)

clean:
		rm -f *.o
		$(MAKE) clean -C ./libft

fclean: clean
		rm -f $(NAME)
		$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
