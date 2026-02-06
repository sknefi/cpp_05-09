NAME = btc

CPP = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = \
	BitcoinExchange.cpp \
	main.cpp 

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CPP) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: FLAGS += -DDEBUG -g
debug: re

.PHONY: all clean fclean re debug