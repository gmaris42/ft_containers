# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 15:16:37 by gmaris            #+#    #+#              #
#    Updated: 2022/01/19 17:18:09 by gmaris           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tester

CC = clang++
FLAGS = -Wall -Wextra -Werror -std=c++98 -g #-fsanitize=address

SRCS_DIR = ./

SRC 		=	test.cpp

INC			=	Stack.hpp\
				Map.hpp\
				Vector.hpp

OBJS_DIR 	= 	./obj/
OBJ 		= 	$(SRC:.cpp=.o)
OBJS 		= 	$(addprefix $(OBJS_DIR), $(OBJ))

TEST 		= 	stack_test.hpp

# TEST_DIR	= 	./test/
# TESTS 		= 	$(addprefix $(TEST_DIR), $(TEST))

INC_DIR		= 	./includes/
INCS		= 	$(addprefix $(INC_DIR), $(INC))
INC_FLAG 	= 	-I$(INC_DIR) -I$(TEST_DIR)

SRCS 		= 	$(addprefix $(SRCS_DIR), $(SRC))


YELLOW = \033[033m
GREEN = \033[032m
BLUE = \033[36m
RED = \033[031m
PURPLE = \033[35m
RESET = \033[0m

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.cpp $(INCS) $(TESTS)
	@mkdir -p $(OBJS_DIR)
	@echo "$(YELLOW)$(notdir $(basename $@))...$(RESET)"
	@$(CC) $(INC_FLAG) $(FLAGS) -c $< -o $@
	@echo "\t\t[$(GREEN)OK$(RESET)]"

$(NAME): $(OBJS) Makefile $(INCS) $(TESTS)
	@$(CC) $(INC_FLAG) $(FLAGS) -o $(NAME) $(OBJS)
	@echo "[$(GREEN)$(NAME) compiled$(RESET)]"

all: $(NAME)

clean:
	@echo "Cleaning: $(OBJS_DIR)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Cleaning: $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: fclean clean re all
