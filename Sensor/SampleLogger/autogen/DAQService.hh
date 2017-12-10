// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.
#ifndef __DAQService_hh__
#define __DAQService_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_DAQService
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_DAQService
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_DAQService
#endif



#ifndef __SDOPackage_hh_EXTERNAL_GUARD__
#define __SDOPackage_hh_EXTERNAL_GUARD__
#include "SDOPackage.hh"
#endif
#ifndef __RTC_hh_EXTERNAL_GUARD__
#define __RTC_hh_EXTERNAL_GUARD__
#include "RTC.hh"
#endif



#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif





struct NameValue {
  typedef _CORBA_ConstrType_Variable_Var<NameValue> _var_type;

  
  ::CORBA::String_member name;

  ::CORBA::String_member value;



  void operator>>= (cdrStream &) const;
  void operator<<= (cdrStream &);
};

typedef NameValue::_var_type NameValue_var;

typedef _CORBA_ConstrType_Variable_OUT_arg< NameValue,NameValue_var > NameValue_out;

_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_NameValue;

_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_NVList;

class NVList_var;

class NVList : public _CORBA_Unbounded_Sequence< NameValue >  {
public:
  typedef NVList_var _var_type;
  inline NVList() {}
  inline NVList(const NVList& _s)
    : _CORBA_Unbounded_Sequence< NameValue > (_s) {}

  inline NVList(_CORBA_ULong _max)
    : _CORBA_Unbounded_Sequence< NameValue > (_max) {}
  inline NVList(_CORBA_ULong _max, _CORBA_ULong _len, NameValue* _val, _CORBA_Boolean _rel=0)
    : _CORBA_Unbounded_Sequence< NameValue > (_max, _len, _val, _rel) {}



  inline NVList& operator = (const NVList& _s) {
    _CORBA_Unbounded_Sequence< NameValue > ::operator=(_s);
    return *this;
  }
};

class NVList_out;

class NVList_var {
public:
  inline NVList_var() : _pd_seq(0) {}
  inline NVList_var(NVList* _s) : _pd_seq(_s) {}
  inline NVList_var(const NVList_var& _s) {
    if( _s._pd_seq )  _pd_seq = new NVList(*_s._pd_seq);
    else              _pd_seq = 0;
  }
  inline ~NVList_var() { if( _pd_seq )  delete _pd_seq; }
    
  inline NVList_var& operator = (NVList* _s) {
    if( _pd_seq )  delete _pd_seq;
    _pd_seq = _s;
    return *this;
  }
  inline NVList_var& operator = (const NVList_var& _s) {
    if( _s._pd_seq ) {
      if( !_pd_seq )  _pd_seq = new NVList;
      *_pd_seq = *_s._pd_seq;
    } else if( _pd_seq ) {
      delete _pd_seq;
      _pd_seq = 0;
    }
    return *this;
  }
  inline NameValue& operator [] (_CORBA_ULong _s) {
    return (*_pd_seq)[_s];
  }



  inline NVList* operator -> () { return _pd_seq; }
  inline const NVList* operator -> () const { return _pd_seq; }
#if defined(__GNUG__)
  inline operator NVList& () const { return *_pd_seq; }
#else
  inline operator const NVList& () const { return *_pd_seq; }
  inline operator NVList& () { return *_pd_seq; }
#endif
    
  inline const NVList& in() const { return *_pd_seq; }
  inline NVList&       inout()    { return *_pd_seq; }
  inline NVList*&      out() {
    if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
    return _pd_seq;
  }
  inline NVList* _retn() { NVList* tmp = _pd_seq; _pd_seq = 0; return tmp; }
    
  friend class NVList_out;
  
private:
  NVList* _pd_seq;
};

class NVList_out {
public:
  inline NVList_out(NVList*& _s) : _data(_s) { _data = 0; }
  inline NVList_out(NVList_var& _s)
    : _data(_s._pd_seq) { _s = (NVList*) 0; }
  inline NVList_out(const NVList_out& _s) : _data(_s._data) {}
  inline NVList_out& operator = (const NVList_out& _s) {
    _data = _s._data;
    return *this;
  }
  inline NVList_out& operator = (NVList* _s) {
    _data = _s;
    return *this;
  }
  inline operator NVList*&()  { return _data; }
  inline NVList*& ptr()       { return _data; }
  inline NVList* operator->() { return _data; }

