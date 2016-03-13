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

SRC		:= 	sine.cpp				\
			../utils/Timer/TimerException.cpp	\
			../utils/Timer/UTimer.cpp		\
			../utils/Timer/WTimer.cpp

OBJ		:= $(SRC:.cpp=.o)

CXXFLAGS	:= -I ../../dxl_sdk_usb2ax/include -I ../../src -I ../utils/Timer/.
CXXFLAGS	+= -W -Wall -Wextra

LDFLAGS		:= -ldxlservo -L ../../
LDFLAGS		+= -lboost_iostreams -lboost_system

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

install_deps:
	sudo apt-get install gnuplot libgnuplot-iostream-dev gnuplot-x11

.PHONY: all clean re install_deps
