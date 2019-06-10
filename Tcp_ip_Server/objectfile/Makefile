TARGET=sv
CC=g++
OP=-D REETRANT -lpthread
MDIR=../
HDPATH=$(MDIR)header/
OBJECT=main.o server_class.o
VPATH=$(MDIR):$(HDPATH)

$(TARGET):$(OBJECT)
	$(CC) -o $@ $(OBJECT) $(OP)
	mv $(TARGET) ../

main.o:$(MDIR)main.cpp $(HDPATH)server_class.h $(MDIR)server_class.cpp
server_class.o:$(MDIR)server_class.cpp $(HDPATH)server_class.h



clean:
	rm -f *.o
	rm -f $(TARGET)
