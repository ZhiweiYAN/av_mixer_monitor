CC = gcc
AR = ar

CFLAGS = -O2 -Wall -std=gnu99
INCL = -I./include -I./include/SDL -I./include/mxml
#MinGW platform
DRAW_LIB = libxml_draw.a
DRAW_OBJS =  draw_screen.o \
	draw_line.o \
	draw_rectangle.o \
	draw_ellipse.o \
	draw_text.o \
	draw_image.o \
	display_picture.o \
	init_display.o \
	read_screen_info.o 

$(DRAW_LIB):$(DRAW_OBJS)
	$(AR) cq $@ $(DRAW_OBJS)

$(DRAW_OBJS):%.o:%.c
	$(CC) -c $(CFLAGS) $(INCL) $< -o $@

.PHONY:clean
clean:
	rm -frv $(DRAW_LIB) $(DRAW_OBJS)
