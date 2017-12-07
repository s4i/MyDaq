// -*- C++ -*-
/*!
 * @file
 * @brief
 * @date
 * @author
 *
 */

#include "TempReader.h"
#include <Python.h>

using DAQMW::FatalType::DATAPATH_DISCONNECTED;
using DAQMW::FatalType::OUTPORT_ERROR;
using DAQMW::FatalType::USER_DEFINED_ERROR1;
using DAQMW::FatalType::USER_DEFINED_ERROR2;

// Python.h
PyObject *pName, *pModule, *pFunc, *pFunc2;
PyObject *pArgs, *pValue, *pValue2;
PyObject* sysPath, *dir;

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

    try {
		Py_Initialize();
        /** Python2.7 PYTHONPATH 未設定時のカレントディレクトリ捕捉 */
		PyObject *sys = PyImport_ImportModule("sys");
		PyObject *path = PyObject_GetAttrString(sys, "path");
		PyList_Append(path, PyString_FromString("."));
		PySys_SetArgv(*ArgCounter_ptr, ArgVector_ptr); // Python2.7
		//char word[] = "path";
		//sysPath = PySys_GetObject(word);
		//dir = PyString_FromString(".");
		//PyList_Append(sysPath, dir);
		pName = PyString_FromString(MY_MODULE.c_str()); 
		
		// Python Module<(*:module).py> set
		pModule = PyImport_Import(pName);
		Py_DECREF(pName);
		if (pModule != NULL) {
			// Func1
			pFunc = PyObject_GetAttrString(pModule, MY_FUNC1.c_str());
			if (pFunc && PyCallable_Check(pFunc)) {
				// def 実行
				pValue = PyObject_CallObject(pFunc, NULL);
				if (pValue != NULL) {
					w1_dir = PyString_AsString(pValue); // Python2.7
					//pStr = PyUnicode_AsUTF8String(pValue);
					//w1_dir = PyUnicode_AsUTF8AndSize(pStr, &psize);

					Py_DECREF(pValue);
				}
				else {
					Py_DECREF(pFunc);
					Py_DECREF(pModule);
					PyErr_Print();
					fprintf(stderr,"Call failed\n");
					return 1;
				}
			}
			else {
				if (PyErr_Occurred())
					PyErr_Print();
				fprintf(stderr, "Cannot find function \"%s\"\n", MY_FUNC1.c_str());
			}
			
			std::cerr << w1_dir << std::endl; //w1_slave dir path
			
			// Func2
			pFunc2 = PyObject_GetAttrString(pModule, MY_FUNC2.c_str());    
			if (pFunc2 && PyCallable_Check(pFunc)) {
				pArgs = PyTuple_New(1); // 引数は1
				// ready 関数実行
				PyTuple_SetItem(pArgs, 0, PyString_FromString(w1_dir)); // Python2.7

			}
			else {
				if (PyErr_Occurred())
					PyErr_Print();
				fprintf(stderr, "Cannot find function \"%s\"\n", MY_FUNC2.c_str());
			}
		}
		else {
			PyErr_Print();
			fprintf(stderr, "Failed to load \"%s\"\n", MY_MODULE.c_str());
			return 1;
		}
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

int TempReader::daq_stop()
{
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
    memcpy(&(m_out_data.data[HEADER_BYTE_SIZE]), &mm_data[0], data_byte_size);
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
		if (pValue2 != NULL) {
			ret = PyString_AsString(pValue2); // Python2.7
			
			/*** python3.5 */
			//pStr2 = PyUnicode_AsUTF8String(pValue2);
			//ret = PyUnicode_AsUTF8AndSize(pStr2, &psize);
			
			Py_DECREF(pValue2);
		}
		else {
			Py_DECREF(pFunc2);
			Py_DECREF(pModule);
			PyErr_Print();
			fprintf(stderr,"Call failed\n");
			return 1;
		}
		
		sprintf(mm_data, "気温(度): %s", ret);
		std::cerr << mm_data << std::endl;
		m_recv_byte_size = sizeof(mm_data);
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
    void TempReaderInit(RTC::Manager* manager)
    {
        RTC::Properties profile(tempreader_spec);
        manager->registerFactory(profile,
                    RTC::Create<TempReader>,
                    RTC::Delete<TempReader>);
    }
};
