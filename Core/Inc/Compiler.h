/***********************************************************************************
**  PROJECT      : VNPT - IoT                                                     **
**                                                                                **  
**  FILENAME     : Compiler.h                                                     **
**                                                                                **
**  VERSION      : 1.0.0                                                          **
**                                                                                **
**  DATE         : 2022-05-02                                                     **
**								                  **
**  AUTHOR       : @VNPT TEAMS       	                                          **
**                                                                                **
**  VENDOR       : @GRAPETECH				                          **
**                                                                                **
**  DESCRIPTION  : Compiler Driver header definition file                         **
**                                                                                **                                                                               
**  MAY BE CHANGED BY USER : TIEN DAT NGUYEN, NGUYEN VAN NHI                      **
**                                                                                **
***********************************************************************************/

#ifndef COMPILER_H_
#define COMPILER_H_

/* The memory class is used for the declaration of local pointers */
#define AUTOMATIC


/* The memory class is used within type definitions, where no memory
   qualifier can be specified */
#define TYPEDEF


/* This is used to define the void pointer to zero definition */
#define NULL_PTR          ((void *)0)


/* This is used to define the abstraction of compiler keyword inline */
#define INLINE            inline


/* This is used to define the local inline function */
#define LOCAL_INLINE      static inline


/* This is used to define the abstraction of compiler keyword static */
#define STATIC            static


/*************************************UNFINISHED***********************************/



/* Function is private */
#define PRIVATE
/* Function is public */
#define PUBLIC
/* This is FUNC macro for the identification information */
#define FUNC(rettype, memclass) memclass rettype


/* This is FUNC_P2CONST macro for the declaration and definition of functions
 returning a pointer to a constant */
#define PTRCLASS

#define MEMCLASS

#define FUNC_P2CONST(rettype, ptrclass, memclass)\
	const ptrclass rettype * memclass


/* This is FUNC_P2VAR macro for the declaration and definition of functions
	returning a pointer to a variable */
#define	PBCFG

#define CODE 

#define FUNC_P2VAR(rettype, ptrclass, memclass)\
	ptrclass rettype * memclass


/* This is P2VAR macro for the declaration and definition of pointer in RAM,
	readable and writeable */
//define memclas, ptrclass
#define P2VAR(ptrtype, memclass, ptrclass) \
	ptrclass ptrtype * memclass


/* Use according POWER_PC standard (CONSTP2FUNC) */
#define POWER_PC
/* Use according METROWERKS_S12XS standard (P2FUNC, P2CONST) */
#define METROWERKS_S12X

/* This is P2CONST macro for the declaration and definition of pointer in RAM,
	read only */
//define memclas, ptrclass
#ifdef	METROWERKS_S12X
	#define P2CONST(ptrtype, memclass, ptrclass) \
		const ptrtype memclass * ptrclass 
#endif

#ifdef	COSMIC_S12X
	#define P2CONST(ptrtype, memclass, ptrclass) \
		const ptrtype ptrclass * memclass
#endif

#ifdef	TASKING_ST10		
	#define P2CONST(ptrtype, memclass, ptrclass) \
		const ptrclass ptrtype * memclass
#endif


/* This is CONSTP2VAR for the declaration and definition of constant pointers
   accessing variables */
//define memclas, ptrclass
#define CONSTP2CONST (ptrtype, memclass, ptrclass) \
	const memclass ptrtype * const ptrclass


/* This is P2FUNC for the definition of pointers to functions */
//define memclas, ptrclass
#ifdef METROWERKS_S12X
	#define P2FUNC(rettype, ptrclass, fctname)\
		rettype (*ptrclass fctname)
#endif

#ifdef COSMIC_S12X
	#define P2FUNC(rettype, ptrclass, fctname) \
		ptrclass rettype (*fctname)
#endif


/* This is CONSTP2FUNC macro for the definition of constant pointers to functions */
//define memclas, ptrclass
#ifdef POWER_PC
	#define CONSTP2FUNC(rettype, ptrclass, fctname)\
		rettype (* const fctname)
#endif

#ifdef CODEWARRIOR_S12X
	#define CONSTP2FUNC(rettype, ptrclass, fctname)\
		rettype (* const ptrclass fctname)
#endif		


/* This is CONST macro for the declaration and definition of constants */
//define memclass
#define CONST(type, memclass) memclass const type


/* This is VAR macro for the declaration and definition of variables */
//define memclass
#define VAR(type, memclass) memclass type


//#ifdef _ChaCha20_
#define CHACHA20_LOCAL_VAR
#define CHACHA20_GLOBAL_VAR
#define CHACHA20_PRIVATE_FUNCTION
#define CHACHA20_PUBLIC_FUNCTION
//#endif

//#ifdef _MQTT_
#define MQTT_LOCAL_VAR
#define MQTT_GLOBAL_VAR
#define MQTT_PRIVATE_FUNCTION
#define MQTT_PUBLIC_FUNCTION
//#endif


//#ifdef _SCHEDULER_
#define SCHEDULER_LOCAL_VAR
#define SCHEDULER_GLOBAL_VAR
#define SCHEDULER_PRIVATE_FUNCTION
#define SCHEDULER_PUBLIC_FUNCTION
//#endif


//#ifdef _SketchVNPT_
#define SKETCHVNPT_LOCAL_VAR
#define SKETCHVNPT_GLOBAL_VAR
#define SKETCHVNPT_PRIVATE_FUNCTION
#define SKETCHVNPT_PUBLIC_FUNCTION
//#endif


//#ifdef _SketchWifi_
#define SKETCHWIFI_LOCAL_VAR
#define SKETCHWIFI_GLOBAL_VAR
#define SKETCHWIFI_PRIVATE_FUNCTION
#define SKETCHWIFI_PUBLIC_FUNCTION
//#endif


//#ifdef _OTAUpdate_
#define OTA_LOCAL_VAR
#define OTA_GLOBAL_VAR
#define OTA_PRIVATE_FUNCTION
#define OTA_PUBLIC_FUNCTION
//#endif

#define MAIN_LOCAL_VAR
#define MAIN_GLOBAL_VAR
#define MAIN_PRIVATE_FUNCTION
#define MAIN_PUBLIC_FUNCTION

#define AES_LOCAL_VAR
#define AES_GLOBAL_VAR
#define AES_PRIVATE_FUNCTION
#define AES_PUBLIC_FUNCTION

#define DEBUG_LOCAL_VAR
#define DEBUG_GLOBAL_VAR
#define DEBUG_PRIVATE_FUNCTION
#define DEBUG_PUBLIC_FUNCTION


#endif  /* End of Compiler.h Module */
