TARGET=sv
CC=g++
OP=-D REETRANT -lpthread
OJPATH=objectfile/
HDPATH=header/
OBJECT=$(OJPATH)(main.o server_class.o)

$(TARGET):$(OJPATH)$(OBJECT)
	$(CC) -o $(OJPATH)$@ $(OJPATH)$(OBJECT) $(OP)

$(OJPATH)main.o:main.cpp $(HDPATH)server_class.h server_class.cpp
$(OJPATH)server_class.o:server_class.cpp $(HDPATH)server_class.h



clean:
	rm -f *.o
	rm -f $(TARGET)
