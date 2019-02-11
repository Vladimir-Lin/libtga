#include "libbmp.hpp"

#pragma pack(push,1)

// Totally 14 bytes
typedef struct          {
  uint8_t magic   [ 2 ] ; /* the magic number used to identify the BMP file:
                             0x42 0x4D (Hex code points for B and M).
                             The following entries are possible:
                             BM - Windows 3.1x, 95, NT, ... etc
                             BA - OS/2 Bitmap Array
                             CI - OS/2 Color Icon
                             CP - OS/2 Color Pointer
                             IC - OS/2 Icon
                             PT - OS/2 Pointer. */
  uint8_t size    [ 4 ] ; /* the size of the BMP file in bytes */
  uint8_t creator [ 4 ] ; /* reserved. */
  uint8_t offset  [ 4 ] ; /* the offset, i.e. starting address,
                            of the byte where the bitmap data can be found. */
} BmpHeader             ;

typedef struct         {
  uint8_t size   [ 4 ] ; /* the size of this header (12 bytes) */
  uint8_t width  [ 2 ] ; /* the bitmap width in pixels */
  uint8_t height [ 2 ] ; /* the bitmap height in pixels */
  uint8_t planes [ 2 ] ; /* the number of color planes being used. Must be set to 1. */
  uint8_t depth  [ 2 ] ; /* the number of bits per pixel,
                            which is the color depth of the image.
                            Typical values are 1, 4, 8, 16, 24 and 32. */
} CoreHeader           ;

typedef struct              {
  uint8_t size        [ 4 ] ; /* the size of this header (40 bytes) */
  uint8_t width       [ 2 ] ; /* the bitmap width in pixels */
  uint8_t height      [ 2 ] ; /* the bitmap height in pixels */
  uint8_t planes      [ 2 ] ; /* the number of color planes being used. Must be set to 1. */
  uint8_t depth       [ 2 ] ; /* the number of bits per pixel,
                                 which is the color depth of the image.
                                 Typical values are 1, 4, 8, 16, 24 and 32. */
  uint8_t compression [ 4 ] ; /* the compression method being used.
                                 See also bmp_compression_method_t. */
  uint8_t bytes       [ 4 ] ; /* the image size. This is the size of the raw bitmap
                                 data (see below), and should not be confused
                                 with the file size. */
  uint8_t horizontal  [ 4 ] ; /* the horizontal resolution of the image. (pixel per meter) */
  uint8_t vertical    [ 4 ] ; /* the vertical resolution of the image. (pixel per meter) */
  uint8_t colors      [ 4 ] ; /* the number of colors in the color palette, or 0 to default to 2<sup><i>n</i></sup>. */
  uint8_t importants  [ 4 ] ; /* the number of important colors used,
                                 or 0 when every color is important;
                                 generally ignored. */
} InforHeader               ;

#pragma pack(pop)

BmpObject:: BmpObject (void)
{
  bmpData  = nullptr ;
  dataSize = 0       ;
}

BmpObject::~BmpObject (void)
{
}

void BmpObject::setData(void * data,uint32_t size)
{
  bmpData  = data ;
  dataSize = size ;
}

void * BmpObject::data(void)
{
  return bmpData ;
}

uint32_t BmpObject::size(void)
{
  return dataSize ;
}

int16_t BmpObject::toInt16(void * data)
{
  uint8_t * v = (uint8_t *) data  ;
  int16_t   r = (int16_t) v [ 1 ] ;
  r <<= 8                         ;
  r  |= v [ 0 ]                   ;
  return r                        ;
}

uint16_t BmpObject::toUint16(void * data)
{
  uint8_t * v = (uint8_t *) data   ;
  uint16_t  r = (uint16_t) v [ 1 ] ;
  r <<= 8                          ;
  r  |= v [ 0 ]                    ;
  return r                         ;
}

int32_t BmpObject::toInt32(void * data)
{
  uint8_t * v = (uint8_t *) data  ;
  int32_t   r = (int32_t) v [ 3 ] ;
  r <<= 8                         ;
  r  |= v [ 2 ]                   ;
  r <<= 8                         ;
  r  |= v [ 1 ]                   ;
  r <<= 8                         ;
  r  |= v [ 0 ]                   ;
  return r                        ;
}

uint32_t BmpObject::toUint32(void * data)
{
  uint8_t * v = (uint8_t *) data   ;
  uint32_t  r = (uint32_t) v [ 3 ] ;
  r <<= 8                          ;
  r  |= v [ 2 ]                    ;
  r <<= 8                          ;
  r  |= v [ 1 ]                    ;
  r <<= 8                          ;
  r  |= v [ 0 ]                    ;
  return r                         ;
}

void BmpObject::fromInt16(int16_t v,void * data)
{
  uint8_t * z = (uint8_t *) data ;
  z [ 0 ] = v & 0xFF ; v >>= 8   ;
  z [ 1 ] = v & 0xFF             ;
}

void BmpObject::fromUint16(uint16_t v,void * data)
{
  uint8_t * z = (uint8_t *) data ;
  z [ 0 ] = v & 0xFF ; v >>= 8   ;
  z [ 1 ] = v & 0xFF             ;
}

void BmpObject::fromInt32(int32_t v,void * data)
{
  uint8_t * z = (uint8_t *) data ;
  z [ 0 ] = v & 0xFF ; v >>= 8   ;
  z [ 1 ] = v & 0xFF ; v >>= 8   ;
  z [ 2 ] = v & 0xFF ; v >>= 8   ;
  z [ 3 ] = v & 0xFF             ;
}

void BmpObject::fromUint32(uint32_t v,void * data)
{
  uint8_t * z = (uint8_t *) data ;
  z [ 0 ] = v & 0xFF ; v >>= 8   ;
  z [ 1 ] = v & 0xFF ; v >>= 8   ;
  z [ 2 ] = v & 0xFF ; v >>= 8   ;
  z [ 3 ] = v & 0xFF             ;
}
