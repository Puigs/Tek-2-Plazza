NAME	= plazza

CC	= g++

RM	= rm -f

SRCS	= ./main.cpp \
	  ./src/Americana.cpp \
	  ./src/Client.cpp \
	  ./src/Error.cpp \
	  ./src/Fantasia.cpp \
	  ./src/Kitchen.cpp \
	  ./src/Margarita.cpp \
	  ./src/Param.cpp \
	  ./src/Parser.cpp \
	  ./src/Pizza.cpp \
	  ./src/PizzaFactory.cpp \
	  ./src/Process.cpp \
	  ./src/Regina.cpp \
	  ./src/Server-Master.cpp \
	  ./src/arg.cpp \
	  ./src/init.cpp \
	  ./src/loop.cpp \
	  ./src/utils.cpp \
	  ./src/Loop.cpp	\

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./include/pp
CPPFLAGS += -Wall -Wextra -lpthread -g3

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) -lpthread $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