  inline NameValue& operator [] (_CORBA_ULong _i) {
    return (*_data)[_i];
  }



  NVList*& _data;

private:
  NVList_out();
  NVList_out& operator=(const NVList_var&);
};

enum DAQLifeCycleState { LOADED, CONFIGURED, RUNNING, PAUSED, ERRORED /*, __max_DAQLifeCycleState=0xffffffff */ };
typedef DAQLifeCycleState& DAQLifeCycleState_out;

_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_DAQLifeCycleState;

enum DAQCommand { CMD_CONFIGURE, CMD_START, CMD_STOP, CMD_UNCONFIGURE, CMD_PAUSE, CMD_RESUME, CMD_RESTART, CMD_NOP /*, __max_DAQCommand=0xffffffff */ };
typedef DAQCommand& DAQCommand_out;

_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_DAQCommand;

enum DAQDone { UNDONE, DONE /*, __max_DAQDone=0xffffffff */ };
typedef DAQDone& DAQDone_out;

_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_DAQDone;

enum CompStatus { COMP_WORKING, COMP_FINISHED, COMP_WARNING, COMP_FATAL, COMP_RESTART /*, __max_CompStatus=0xffffffff */ };
typedef CompStatus& CompStatus_out;

_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_CompStatus;

struct FatalErrorStatus {
  typedef _CORBA_ConstrType_Variable_Var<FatalErrorStatus> _var_type;

  
  ::CORBA::Long fatalTypes;

  ::CORBA::Long errorCode;

  ::CORBA::String_member description;



  void operator>>= (cdrStream &) const;
  void operator<<= (cdrStream &);
};

typedef FatalErrorStatus::_var_type FatalErrorStatus_var;

typedef _CORBA_ConstrType_Variable_OUT_arg< FatalErrorStatus,FatalErrorStatus_var > FatalErrorStatus_out;

_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_FatalErrorStatus;

struct Status {
  typedef _CORBA_ConstrType_Variable_Var<Status> _var_type;

  
  ::CORBA::String_member comp_name;

  DAQLifeCycleState state;

  ::CORBA::ULongLong event_size;

  CompStatus comp_status;



  void operator>>= (cdrStream &) const;
  void operator<<= (cdrStream &);
};

typedef Status::_var_type Status_var;

typedef _CORBA_ConstrType_Variable_OUT_arg< Status,Status_var > Status_out;

_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_Status;

#ifndef __DAQService__
#define __DAQService__

class DAQService;
class _objref_DAQService;
class _impl_DAQService;

typedef _objref_DAQService* DAQService_ptr;
typedef DAQService_ptr DAQServiceRef;

class DAQService_Helper {
public:
  typedef DAQService_ptr _ptr_type;

  static _ptr_type _nil();
  static _CORBA_Boolean is_nil(_ptr_type);
  static void release(_ptr_type);
  static void duplicate(_ptr_type);
  static void marshalObjRef(_ptr_type, cdrStream&);
  static _ptr_type unmarshalObjRef(cdrStream&);
};

typedef _CORBA_ObjRef_Var<_objref_DAQService, DAQService_Helper> DAQService_var;
typedef _CORBA_ObjRef_OUT_arg<_objref_DAQService,DAQService_Helper > DAQService_out;

#endif

// interface DAQService
class DAQService {
public:
  // Declarations for this interface type.
  typedef DAQService_ptr _ptr_type;
  typedef DAQService_var _var_type;

  static _ptr_type _duplicate(_ptr_type);
  static _ptr_type _narrow(::CORBA::Object_ptr);
  static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
  
  static _ptr_type _nil();

  static inline void _marshalObjRef(_ptr_type, cdrStream&);

  static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
    omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
    if (o)
      return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
    else
      return _nil();
  }

  static _core_attr const char* _PD_repoId;

  // Other IDL defined within this scope.
  
};

