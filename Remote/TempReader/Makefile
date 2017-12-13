COMP_NAME = TempReader

all: $(COMP_NAME)Comp

SRCS += $(COMP_NAME).cpp
SRCS += $(COMP_NAME)Comp.cpp

# Socket library
LDLIBS += -L$(DAQMW_LIB_DIR) -lSock -I/usr/local/include -L/usr/local/lib -g \
			-I/usr/include/python3.4m -L/usr/lib/python3.5/config -lpython3.4m
CXXFLAGS += -I/usr/include/python3.4m -L/usr/lib/python3.5/config -lpython3.4m

# sample install target
#
# MODE = 0755
# BINDIR = /home/daq/bin
#
# install: $(COMP_NAME)Comp
#	mkdir -p $(BINDIR)
#	install -m $(MODE) $(COMP_NAME)Comp $(BINDIR)

include /usr/share/daqmw/mk/comp.mk

clean:
	@rm -f $(wildcard *.o) $(COMP_NAME)Comp.o $(COMP_NAME)Comp
	@rm -f *Skel.h *Skel.cpp
	@rm -f *Stub.h *Stub.cpp
	@rm -f *~
	@rm -f DAQService.hh DAQServiceDynSK.cc DAQServiceSK.cc
	@rm -f DAQService.idl
	@rm -f symlink
	@rm -fr $(AUTO_GEN_DIR) .depend
	@rm -fr __pycache__
