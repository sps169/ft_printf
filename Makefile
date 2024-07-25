NAME	=	libftprintf.a

SRC_DIR	=	./src/

INCLUDE	=	-Iinclude

CC	=	gcc

CFLAGS	=  -Wall -Wextra -Werror #-fsanitize=address -g3

SRCS	=	$(SRC_DIR)ft_printf.c			\
			$(SRC_DIR)utils.c				\
			$(SRC_DIR)ft_atoi.c				\
			$(SRC_DIR)ft_printf_handler.c	\
			$(SRC_DIR)ft_printf_handler_2.c	\
			
OBJS		=	$(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all			:	$(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean		:
				rm -f $(OBJS)

fclean		:	clean
				rm $(NAME)

re		:	fclean all

.PHONY: all clean fclean re
