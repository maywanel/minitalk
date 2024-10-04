CC	=	gcc
FLAGS	=	-Wall -Werror -Wextra -I.
CLIENT	=	client
SERVER	=	server
SRC_C	=	client.c
SRC_S	=	server.c
OBJ_S	=	server.o
OBJ_C	=	client.o
INC		=	minitalk.h
UTILS	=	utils.c
RM	=	rm -rf

all : $(CLIENT) $(SERVER)

$(SERVER) : $(OBJ_S) $(INC)
	$(CC) $(FLAGS) $(UTILS) -o $@ $(OBJ_S)

$(CLIENT) : $(OBJ_C) $(INC)
	$(CC) $(FLAGS) $(UTILS) -o $@ $(OBJ_C)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_C) $(OBJ_S)

fclean: clean
	$(RM) $(CLIENT) $(SERVER)

re : fclean all

.PHONY: all clean fclean re