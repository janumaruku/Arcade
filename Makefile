##
## EPITECH PROJECT, 2025
## new_workspace_creator
## File description:
## Makefile
##

NAME		=	arcade

include mk/config.mk
include mk/sources.mk

OBJ		=	$(SRC:%.cpp=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CXXFLAGS += -g3 -DDEBUG
debug: re

tests_run:
	@echo "No test Makefile target configured yet."

run: $(NAME)
	@./$(NAME) $(ARGS)

.PHONY: all clean fclean re debug tests_run run
