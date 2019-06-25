TARGET=sv
CC=g++
OP=-D REENTRANT -lpthread
MDIR=../
HDPATH=$(MDIR)header/
OBJECT=main.o server_class.o client_class.o
VPATH=$(MDIR):$(HDPATH)

CPP=main.cpp server_class.cpp client_class.cpp
HD=server_class.h client_class.h

$(TARGET):$(OBJECT)
	$(CC) -o $@ $(OBJECT) $(OP)
	mv $(TARGET) ../

main.o:$(CPP) $(HD)
server_class.o:$(MDIR)server_class.cpp $(HDPATH)server_class.h
client_class.o:client_class.cpp client_class.h


clean:
	rm -f *.o
	rm -f ../$(TARGET)
