// -*- C++ -*-
/*!
 * @file
 * @brief
 * @date
 * @author
 *
 */

#include "SampleReader.h"

using DAQMW::FatalType::DATAPATH_DISCONNECTED;
using DAQMW::FatalType::OUTPORT_ERROR;
using DAQMW::FatalType::USER_DEFINED_ERROR1;
using DAQMW::FatalType::USER_DEFINED_ERROR2;
using namespace std;

// Module specification
// Change following items to suit your component's spec.
static const char* samplereader_spec[] =
{
    "implementation_id", "SampleReader",
    "type_name",         "SampleReader",
    "description",       "SampleReader component",
    "version",           "1.0",
    "vendor",            "Kazuo Nakayoshi, KEK",
    "category",          "example",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
};

SampleReader::SampleReader(RTC::Manager* manager)
    : DAQMW::DaqComponentBase(manager),
      m_OutPort("samplereader_out", m_out_data),
      m_sock(0),
      m_recv_byte_size(0),
      m_out_status(BUF_SUCCESS),
      
      m_debug(false),
      sock(0),
      autoflag(false)
{
    // Registration: InPort/OutPort/Service

    // Set OutPort buffers
    registerOutPort("samplereader_out", m_OutPort);

    init_command_port();
    init_state_table();
    set_comp_name("SAMPLEREADER");
}

SampleReader::~SampleReader()
{
}

RTC::ReturnCode_t SampleReader::onInitialize()
{
    if (m_debug) {
        std::cerr << "SampleReader::onInitialize()" << std::endl;
    }

    return RTC::RTC_OK;
}

RTC::ReturnCode_t SampleReader::onExecute(RTC::UniqueId ec_id)
{
    daq_do();

    return RTC::RTC_OK;
}

int SampleReader::daq_dummy()
{
    return 0;
}

int SampleReader::daq_configure()
{
    std::cerr << "*** SampleReader::configure" << std::endl;
    
    char hostname[] = "192.168.200.220";
	
	//RFID
    memset(buf,'\0',sizeof(buf));
    memset(rebuf,'\0',sizeof(rebuf));
    memset(inbuf,'\0',sizeof(inbuf));

    //接続を確率

    sock = con.CreateSocket(hostname);

    bb.Initialize(sock);
    //bb.SetConfig(sock);

    //bb.GetConfig(sock);


    //FD_SET(0m&read_set);
    FD_ZERO(&read_set);
	//RFID

    ::NVList* paramList;
    paramList = m_daq_service0.getCompParams();
    parse_params(paramList);

    return 0;
}

int SampleReader::parse_params(::NVList* list)
{
    return 0;
}

int SampleReader::daq_unconfigure()
{
    std::cerr << "*** SampleReader::unconfigure" << std::endl;

    return 0;
}

int SampleReader::daq_start()
{
    std::cerr << "*** SampleReader::start" << std::endl;
  
    m_out_status = BUF_SUCCESS;

    // Check data port connections
    bool outport_conn = check_dataPort_connections( m_OutPort );
    if (!outport_conn) {
        std::cerr << "### NO Connection" << std::endl;
        fatal_error_report(DATAPATH_DISCONNECTED);
    }

    return 0;
}

int SampleReader::daq_stop()
{
    std::cerr << "*** SampleReader::stop" << std::endl;

    if (m_sock) {
        m_sock->disconnect();
        delete m_sock;
        m_sock = 0;
    }

    return 0;
}

int SampleReader::daq_pause()
{
    std::cerr << "*** SampleReader::pause" << std::endl;

    return 0;
}

int SampleReader::daq_resume()
{
    std::cerr << "*** SampleReader::resume" << std::endl;

    return 0;
}

int SampleReader::read_data_from_detectors()
{
    int received_data_size = 0;

    received_data_size = SEND_BUFFER_SIZE;

    return received_data_size;
}

