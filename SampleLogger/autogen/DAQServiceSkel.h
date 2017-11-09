// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file DAQServiceSkel.h 
 * @brief DAQService server skeleton header wrapper code
<<<<<<< HEAD
 * @date Wed Nov  8 02:43:03 2017 
=======
 * @date Wed Nov  1 16:55:42 2017 
>>>>>>> 5ba1018078814e0d7ab6e6279abdeffed5dca237
 *
 */

#ifndef DAQSERVICESKEL_H
#define DAQSERVICESKEL_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "DAQServiceC.h"
#  include "DAQServiceS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "DAQService.hh"
#elif defined ORB_IS_MICO
#  include "DAQService.h"
#elif defined ORB_IS_ORBIT2
#  include "/DAQService-cpp-stubs.h"
#  include "/DAQService-cpp-skels.h"
#else
#  error "NO ORB defined"
#endif

#endif // DAQSERVICESKEL_H
