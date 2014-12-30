//
//  Import/Export Directive for blas DLL
//
//  Chris Anderson (C) UCLA 1997
//
#undef  __IMPEXP__

#ifdef  __BCPLUSPLUS__
#ifdef  __EXPORT_BLAS__
#define __IMPEXP__  __declspec(dllexport)
#endif
#ifdef  __USEDLL__
#define __IMPEXP__  __declspec(dllimport)
#endif
#endif

#ifdef  _MSC_VER
#ifdef  __EXPORT_BLAS__
#define __IMPEXP__  __declspec(dllexport)
#endif
#ifdef  __USEDLL__
#define __IMPEXP__  __declspec(dllimport)
#endif
#endif


#ifdef   __STATIC__
#undef   __IMPEXP__
#define  __IMPEXP__
#endif

#ifndef __IMPEXP__
#define __IMPEXP__
#endif
  
