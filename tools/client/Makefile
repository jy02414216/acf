#################设计系统参数#######################################
WORKROOT    :=  ../
CC  :=  gcc 
CXX :=  g++ 
CFLAGS  :=  -pipe -Wall -W -g 
CXXFLAGS    :=  -pipe -Wall -W -g 

DEP_INCPATH = -I$(WORKROOT)/include
DEP_LDFLAGS = -L$(WORKROOT)/lib/wrapsock/output/lib
DEP_LDLIBS = -lwrapsock

CCFILE = client.c
TARGET = client

all : 	
	$(CC) $(CCFILE) $(DEP_INCPATH) $(CFLAGS) $(DEP_LDFLAGS) $(DEP_LDLIBS) -o $(TARGET)
	$(_output)
clean : 
	$(_clean)

define _output
    mkdir -p output
	mkdir -p output/bin
	cp -rf $(TARGET) output/bin
endef

define _clean
	rm -rf output
endef
