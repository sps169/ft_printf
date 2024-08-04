NAME	=	libftprintf.a

SRC_DIR	=	./src/

INCLUDE	=	-Iinclude

CC	=	gcc

CFLAGS	= -Wall -Wextra -Werror

SRCS	=	$(SRC_DIR)ft_printf.c				\
			$(SRC_DIR)flags_parse.c				\
			$(SRC_DIR)justify_print.c			\
			$(SRC_DIR)utils.c					\
			$(SRC_DIR)ft_atoi.c					\
			$(SRC_DIR)ft_itoa.c					\
			$(SRC_DIR)ft_utoa_base.c			\
			$(SRC_DIR)ft_strjoin.c				\
			$(SRC_DIR)ft_substr.c				\
			$(SRC_DIR)ft_printf_handler.c		\
			$(SRC_DIR)ft_printf_handler_2.c		\
			$(SRC_DIR)ft_printf_hex_handler.c	\
			
OBJS		=	$(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all			:	$(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

bonus		:	$(NAME)

clean		:
				rm -f $(OBJS)

fclean		:	clean
				rm $(NAME)

re		:	fclean all

.PHONY: all clean fclean re
