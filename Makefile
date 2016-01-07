##
## Makefile for sine_movement
##
## Made by chauvo_t
## Login   <chauvo_t@epitech.net>
##
## Started on  Mon Dec  7 14:34:37 2015 chauvo_t
## Last update Thu Jan  7 21:49:17 2016 chauvo_t
##

CXX		:= clang++ -std=c++11
RM		:= rm -f

SRC		:=	dxl_sdk_usb2ax/src/dxl_hal.c	\
			dxl_sdk_usb2ax/src/dynamixel.c	\
			src/DxlServo.cpp		\
			src/DxlException.cpp

OBJ		:= $(SRC:.cpp=.o)
OBJ		:= $(OBJ:.c=.o)

CXXFLAGS	:= -W -Wall -Wextra
CXXFLAGS	+= -I ./dxl_sdk_usb2ax/include

LDFLAGS		:= -ldxl -L dxl_sdk_usb2ax/lib

NAME		:= libdxlservo.a

all: $(NAME)

$(NAME):	$(OBJ)
	make -C dxl_sdk_usb2ax/src
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o:	%.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) -c

%.o:	%.c
	$(COMPILE.c) $< -o $@ $(CXXFLAGS) -c

clean:
	make clean -C dxl_sdk_usb2ax/src
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: clean all

.PHONY: all clean re install_deps
