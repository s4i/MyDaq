// -*- C++ -*-
/*!
 * @file
 * @brief
 * @date
 * @author
 *
 */

#include "AccelReader.h"

using DAQMW::FatalType::DATAPATH_DISCONNECTED;
using DAQMW::FatalType::OUTPORT_ERROR;
using DAQMW::FatalType::USER_DEFINED_ERROR1;
using DAQMW::FatalType::USER_DEFINED_ERROR2;

// Module specification
// Change following items to suit your component's spec.
static const char* accelreader_spec[] =
{
    "implementation_id", "AccelReader",
    "type_name",         "AccelReader",
    "description",       "AccelReader component",
    "version",           "1.0",
    "vendor",            "Kazuo Nakayoshi, KEK",
    "category",          "example",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
};

AccelReader::AccelReader(RTC::Manager* manager)
    : DAQMW::DaqComponentBase(manager),
      m_OutPort("accelreader_out", m_out_data),
      m_recv_byte_size(0),
      m_out_status(BUF_SUCCESS),

      m_debug(false)
{
    // Set OutPort buffers
    registerOutPort("accelreader_out", m_OutPort);
    init_command_port();
    init_state_table();
    set_comp_name("ACCELREADER");
}

AccelReader::~AccelReader()
{
}

RTC::ReturnCode_t AccelReader::onInitialize()
{
    if (m_debug) {
        std::cerr << "AccelReader::onInitialize()" << std::endl;
    }
    return RTC::RTC_OK;
}

RTC::ReturnCode_t AccelReader::onExecute(RTC::UniqueId ec_id)
{
    daq_do();

    return RTC::RTC_OK;
}

int AccelReader::daq_dummy(){ return 0; }

int AccelReader::daq_configure()
{
    std::cerr << "*** AccelReader::configure" << std::endl;

    return 0;
}

int AccelReader::parse_params(::NVList* list){ return 0; }

int AccelReader::daq_unconfigure()
{
    std::cerr << "*** AccelReader::unconfigure" << std::endl;

    return 0;
}

int AccelReader::daq_start()
{
    std::cerr << "*** AccelReader::start" << std::endl;

    m_out_status = BUF_SUCCESS;

    try {
        /* シリアルポートオープン */
        if((fd = serialOpen("/dev/ttyACM0", 9600)) < 0){
            printf("can not open serialport");
        } // 次はsetdataに進む

    } catch (int e) {
        std::cerr << "Sock Fatal Error : File descriptor" << std::endl;
        fatal_error_report(USER_DEFINED_ERROR1, "Serial port open failed");
    } catch (...) {
        std::cerr << "Sock Fatal Error : Unknown" << std::endl;
        fatal_error_report(USER_DEFINED_ERROR1, "Unknown error");
    }

    // Check data port connections
    bool outport_conn = check_dataPort_connections( m_OutPort );
    if (!outport_conn) {
        std::cerr << "### NO Connection" << std::endl;
        fatal_error_report(DATAPATH_DISCONNECTED);
    }

    return 0;
}

int AccelReader::daq_stop()
{
	///
	close(fd);
	///

    std::cerr << "*** AccelReader::stop" << std::endl;

    // if (m_sock) {
    //     m_sock->disconnect();
    //     delete m_sock;
    //     m_sock = 0;
    // }

    return 0;
}

int AccelReader::daq_pause()
{
    std::cerr << "*** AccelReader::pause" << std::endl;

    return 0;
}

int AccelReader::daq_resume()
{
    std::cerr << "*** AccelReader::resume" << std::endl;

    return 0;
}

int AccelReader::set_data(size_t data_byte_size)
{
    unsigned char header[8];
    unsigned char footer[8];

    set_header(&header[0], data_byte_size);
    set_footer(&footer[0]);

    ///set OutPort buffer length
    m_out_data.data.length(data_byte_size + HEADER_BYTE_SIZE + FOOTER_BYTE_SIZE);
    memcpy(&(m_out_data.data[0]), &header[0], HEADER_BYTE_SIZE);
    memcpy(&(m_out_data.data[HEADER_BYTE_SIZE]), &m_data[0], data_byte_size);
    memcpy(&(m_out_data.data[HEADER_BYTE_SIZE + data_byte_size]), &footer[0], FOOTER_BYTE_SIZE);

    return 0;
}

int AccelReader::write_OutPort()
{
    ////////////////// send data from OutPort  //////////////////
    bool ret = m_OutPort.write();

    //////////////////// check write status /////////////////////
    if (ret == false) {  // TIMEOUT or FATAL
        m_out_status  = check_outPort_status(m_OutPort);
        if (m_out_status == BUF_FATAL) {   // Fatal error
            fatal_error_report(OUTPORT_ERROR);
        }
        if (m_out_status == BUF_TIMEOUT) { // Timeout
            return -1;
        }
    }
    else {
        m_out_status = BUF_SUCCESS; // successfully done
    }

    return 0;
}

int AccelReader::daq_run()
{
    if (m_debug) {
        std::cerr << "*** AccelReader::run" << std::endl;
    }

    if (check_trans_lock()) {  // check if stop command has come
        set_trans_unlock();    // transit to CONFIGURED state
        return 0;
    }

    if (m_out_status == BUF_SUCCESS) {
		// 受信処理  velocity
		while(serialDataAvail(fd)){
			memset(m_data, 0, SEND_BUFFER_SIZE);
			for(int i = 0; i < SEND_BUFFER_SIZE; i++){
				m_data[i] = serialGetchar(fd);
				if(m_data[i] == '\n') {
					m_data[i] = '\0'; //x:111y:111z:111\n
					break;
				}
			}
		}
		delay(50);


		sprintf(m_data, "%s", m_data);
		//std::cerr << m_data << std::endl;
		m_recv_byte_size = sizeof(m_data);
		set_data(m_recv_byte_size); // set data to OutPort Buffer
    }

    if (write_OutPort() < 0) {
        ;     // Timeout. do nothing.
    }
    else {    // OutPort write successfully done
        inc_sequence_num();                     // increase sequence num.
        inc_total_data_size(m_recv_byte_size);  // increase total data byte size
    }
    return 0;
}


extern "C"
{
    void AccelReaderInit(RTC::Manager* manager)
    {
        RTC::Properties profile(accelreader_spec);
        manager->registerFactory(profile,
                    RTC::Create<AccelReader>,
                    RTC::Delete<AccelReader>);
    }
};
