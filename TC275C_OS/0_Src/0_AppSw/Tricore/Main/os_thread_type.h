
#ifndef OS_THREAD_H_ 
#define OS_THREAD_H_

#define NO_DEFINITION (0)
#define PERIODIC      (1)
#define EVENT  (2)

typedef enum  {

	 CORE_ID0,
	 CORE_ID1,
	 CORE_ID2,
	 CORE_MAX_ID_NUM

}OS_CORE_ID_t;

typedef enum  {

	 THREAD_ID0,
	 THREAD_ID1,
	 THREAD_ID2,
	 THREAD_ID3,
	 THREAD_ID4,
	 THREAD_ID5,
	 THREAD_ID6,
	 THREAD_ID7,
	 THREAD_ID8,
	 THREAD_ID9,
	 THREAD_ID10,
	 THREAD_MAX_ID_NUM,
	 NO_THREAD
 
}OS_THREAD_ID_t;

#endif

