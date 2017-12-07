COMP_NAME = TempReader

all: $(COMP_NAME)Comp

SRCS += $(COMP_NAME).cpp
SRCS += $(COMP_NAME)Comp.cpp

# Socket library
LDLIBS += -L$(DAQMW_LIB_DIR) -lSock -I/usr/local/include -L/usr/local/lib \
			-I/usr/include/python2.7 -L/usr/lib/python2.7/config -lpython2.7
CXXFLAGS += -I/usr/include/python2.7 -L/usr/lib/python2.7/config -lpython2.7

# sample install target
#
# MODE = 0755
# BINDIR = /home/daq/bin
#
# install: $(COMP_NAME)Comp
#	mkdir -p $(BINDIR)
#	install -m $(MODE) $(COMP_NAME)Comp $(BINDIR)

include /usr/share/daqmw/mk/comp.mk
