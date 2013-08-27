/*
 * macro.h
 *
 *  Created on: 2013-7-12
 *      Author: xuzewen
 */

#ifndef MACRO_H_
#define MACRO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>
#include <pthread.h>
#ifdef LINUX
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/epoll.h>
#endif
#ifdef WIN32
#include <io.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <Iphlpapi.h>
#endif

#define __LIBMISC_H__

#if !defined (__LIBMISC_H__) && !defined (__LIBMISC__)
#error only libmisc.h can be included directly.
#endif

#ifdef  __cplusplus
# define LIBMISC_BEGIN_DECLS  									extern "C" {
# define LIBMISC_END_DECLS    									}
#else
# define LIBMISC_BEGIN_DECLS
# define LIBMISC_END_DECLS
#endif

#ifdef _MSC_VER
#define LIBMISC_EXPORT											_declspec(dllexport)
#else
#define LIBMISC_EXPORT
#endif

#define uchar													unsigned char			/** 无符号单字节. */
#define ushort													unsigned short			/** 无符号双字节. */
#define uint													unsigned int			/** 无符号四字节. */
#define ulong													unsigned long			/** 无符号四/八字节. 为避免平台的差异, 不建议使用. */
#define ullong  												unsigned long long int	/** 无符号八字节. */

#define UCHAR_MAX_VALUE											0xFF					/** uchar极限值. */
#define USHORT_MAX_VALUE										0xFFFF					/** ushort极限值. */
#define UINT_MAX_VALUE											0xFFFFFFFF				/** uint极限值. */
#define ULONG_MAX_VALUE											0xFFFFFFFF				/** ulong极限值. */
#define ULLONG_MAX_VALUE										0xFFFFFFFFFFFFFFFFULL	/** ullong极限值. */

#define PRESENT													0x01					/** present. */
#define NOT_PRESENT												0x00					/** not present. */

#define H2N_DIR													0x00					/** host to network direction. */
#define N2H_DIR													0x01					/** network to host direction. */

#endif /* MACRO_H_ */
