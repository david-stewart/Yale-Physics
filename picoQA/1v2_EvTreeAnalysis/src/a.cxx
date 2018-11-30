// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME a

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "RunStats.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_OneVar(void *p = 0);
   static void *newArray_OneVar(Long_t size, void *p);
   static void delete_OneVar(void *p);
   static void deleteArray_OneVar(void *p);
   static void destruct_OneVar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OneVar*)
   {
      ::OneVar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OneVar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OneVar", ::OneVar::Class_Version(), "RunStats.h", 21,
                  typeid(::OneVar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::OneVar::Dictionary, isa_proxy, 4,
                  sizeof(::OneVar) );
      instance.SetNew(&new_OneVar);
      instance.SetNewArray(&newArray_OneVar);
      instance.SetDelete(&delete_OneVar);
      instance.SetDeleteArray(&deleteArray_OneVar);
      instance.SetDestructor(&destruct_OneVar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OneVar*)
   {
      return GenerateInitInstanceLocal((::OneVar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::OneVar*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr OneVar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OneVar::Class_Name()
{
   return "OneVar";
}

//______________________________________________________________________________
const char *OneVar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OneVar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OneVar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OneVar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OneVar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OneVar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OneVar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OneVar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void OneVar::Streamer(TBuffer &R__b)
{
   // Stream an object of class OneVar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(OneVar::Class(),this);
   } else {
      R__b.WriteClassBuffer(OneVar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OneVar(void *p) {
      return  p ? new(p) ::OneVar : new ::OneVar;
   }
   static void *newArray_OneVar(Long_t nElements, void *p) {
      return p ? new(p) ::OneVar[nElements] : new ::OneVar[nElements];
   }
   // Wrapper around operator delete
   static void delete_OneVar(void *p) {
      delete ((::OneVar*)p);
   }
   static void deleteArray_OneVar(void *p) {
      delete [] ((::OneVar*)p);
   }
   static void destruct_OneVar(void *p) {
      typedef ::OneVar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::OneVar

namespace {
  void TriggerDictionaryInitialization_a_Impl() {
    static const char* headers[] = {
"RunStats.h",
0
    };
    static const char* includePaths[] = {
"/Users/djs232/local/root6/pro/include",
"/Users/djs232/lavoro/2018/git/Yale-Physics/picoQA/1v2_EvTreeAnalysis/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "a dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
struct __attribute__((annotate("$clingAutoload$RunStats.h")))  OneVar;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "a dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "RunStats.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"OneVar", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("a",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_a_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_a_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_a() {
  TriggerDictionaryInitialization_a_Impl();
}
