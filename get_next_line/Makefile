SIZE:=10

BUFFER:=-D BUFFER_SIZE=$(SIZE)

MANDATORY := get_next_line.c \
get_next_line.h\
get_next_line_utils.c\

BONUS := get_next_line_bonus.c \
get_next_line_bonus.h\
get_next_line_utils_bonus.c\

m:
	cc $(MANDATORY) $(BUFFER) test.c

b:
	cc $(BONUS) $(BUFFER) test.c

clean:
	@rm a.out
