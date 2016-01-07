##
## Makefile for move_servo
##
## Made by chauvo_t
## Login   <chauvo_t@epitech.net>
##
## Started on  Mon Dec  7 14:34:37 2015 chauvo_t
## Last update Tue Jan  5 12:06:01 2016 chauvo_t
##

CXX		:= clang++
RM		:= rm -f

SRC		:= 	move_servo.cpp

OBJ		:= $(SRC:.cpp=.o)

CXXFLAGS	:= -I ../../src -I ../../dxl_sdk_usb2ax/include
CXXFLAGS	+= -W -Wall -Wextra

LDFLAGS		:= -ldxlservo -L ../../

NAME		:= move_servo

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o:	%.c
	$(CXX) $< -o $@ $(CXXFLAGS) -c

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

.PHONY: all clean fclean re
