# The makefile is desinged for the testbe which is used to simulate the multiple tty terminals.
PROJECT=mixer_server_monitor
TARGET=msm

CC=gcc
AR=ar
ifdef REL
	CFLAGS=-O2 -std=gnu99
else
	CFLAGS=-g -Wall -std=gnu99 -DDEBUG
endif

INC_DIR_FLAGS=-I./include -I./include/SDL -I./include/mxml
LIB_OPTIONS=-L./lib  -lxml_draw  -lmxml -lpthread -lSDL_draw \
		-lmingw32 -lSDL_ttf -lSDLmain -lSDL \
		-lread_screen_info  -lwsock32

OBJS=msm_main.o network_manager.o threads_ui_manager.o \
	handle_errors.o queues_ui_manager.o


$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIB_OPTIONS)

$(OBJS):%.o:%.c
	$(CC) -c $(CFLAGS) $(INC_DIR_FLAGS) $< -o $@

.PHONY:clean
clean:
	-rm -frv $(TARGET) $(OBJS)

.PHONY:pp
pp:
	-find ./ -name "*" -print |egrep '\.cpp$$|\.c$$|\.h$$' |xargs astyle --style=linux -s -n;
