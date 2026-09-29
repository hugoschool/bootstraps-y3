CXX	?=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20

SRC	:=	$(shell find . -iname "*.cpp" -type f)
OBJ	:=	$(SRC:.cpp=.o)

BINARY	:=	bsr-type

.PHONY: all
all:	$(BINARY)

$(BINARY):	$(OBJ)
	$(CXX) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean:	clean
	$(RM) $(BINARY)

.PHONY: re
re:	fclean all
