#################设计系统参数#######################################
WORKROOT    :=  ../../
CC  :=  gcc 
CXX :=  g++ 
CFLAGS  :=  -pipe -Wall -W -g -c 
CXXFLAGS    :=  -pipe -Wall -W -g -fPIC -shared

DEP_INCPATH = 
DEP_LDFLAGS = 
DEP_LDLIBS = 

CCFILE = wrapsock.c
OFILE = wrapsock.o
TARGET = libwrapsock.a
HEADERS = *.h

all : 	
	$(CC) $(CCFILE) $(DEP_INCPATH) $(CFLAGS) $(DEP_LDFLAGS) $(DEP_LDLIBS) 
	ar -r $(TARGET) $(OFILE) 
	$(_output)
clean : 
	$(_clean)

define _output
    mkdir -p output
	mkdir -p output/lib
	mkdir -p output/include
	cp -rf $(TARGET) output/lib
	cp -rf $(HEADERS) output/include
	rm -rf $(TARGET)
endef

define _clean
	rm -rf $(OFILE)
	rm -rf output
endef
