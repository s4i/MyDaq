COMP_NAME = SampleReader

all: $(COMP_NAME)Comp

#RFID_Calculation.o: RFID_Calculation.cpp RFID_Calculation.h
#	g++ -Wall -c RFID_Calculation.cpp
#RFID_Command.o: RFID_Command.cpp RFID_Command.h
#	g++ -Wall -c RFID_Command.cpp
#RFID_Connection.o: RFID_Connection.cpp RFID_Connection.h
#	g++ -Wall -c RFID_Connection.cpp

SRCS += $(COMP_NAME).cpp 
SRCS += $(COMP_NAME)Comp.cpp
SRCS += RFID_Calculation.cpp 
SRCS += RFID_Command.cpp 
SRCS += RFID_Connection.cpp
#SRCS += main.o

# Socket library
LDLIBS += -L$(DAQMW_LIB_DIR) -lSock

# sample install target
#
# MODE = 0755
# BINDIR = /home/daq/bin
#
# install: $(COMP_NAME)Comp
#	mkdir -p $(BINDIR)
#	install -m $(MODE) $(COMP_NAME)Comp $(BINDIR)

include /usr/share/daqmw/mk/comp.mk
