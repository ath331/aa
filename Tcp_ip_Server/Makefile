TARGET=sv
CC=g++
OP=-D REETRANT -lpthread
OBJECT=main.o server_class.o

$(TARGET):$(OBJECT)
	$(CC) -o $@ $(OBJECT) $(OP)

main.o:main.cpp server_class.h server_class.cpp
server_class.o:server_class.cpp server_class.h



clean:
	rm -f *.o
	rm -f $(TARGET)
