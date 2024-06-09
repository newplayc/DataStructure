CC= gcc 
#CC= arm-none-linux-gnueabi-gcc
EXTRA_LIBS += -lpthread
EXEC = pthread 
OBJS = pthread.o 
CFLAGS += 
LDFLAGS+= –static
 
all: $(EXEC) 
$(EXEC): $(OBJS) 
	$(CC) -o $@ $(OBJS) $(EXTRA_LIBS) 

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o
