// -*- C++ -*-
/*!
 * @file 
 * @brief
 * @date
 * @author
 *
 */

#ifndef SAMPLEREADER_H
#define SAMPLEREADER_H

#include "DaqComponentBase.h"
#include <daqmw/Sock.h>

#include <time.h>

//RFID S
#include <iostream>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include "RFID_Connection.h"
#include "AutoAndStop.h"
#include "RFID_Calculation.h"
#include "RFID_Command.h"
//RFID E

using namespace RTC;

class SampleReader
    : public DAQMW::DaqComponentBase, 
      public RFID_Connection::RFID_Connection,
      public RFID_Calculation::RFID_Calculation,
      public RFID_Command::RFID_Command
{
public:
    SampleReader(RTC::Manager* manager);
    ~SampleReader();
    
    
    // The initialize action (on CREATED->ALIVE transition)
    // former rtc_init_entry()
    virtual RTC::ReturnCode_t onInitialize();

    // The execution action that is invoked periodically
    // former rtc_active_do()
    virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

private:
    TimedOctetSeq          m_out_data;
    OutPort<TimedOctetSeq> m_OutPort;

private:
    int daq_dummy();
    int daq_configure();
    int daq_unconfigure();
    int daq_start();
    int daq_run();
    int daq_stop();
    int daq_pause();
    int daq_resume();
    int i;
    char* data;
	
    int parse_params(::NVList* list);
    int read_data_from_detectors();
    int set_data(unsigned int data_byte_size);
    int write_OutPort();

    DAQMW::Sock* m_sock;               /// socket for data server
    
    RFID_Connection con;
    //AccessDataBase db;
    //AutoAndStop com;
    RFID_Command bb;
    fd_set read_set;

    static const int EVENT_BYTE_SIZE  = 8;    // event byte size
    static const int SEND_BUFFER_SIZE = 1024; //
    unsigned char m_data[SEND_BUFFER_SIZE];
    char mm_data[SEND_BUFFER_SIZE];
    unsigned int  m_recv_byte_size;

    BufferStatus m_out_status;

    int m_srcPort;                        /// Port No. of data server
    std::string m_srcAddr;                /// IP addr. of data server

    bool m_debug;
    
	int sock;
	bool autoflag;
	unsigned char buf[30], rebuf[30], inbuf[30];
	unsigned char SREAD(unsigned char *sbuf);
	unsigned char STOP(unsigned char *sbuf);
};


extern "C"
{
    void SampleReaderInit(RTC::Manager* manager);
};

#endif // SAMPLEREADER_H
