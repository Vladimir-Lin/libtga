/****************************************************************************\
 *
 *                         libbmp
 *
\****************************************************************************/

#ifndef LIBBMP_HPP
#define LIBBMP_HPP

#if defined (WIN32) && defined(BUILD_SHARED_LIBS)
  #if defined (_MSC_VER)
    #pragma warning(disable: 4251)
  #endif
  #if defined(EXPORT_LIBBMP)
    #define LIBBMP_EXPORT __declspec(dllexport)
  #else
    #define LIBBMP_EXPORT __declspec(dllimport)
  #endif
#else
    #define LIBBMP_EXPORT
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

class BmpObject
{
  public:

    explicit         BmpObject  (void) ;
    virtual         ~BmpObject  (void) ;

    virtual void     setData    (void * data,uint32_t size) ;
    virtual void   * data       (void) ;
    virtual uint32_t size       (void) ;

  protected:

    void *   bmpData  ;
    uint32_t dataSize ;

    int16_t          toInt16    (void * data) ;
    uint16_t         toUint16   (void * data) ;
    int32_t          toInt32    (void * data) ;
    uint32_t         toUint32   (void * data) ;

    void             fromInt16  (int16_t  v,void * data) ;
    void             fromUint16 (uint16_t v,void * data) ;
    void             fromInt32  (int32_t  v,void * data) ;
    void             fromUint32 (uint32_t v,void * data) ;

  private:

} ;

#endif
