PROGRAM_NAME = calculator
OBJ_PATH = ./obj/
SRCMODULES = calculator.c
OBJMODULES = $(addprefix $(OBJ_PATH), $(SRCMODULES:.c=.o))
CC = gcc 

ifeq ($(RELEASE), 1)
	#CFLAGS = -Wall -Werror -Wextra -ansi -pedantic -O3
	TCFLAGS = -Wall -Werror -Wextra -O3 -l readline
else
	#CFLAGS = -Wall -Werror -Wextra -ansi -pedantic -g -O0
	TCFLAGS = -Wall -Werror -Wextra -g -O0 -l readline
endif

ifeq ($(WINDOWS), 1)
	CFLAGS = $(TCFLAGS) -D FOR_WINDOWS
else ifeq ($(TESTING), 1)
	CFLAGS = $(TCFLAGS) -D FOR_TESTING
else
	CFLAGS = $(TCFLAGS)
endif

$(PROGRAM_NAME): main.c $(OBJMODULES)
	$(CC) $^ $(CFLAGS) -o $@

$(OBJ_PATH)%.o: %.c %.h
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_PATH)deps.mk: $(SRCMODULES)
	$(CC) -MM $^ > $@

.PHONY: clean
clean:
	rm -f $(OBJ_PATH)*.o $(PROGRAM_NAME) $(OBJ_PATH)deps.mk

ifneq (clean, $(MAKECMDGOALS))
-include $(OBJ_PATH)deps.mk
endif
