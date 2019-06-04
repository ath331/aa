CC=g++
CFLAGS=<컴파일 옵션>
LDFLAGS=<링크 옵션>
LDLIBS=<링크 라이브러리 목록>
OBJS=main.o server_class.o
TARGET=sv
 
all: $(TARGET)
	 
clean:
	    rm -f *.o
	        rm -f $(TARGET)
		 
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)


main.o: server_class.h server_class.cpp main.cpp
server_class.cpp : server_class.h server_class.cpp

