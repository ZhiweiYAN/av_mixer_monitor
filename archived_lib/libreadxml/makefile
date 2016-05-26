#WIN32=1
#MinGW platform
#ifdef WIN32
# read_screen_info.dll:read_screen_info.c
# gcc -shared -O2 -I./include/ -o read_screen_info.dll read_screen_info.c -Wl,-output-def,read_screen_info.def,--out-implib,libread_screen_info.a -L./lib/ -lmxml -lpthread
#endif
#Linux platform
#LINUX=1
#ifdef LINUX
#read_screen_info.dll:read_screen_info.c
#	gcc -shared -fPIC -I./include/ -o libread_screen_info.so read_screen_info.c -L./lib/ -lmxml -lpthread
#endif
CC = gcc
AR = ar

CFLAGS = -O2 -Wall -std=gnu99
INCL = -I./include 
#MinGW platform
READ_LIB = libread_screen_info.a
READ_OBJS =  read_screen_info.o 

$(READ_LIB):$(READ_OBJS)
	$(AR) cq $@ $(READ_OBJS)

$(READ_OBJS):%.o:%.c
	$(CC) -c $(CFLAGS) $(INCL) $< -o $@

.PHONY:clean
clean:
	rm -frv $(READ_LIB) $(READ_OBJS) 

	
