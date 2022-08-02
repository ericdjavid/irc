#	MAKEFILE
NAME		= IRC
#                      __    __    __    __
#                     /  \  /  \  /  \  /  \
#____________________/  __\/  __\/  __\/  __\_____________________________
#___________________/  /__/  /__/  /__/  /________________________________
#                   | / \   / \   / \   / \  \____
#                   |/   \_/   \_/   \_/   \    o \
#                                           \_____/--<--.   --..,_   _,.--.
#	COLORS
C_GREY		=	\e[1;30m
C_RED		=	\e[1;31m
C_GREEN		=	\e[1;32m
C_YELLOW	=	\e[1;33m
C_BLUE		=	\e[1;34m
C_PURPLE	=	\e[1;35m
C_CYAN		=	\e[1;36m
C_WHITE		=	\e[1;37m
C_END		=	\e[0m

#	CONSTANTS
CC			=	c++ -std=c++98 -g
FLAGS		=	-Wall -Wextra -Werror
SRCS		=	main.cpp
OBJS		=	$(SRCS:.cpp=.o)

# Quand make va essayer de cr´eer la cible, il va regarder la (les) d´ependance(s).
# En fait make consid`ere qu’on travaille avec des fichiers et que la cible et les
# d´ependances sont des noms de fichers. Pour d´eterminer si une cible ou une
# d´ependance est `a jour, il va regarder la date de modification du fichier portant
# le nom de la d´ependance ou de la cible.

# règle générique construire un .o (cible) à partir d'un .cpp appelée par défaut.
%.o: %.cpp
			$(CC) $(FLAGS) -o $@ -c $?
# $@ Le nom de la cible
# $? La liste des dépendances plus récentes que la cible

#	COMMANDS
all:	$(NAME)

$(NAME):	$(OBJS)
	@echo "$<\n[$(C_PURPLE)COMPILING$(C_END)]"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	@rm *.o 
	@echo "$<\n[$(C_GREEN)OK$(C_END)]"

clean:
	@echo "$<[$(C_YELLOW)CLEANING$(C_END)]"
	@rm -f *.o
	@echo "$<[$(C_GREEN)OK$(C_END)]"

fclean: clean
	@rm -f $(NAME)

re:	fclean all

# indique a Makefile les cibles qui ne sont pas des fichiers
.PHONY : all clean fclean re
