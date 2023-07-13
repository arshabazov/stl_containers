NAME	=	ft_containers

HEADER	=	src/vector.hpp\
			src/utils/iterator_traits.hpp\
			src/utils/random_access_iterator.hpp\
			src/utils/reverse_iterator.hpp

SRCS	=	main.cpp\

OBJS	=	$(SRCS:%.cpp=%.o)

CC		=	clang++
FLAGS1	=	-Wall -Wextra -Werror -Wshadow -Wno-shadow -std=c++98

.PHONY	:	all clear fclear re

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(FLAGS1) $(OBJS) -o $(NAME)

%.o		:	%.cpp $(HEADER)
			$(CC) $(FLAGS1) $(FLAGS2)  -c $< -o $@

clean	:
		@$(RM) $(OBJS)

fclean	:	clean
		@$(RM) $(NAME)

re		:	fclean all