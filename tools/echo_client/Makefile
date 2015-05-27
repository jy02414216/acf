#################设计系统参数#######################################
WORKROOT    :=  ../../
CC  :=  gcc 
CXX :=  g++ 
CFLAGS  :=  -pipe -Wall -W -g 
CXXFLAGS    :=  -pipe -Wall -W -g 

DEP_INCPATH = -I$(WORKROOT)/src -I$(WORKROOT)/src/lib/wrapsock/output/include -I$(WORKROOT)/third-lib/libconfig/include
DEP_LDFLAGS = -L$(WORKROOT)/src/lib/wrapsock/output/lib -L$(WORKROOT)/third-lib/libconfig/lib
DEP_LDLIBS = -lwrapsock -lconfig -lpthread

CCFILE = echo_client.cpp
TARGET = echo_client

all : 	
	$(CXX) $(CCFILE) $(DEP_INCPATH) $(CFLAGS) $(DEP_LDFLAGS) $(DEP_LDLIBS) -o $(TARGET)
	$(_output)
clean : 
	$(_clean)

define _output
	mkdir -p output/bin output/conf
	cp $(TARGET) output/bin/
	cp -r conf/* output/conf/

endef

define _clean
	rm -rf *.o
	rm -rf $(TARGET)
	rm -rf output
endef
