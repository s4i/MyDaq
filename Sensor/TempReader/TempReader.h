// -*- C++ -*-
/*!
 * @file
 * @brief
 * @date
 * @author
 *
 */

#ifndef TEMPREADER_H
#define TEMPREADER_H

#include "DaqComponentBase.h"
#include <daqmw/Sock.h>
////
#include <cstddef>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
////
using namespace RTC;

class TempReader
    : public DAQMW::DaqComponentBase
{
public:
    TempReader(RTC::Manager* manager);
    ~TempReader();

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

    int parse_params(::NVList* list);
    int set_data(size_t data_byte_size);
    int write_OutPort();

    /* file discriptor */
	int fd;
    //
    static const int EVENT_BYTE_SIZE  = 8;  // event byte size
    static const int SEND_BUFFER_SIZE = 50; //

    unsigned char s_data[SEND_BUFFER_SIZE];
    unsigned char m_data[SEND_BUFFER_SIZE];
    char mm_data[SEND_BUFFER_SIZE];
    size_t m_recv_byte_size;

    BufferStatus m_out_status;

    int m_srcPort;                        /// Port No. of data server
    std::string m_srcAddr;                /// IP addr. of data server
	
    const std::string MY_MODULE = "device_pi2";
	const std::string MY_FUNC1 = "ready";
	const std::string MY_FUNC2 = "w1";
	char *w1_dir = nullptr, *ret = nullptr;
    
    bool m_debug;
};

class ArgumentCatcher
	: TempReader
{
public:
	ArgumentCatcher();
	~ArgumentCatcher();
	int GetArgument(int *cnt = nullptr, char **vec = nullptr);
	int* ReturnArgCounter();
	char** ReturnArgVector();
private:
	int *arg_counter_ptr;
	char **arg_vector_ptr;	
};

int ArgumentCatcher::GetArgument(int *cnt, char **vec) {
	arg_counter_ptr = cnt;
	arg_vector_ptr = vec;
	return 0;
}

int* ArgumentCatcher::ReturnArgCounter() {
	return arg_counter_ptr;
}

char** ArgumentCatcher::ReturnArgVector() {
	return arg_vector_ptr;
}

extern "C"
{
    void TempReaderInit(RTC::Manager* manager);
};

#endif // TEMPREADER_H
