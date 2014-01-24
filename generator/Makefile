##
## Generator
##

CC=		g++

NAME=		mapGenerator

INCLUDES=	-I common/headers/\
		-I headers/

LIBS=		-lsfml-graphics -lsfml-window -lsfml-system

CPPFLAGS=	-W -O3 -Wall -Wextra -p -pedantic -ansi $(INCLUDES) $(LIBS) $(CFLAGS)

SRC=		common/src/main.cpp\
		common/src/errorWindow.cpp\
		common/src/intToString.cpp\
		common/src/isNum.cpp\
		src/Render.cpp\
		src/QuadTree.cpp\
		src/Except.cpp\
		src/Build.cpp\
		src/Object.cpp\
		src/Save.cpp\
		src/Gui.cpp

OBJ=		$(SRC:.cpp=.o)

CFLAGS +=	-W
CFLAGS +=	`pkg-config --cflags --libs gtk+-3.0`
CFLAGS +=	-Wall -ansi -pedantic -g -lpthread

RM=		rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

count:
		cat $(SRC) | wc -l