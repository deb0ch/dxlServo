#
# Copyright (c) 2016 Thomas Chauvot de Beauchene
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

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

.PHONY: all clean re
