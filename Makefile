SRCS = main.c get_path.c

SRCS_DIR = $(addprefix srcs/, $(SRCS))

OBJS = ${SRCS_DIR:.c=.o}

BN = pipex-bonus.c get_path.c pipex-bonus-utils.c pipex-bonus-utils-more.c

BN_DIR = $(addprefix srcs/, $(BN))

BN_OBJS = ${BN_DIR:.c=.o}

NAME = pipex

LIBFT = Libft/libft.a

PRINT_F = Printf/libftprintf.a

GNL = GNL/gnl.a

CC = cc
C_FLAGS = -Wall -Wextra -Werror -g
RM = rm -f

all : $(NAME)

.c.o :
		${CC} ${C_FLAGS} -c $< -o ${<:.c=.o}


$(NAME) : ${LIBFT} ${PRINT_F} ${OBJS}
		  ${CC} ${C_FLAGS} ${OBJS} ${LIBFT} ${PRINT_F} -o ${NAME}

bonus : ${LIBFT} ${PRINT_F} ${GNL} ${BN_OBJS}
		  ${CC} ${C_FLAGS} ${BN_OBJS} ${GNL} ${LIBFT} ${PRINT_F} -o ${NAME}

$(LIBFT) :
		  @make -C ./Libft

$(PRINT_F) :
			@make -C ./Printf

$(GNL) :
		@make -C ./GNL

clean :	
		@make clean -C ./Libft
		@make clean -C ./Printf
		@make clean -C ./GNL
		${RM} ${OBJS} ${BN_OBJS}

fclean : clean
		${RM} ${NAME} ${LIBFT} ${PRINT_F} ${GNL}

re : fclean all

.PHONY : all clean fclean re