class _objref_DAQService :
  public virtual ::CORBA::Object,
  public virtual omniObjRef
{
public:
  DAQLifeCycleState getState();
  RTC::ReturnCode_t setCommand(::DAQCommand command);
  DAQCommand getCommand();
  DAQDone checkDone();
  void setDone();
  void setStatus(const ::Status& stat);
  Status* getStatus();
  void setCompParams(const ::NVList& comp_params);
  NVList* getCompParams();
  void setRunNo(::CORBA::Long run_no);
  ::CORBA::Long getRunNo();
  void setFatalStatus(const ::FatalErrorStatus& fatalStaus);
  FatalErrorStatus* getFatalStatus();

  inline _objref_DAQService()  { _PR_setobj(0); }  // nil
  _objref_DAQService(omniIOR*, omniIdentity*);

protected:
  virtual ~_objref_DAQService();

  
private:
  virtual void* _ptrToObjRef(const char*);

  _objref_DAQService(const _objref_DAQService&);
  _objref_DAQService& operator = (const _objref_DAQService&);
  // not implemented

  friend class DAQService;
};

class _pof_DAQService : public _OMNI_NS(proxyObjectFactory) {
public:
  inline _pof_DAQService() : _OMNI_NS(proxyObjectFactory)(DAQService::_PD_repoId) {}
  virtual ~_pof_DAQService();

  virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
  virtual _CORBA_Boolean is_a(const char*) const;
};

class _impl_DAQService :
  public virtual omniServant
{
public:
  virtual ~_impl_DAQService();

  virtual DAQLifeCycleState getState() = 0;
  virtual RTC::ReturnCode_t setCommand(::DAQCommand command) = 0;
  virtual DAQCommand getCommand() = 0;
  virtual DAQDone checkDone() = 0;
  virtual void setDone() = 0;
  virtual void setStatus(const ::Status& stat) = 0;
  virtual Status* getStatus() = 0;
  virtual void setCompParams(const ::NVList& comp_params) = 0;
  virtual NVList* getCompParams() = 0;
  virtual void setRunNo(::CORBA::Long run_no) = 0;
  virtual ::CORBA::Long getRunNo() = 0;
  virtual void setFatalStatus(const ::FatalErrorStatus& fatalStaus) = 0;
  virtual FatalErrorStatus* getFatalStatus() = 0;
  
public:  // Really protected, workaround for xlC
  virtual _CORBA_Boolean _dispatch(omniCallHandle&);

private:
  virtual void* _ptrToInterface(const char*);
  virtual const char* _mostDerivedRepoId();
  
};


_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_DAQService;



class POA_DAQService :
  public virtual _impl_DAQService,
  public virtual ::PortableServer::ServantBase
{
public:
  virtual ~POA_DAQService();

  inline ::DAQService_ptr _this() {
    return (::DAQService_ptr) _do_this(::DAQService::_PD_repoId);
  }
};







#undef _core_attr
#undef _dyn_attr

extern void operator<<=(::CORBA::Any& _a, const NameValue& _s);
extern void operator<<=(::CORBA::Any& _a, NameValue* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, NameValue*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const NameValue*& _sp);

void operator<<=(::CORBA::Any& _a, const NVList& _s);
void operator<<=(::CORBA::Any& _a, NVList* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, NVList*& _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const NVList*& _sp);

inline void operator >>=(DAQLifeCycleState _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (DAQLifeCycleState& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= ERRORED) {
    _e = (DAQLifeCycleState) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, DAQLifeCycleState _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, DAQLifeCycleState& _s);

inline void operator >>=(DAQCommand _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (DAQCommand& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= CMD_NOP) {
    _e = (DAQCommand) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, DAQCommand _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, DAQCommand& _s);

inline void operator >>=(DAQDone _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (DAQDone& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= DONE) {
    _e = (DAQDone) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, DAQDone _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, DAQDone& _s);

inline void operator >>=(CompStatus _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (CompStatus& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= COMP_RESTART) {
    _e = (CompStatus) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, CompStatus _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, CompStatus& _s);

extern void operator<<=(::CORBA::Any& _a, const FatalErrorStatus& _s);
extern void operator<<=(::CORBA::Any& _a, FatalErrorStatus* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, FatalErrorStatus*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const FatalErrorStatus*& _sp);

extern void operator<<=(::CORBA::Any& _a, const Status& _s);
extern void operator<<=(::CORBA::Any& _a, Status* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Status*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Status*& _sp);

void operator<<=(::CORBA::Any& _a, DAQService_ptr _s);
void operator<<=(::CORBA::Any& _a, DAQService_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, DAQService_ptr& _s);



inline void
DAQService::_marshalObjRef(::DAQService_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_DAQService
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_DAQService
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_DAQService
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_DAQService
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_DAQService
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_DAQService
#endif

#endif  // __DAQService_hh__

