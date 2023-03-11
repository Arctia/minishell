
NAME=minishell

CC=gcc

FLAGS=-Wall -Werror -Wextra -g

INCS = ./global.h ./executor/executor.h

SRCS=	./main/signals2_0.c \
		./main/signals.c \
		./main/tokenizer.c \
		./main/expander.c \
		./main/env_handlers.c \
		./main/main.c \
		./minishell_lexer/lexer/lexer.c \
		./minishell_lexer/lexer/lexer_splitter.c \
		./parser/parser.c \
		./executor/executor.c \
		./executor/ft_execv.c \
		./executor/pipe.c \
		./executor/redir.c

OBJS=$(SRCS:.c=.o)

%.o:%.c $(INCS)
		$(CC) $(FLAGS) -c $< -o $@

LIBFT=./libft/libft.a

READLINE = -L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib \
				-I$(HOME)/.brew/opt/readline/include

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME) $(READLINE)

$(LIBFT):
		$(MAKE) -C ./libft/

all:$(NAME)

clean:
		rm -f *.o
		rm -f main/*.o
		rm -f minishell_lexer/lexer/*.o
		rm -f parser/*.o
		rm -f executor/*.o
		$(MAKE) clean -C ./libft

fclean: clean
		rm -f $(NAME)
		$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
