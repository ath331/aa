CC=g++
CFLAGS= -D_REENTRANT -lpthread
OBJS=main.o server_class.o
TARGET=sv
 
all: $(TARGET)
	 
clean:
	    rm -f *.o
	        rm -f $(TARGET)
		 
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFALGS)




main.o: server_class.h main.cpp server_class.cpp
	g++ -c -o main.o
server_class.o: server_class.h server_class.cpp
	g++ -c -o server_class.o -D_REENTRANT -lpthread
