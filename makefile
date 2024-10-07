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

GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m

all : $(CLIENT) $(SERVER)

$(SERVER) : $(OBJ_S) $(INC)
	@ $(CC) $(FLAGS) $(UTILS) -o $@ $(OBJ_S)
	@printf "$(GREEN) server ready✅\n$(RESET)"

$(CLIENT) : $(OBJ_C) $(INC)
	@ $(CC) $(FLAGS) $(UTILS) -o $@ $(OBJ_C)
	@printf "$(GREEN) client ready✅\n$(RESET)"

%.o: %.c
	@ $(CC) $(FLAGS) -c $< -o $@

clean:
	@ $(RM) $(OBJ_C) $(OBJ_S)
	@printf "$(YELLOW) object files removed.\n$(RESET)"

fclean: clean
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "$(YELLOW) client removed.\n$(RESET)"
	@printf "$(YELLOW) server removed.\n$(RESET)"

re : fclean all

.PHONY: all clean fclean re