int SampleReader::set_data(unsigned int data_byte_size)
{
    unsigned char header[8];
    unsigned char footer[8];

    set_header(&header[0], data_byte_size);
    set_footer(&footer[0]);
    
    i++;
    //sprintf(mm_data,"%s", data);
    ///set OutPort buffer length
    m_out_data.data.length(data_byte_size + HEADER_BYTE_SIZE + FOOTER_BYTE_SIZE);
    memcpy(&(m_out_data.data[0]), &header[0], HEADER_BYTE_SIZE);
    memcpy(&(m_out_data.data[HEADER_BYTE_SIZE]), &mm_data[0], data_byte_size);
    memcpy(&(m_out_data.data[HEADER_BYTE_SIZE + data_byte_size]), &footer[0],
           FOOTER_BYTE_SIZE);
    return 0;
}

int SampleReader::write_OutPort()
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

unsigned char SampleReader::SREAD(unsigned char *sbuf){

  RFID_Calculation Bcc;

  sbuf[0] = 0x10;
  sbuf[1] = 0x02;//STX
  sbuf[2] = 0x53;//Command Class
  sbuf[3] = 0x4F;//Command Code
  sbuf[4] = 0x0E;//Send Sequence
  sbuf[5] = 0x03;//Data length High
  sbuf[6] = 0x00;//Head Write Block
  sbuf[7] = 0x03;//Function Code
  sbuf[8] = 0x01;//Head Write Block
  sbuf[9] = 0x01;//Write Block Count
  sbuf[10] = 0x10;//Head Read Block
  sbuf[11] = 0x03;//Read Block Count

  //bcc calculation
  sbuf[12] = Bcc.Calculation(sbuf,12);

  return *sbuf;
}

unsigned char SampleReader::STOP(unsigned char *sbuf){

  RFID_Calculation Bcc;

  sbuf[0] = 0x10;
  sbuf[1] = 0x02;
  sbuf[2] = 0x69;
  sbuf[3] = 0x6F;
  sbuf[4] = 0x0F;
  sbuf[5] = 0x00;
  sbuf[6] = 0x00;
  sbuf[7] = 0x10;
  sbuf[8] = 0x03;
  sbuf[9] = Bcc.Calculation(sbuf,9);

  //bcc calculation

  return *sbuf;
}

int SampleReader::daq_run()
{
	if (m_debug) {
        std::cerr << "*** SampleReader::run" << std::endl;
    }

    if (check_trans_lock()) {  // check if stop command has come
        set_trans_unlock();    // transit to CONFIGURED state
        return 0;
    }
	//RFID
	//autoコマンドをbufに読み込み
   //com.SREAD(buf);
   SREAD(buf);
   //ブザーを設定
   bb.BuzzerOn(sock);
   //autoコマンド送信
   send(sock,buf,sizeof(buf),0);
   recv(sock,rebuf,sizeof(rebuf),0);

   memset(buf,'\0',sizeof(buf));
   memset(rebuf,'\0',sizeof(rebuf));

   if(autoflag==false){
	   //db.RWStart(hostname);
      // cout << hostname << ":Auto mode start Complete!!" << endl;
      autoflag = true;
   }

   FD_SET(sock,&read_set);

    //再起動
   data = bb.INVENTORY(sock);
   sprintf(mm_data,"%s", data);
   std::cerr << mm_data << std::endl;

   //com.STOP(buf);
   STOP(buf);
   send(sock,buf,sizeof(buf),0);
   recv(sock,rebuf,sizeof(rebuf),0);
   memset(buf,'\0',sizeof(buf));
   memset(rebuf,'\0',sizeof(rebuf));
 	//RFID

    if (m_out_status == BUF_SUCCESS) {   // previous OutPort.write() successfully done
        int ret = read_data_from_detectors();
        if (ret > 0) {
            m_recv_byte_size = ret;
            set_data(m_recv_byte_size); // set data to OutPort Buffer
        }
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
    void SampleReaderInit(RTC::Manager* manager)
    {
        RTC::Properties profile(samplereader_spec);
        manager->registerFactory(profile,
                    RTC::Create<SampleReader>,
                    RTC::Delete<SampleReader>);
    }
};
