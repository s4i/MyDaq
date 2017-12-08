// -*- C++ -*-
/*!
 * @file
 * @brief
 * @date
 * @author
 *
 */

#include "TempReader.h"

using DAQMW::FatalType::DATAPATH_DISCONNECTED;
using DAQMW::FatalType::OUTPORT_ERROR;
using DAQMW::FatalType::USER_DEFINED_ERROR1;
using DAQMW::FatalType::USER_DEFINED_ERROR2;

const char MY_MODULE[] = "device";
const char MY_FUNC1[] = "ready";
const char MY_FUNC2[] = "w1";

// Module specification
// Change following items to suit your component's spec.
static const char* tempreader_spec[] =
{
    "implementation_id", "TempReader",
    "type_name",         "TempReader",
    "description",       "TempReader component",
    "version",           "1.0",
    "vendor",            "Kazuo Nakayoshi, KEK",
    "category",          "example",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
};

TempReader::TempReader(RTC::Manager* manager)
    : DAQMW::DaqComponentBase(manager),
      m_OutPort("tempreader_out", m_out_data),
      m_recv_byte_size(0),
      m_out_status(BUF_SUCCESS),

      m_debug(false)
{
    // Set OutPort buffers
    registerOutPort("tempreader_out", m_OutPort);
    init_command_port();
    init_state_table();
    set_comp_name("TEMPREADER");
}

TempReader::~TempReader()
{
}

RTC::ReturnCode_t TempReader::onInitialize()
{
    if (m_debug) {
        std::cerr << "TempReader::onInitialize()" << std::endl;
    }
    return RTC::RTC_OK;
}

RTC::ReturnCode_t TempReader::onExecute(RTC::UniqueId ec_id)
{
    daq_do();

    return RTC::RTC_OK;
}

int TempReader::daq_dummy(){ return 0; }

int TempReader::daq_configure()
{
    std::cerr << "*** TempReader::configure" << std::endl;
    
    if (pModule == nullptr) {
		Py_Initialize();
		PyObject* sysPath = PySys_GetObject("path");
		PyObject* dir = PyUnicode_DecodeFSDefault("*");
		PyList_Append(sysPath, dir); 
		/****************************************************************/
		
		pName = PyUnicode_DecodeFSDefault(MY_MODULE);
		pModule = PyImport_Import(pName);
		Py_DECREF(pName);
		if (pModule != nullptr) {
			// Func1
			pFunc = PyObject_GetAttrString(pModule, MY_FUNC1);
			if (pFunc && PyCallable_Check(pFunc)) {
				pValue = PyObject_CallObject(pFunc, NULL);
				if (pValue != NULL) {
				// def 実行
				pValue = PyObject_CallObject(pFunc, nullptr);
					if (pValue != nullptr) {
						//w1_dir = PyString_AsString(pValue); // Python2.7
						
						/*** Python 3.5 */
						w1_dir = PyUnicode_AsUTF8(pValue);
						Py_DECREF(pValue);
					}
					else {
						Py_DECREF(pFunc);
						Py_DECREF(pModule);
						PyErr_Print();
						std::cerr << "Call failed" << std::endl;
						return 1;
					}
				}
			}
			else {
				if (PyErr_Occurred())
					PyErr_Print();
				std::cerr << "Cannot find function: " << MY_FUNC1 << std::endl;
				return 1;
			}
			//w1_slave dir path
			std::cerr << w1_dir << std::endl;
		}
		else {
			PyErr_Print();
			std::cerr << "Failed to load: " << MY_MODULE << std::endl;
			return 1;
		}
	}

    return 0;
}

int TempReader::parse_params(::NVList* list){ return 0; }

int TempReader::daq_unconfigure()
{
    std::cerr << "*** TempReader::unconfigure" << std::endl;

    return 0;
}

int TempReader::daq_start()
{
    std::cerr << "*** TempReader::start" << std::endl;

    m_out_status = BUF_SUCCESS;
	
	if (w1_dir != nullptr) {
		// Func2
		pFunc2 = PyObject_GetAttrString(pModule, MY_FUNC2);
		if (pFunc2 && PyCallable_Check(pFunc2)) {
			pArgs = PyTuple_New(1); // 引数は1
			
			//PyTuple_SetItem(pArgs, 0, PyString_FromString(w1_dir)); // Python2.7
			
			pValue2 = PyUnicode_FromString(w1_dir);
			//if (!pValue2) {
				//Py_DECREF(pArgs);
				//Py_DECREF(pModule);
				//std::cerr << "Cannot convert argument" << std::endl;
				//return 1;
			//}
			PyTuple_SetItem(pArgs, 0, pValue2); 
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
			std::cerr << "Cannot find function " << MY_FUNC2 << std::endl;
			return 1;
		}
	}
	
    // Check data port connections
    bool outport_conn = check_dataPort_connections( m_OutPort );
    if (!outport_conn) {
        std::cerr << "### NO Connection" << std::endl;
        fatal_error_report(DATAPATH_DISCONNECTED);
    }

    return 0;
}

int TempReader::daq_stop()
{
	Py_DECREF(pValue2);
	Py_DECREF(pArgs); 
	Py_DECREF(pFunc);
    Py_XDECREF(pFunc2);
    Py_DECREF(pModule);
    Py_Finalize(); // python 終了
    
    std::cerr << "*** TempReader::stop" << std::endl;

    return 0;
}

int TempReader::daq_pause()
{
    std::cerr << "*** TempReader::pause" << std::endl;

    return 0;
}

int TempReader::daq_resume()
{
    std::cerr << "*** TempReader::resume" << std::endl;

    return 0;
}

int TempReader::set_data(size_t data_byte_size)
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

int TempReader::write_OutPort()
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

int TempReader::daq_run()
{
    if (m_debug) {
        std::cerr << "*** TempReader::run" << std::endl;
    }

    if (check_trans_lock()) {  // check if stop command has come
        set_trans_unlock();    // transit to CONFIGURED state
        return 0;
    }

    if (m_out_status == BUF_SUCCESS) {
		// w1 関数実行
		pValue2 = PyObject_CallObject(pFunc2, pArgs);
		if (pValue2 != nullptr) {
			/** Python 2.7 */
			//ret = PyString_AsString(pValue2); // Python2.7
			
			/*** Python3.5 */
			ret = PyUnicode_AsUTF8AndSize(pValue2, &pylen);
			sleep(1);
			
			sprintf(m_data, "気温(度): %s", ret);
			std::cerr << m_data << std::endl;
			m_recv_byte_size = sizeof(m_data);
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
    void TempReaderInit(RTC::Manager* manager)
    {
        RTC::Properties profile(tempreader_spec);
        manager->registerFactory(profile,
                    RTC::Create<TempReader>,
                    RTC::Delete<TempReader>);
    }
};
