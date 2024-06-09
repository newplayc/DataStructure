CC= gcc 
EXEC = hello 
OBJS = hello.o 
CFLAGS += 
LDFLAGS+= –static
 
all: $(EXEC) 
$(EXEC): $(OBJS) 
	$(CC) -o $@ $(OBJS) 

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o
