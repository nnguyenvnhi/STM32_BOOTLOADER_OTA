/***********************************************************************************
**  PROJECT      : VNPT - IoT                                                     **
**                                                                                **  
**  FILENAME     : Std_Types.h                                                    **
**                                                                                **
**  VERSION      : 1.0.0                                                          **
**                                                                                **
**  DATE         : 2022-05-02                                                     **
**                                                                                **
**  AUTHOR       : @VNPT TEAMS                                                    **
**                                                                                **
**  VENDOR       : @GRAPETECH                                                     **
**                                                                                **
**  DESCRIPTION  : Standard Types Driver header definition file                   **
**                                                                                **                                                                               
**  MAY BE CHANGED BY USER : TIEN DAT NGUYEN, NGUYEN VAN NHI                      **
**                                                                                **
***********************************************************************************/
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* CPU register type width */
#define CPU_TYPE_8                                  (8U)
#define CPU_TYPE_16                                 (16U)
#define CPU_TYPE_32                                 (32U)


/* Bit order definition */
#define MSB_FIRST                   (0u)        /* Big endian bit ordering */
#define LSB_FIRST                   (1u)        /* Little endian bit ordering */


/* Byte order definition */
#define HIGH_BYTE_FIRST             (0u)        /* Big endian byte ordering */
#define LOW_BYTE_FIRST              (1u)        /* Little endian byte ordering */


#define CPU_BIT_ORDER       LSB_FIRST
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST

/* Boolean Values */
 
#ifndef FALSE
#define FALSE       (0u)
#endif


#ifndef TRUE
#define TRUE        (1u)
#endif


#ifndef HIGH
#define HIGH		(1u)
#endif

#ifndef LOW
#define LOW			(1u)
#endif

//typedef unsigned char         boolean;
typedef unsigned char         uint8;         /*           0 .. 255             */
typedef char                  int8;          /*        -128 .. +127            */
typedef unsigned int          uint16;        /*           0 .. 65535           */
typedef int                   int16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;        /*           0 .. 4294967295      */
typedef long                  int32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;        /*       0..18446744073709551615  */
typedef long long             int64;
typedef float                 float32_t;
typedef double                float64_t;


#endif /* END OF PLATFORM_TYPES_H */
