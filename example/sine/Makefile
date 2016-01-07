##
## Makefile for sine_movement
##
## Made by chauvo_t
## Login   <chauvo_t@epitech.net>
##
## Started on  Mon Dec  7 14:34:37 2015 chauvo_t
## Last update Tue Jan  5 12:05:33 2016 chauvo_t
##

CXX		:= clang++ -std=c++11
RM		:= rm -f

SRC		:= 	sine.cpp				\
			../utils/Timer/TimerException.cpp	\
			../utils/Timer/UTimer.cpp		\
			../utils/Timer/WTimer.cpp

OBJ		:= $(SRC:.cpp=.o)

CXXFLAGS	:= -I ../../dxl_sdk_usb2ax/include -I ../../src -I ../utils/Timer/.
CXXFLAGS	+= -W -Wall -Wextra

LDFLAGS		:= -ldxlservo -L ../../

NAME		:= sine

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o:	%.c
	$(CXX) $< -o $@ $(CXXFLAGS) -c

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: clean all

.PHONY: all clean re install_deps
