CFLAGS = -Wall -Wextra -Werror
NAME = philo

PC = table.c list.c roles.c utils1.c utils2.c utils3.c parse.c

PO = ${PC:.c=.o}

all : ${NAME}

${NAME} : ${PO}
	cc $^ -o $@ ${CFLAGS}

clean :
	${RM} ${PO}

fclean : clean
	${RM} ${NAME}

re : fclean all
