#ifndef COMMON_H
#define COMMON_H

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif


#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }


#endif // COMMON_H
