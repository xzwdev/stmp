/*
 * logger.h
 *
 *  Created on: 2010-12-1
 *      Author: xuzewen
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#if !defined (__LIBMISC_H__) && !defined (__LIBMISC__)
#error libmisc.h can be included directly.
#endif

#include "macro.h"

LIBMISC_BEGIN_DECLS

/** 日志功能总是应该先初始化后再使用. */
LIBMISC_EXPORT void logger_init();

/** 获得日志文件句柄. */
LIBMISC_EXPORT FILE* logger_fd();

/** 是否为后台进程. */
LIBMISC_EXPORT int logger_isdaemon();

/** 设置日志级别到TRACE. */
LIBMISC_EXPORT void logger_set2trace();

/** 设置日志级别到DEBUG. */
LIBMISC_EXPORT void logger_set2debug();

/** 设置日志级别到INFO. */
LIBMISC_EXPORT void logger_set2info();

/** 设置日志级别到WARN. */
LIBMISC_EXPORT void logger_set2warn();

/** 设置日志级别到ERROR. */
LIBMISC_EXPORT void logger_set2error();

/** 设置日志级别到FAULT. */
LIBMISC_EXPORT void logger_set2fault();

/** TRACE是否可写. */
LIBMISC_EXPORT int logger_istrace();

/** DEBUG是否可写. */
LIBMISC_EXPORT int logger_isdebug();

/** INFO是否可写. */
LIBMISC_EXPORT int logger_isinfo();

/** WARN是否可写. */
LIBMISC_EXPORT int logger_iswarn();

/** ERROR是否可写. */
LIBMISC_EXPORT int logger_iserror();

/** FAULT是否可写. */
LIBMISC_EXPORT int logger_isfault();

/** 函数与行是否可写. */
LIBMISC_EXPORT int logger_isenable(const char* fun, int line);

/** 设置函数与行可写. */
LIBMISC_EXPORT void logger_enable(const char* fun, int line);

/** 设置全部函数与行可写. */
LIBMISC_EXPORT void logger_enable_all();

/** 设置函数与行不可写. */
LIBMISC_EXPORT void logger_disable(const char* fun, int line);

/** 设置全部函数与行不可写. */
LIBMISC_EXPORT void logger_disable_all();

/** 当前时间: yyyy-mm-dd hh. */
LIBMISC_EXPORT char* logger_yyyy_mm_dd_hh_now();

/** 当前时间: yyyy-mm-dd hh:mi:ss. */
LIBMISC_EXPORT char* logger_yyyy_mm_dd_hh_mi_ss_now();

/** 当前时间: yyyy-mm-dd. */
LIBMISC_EXPORT char* logger_yyyy_mm_dd_now();

/** 当前时间: yyyymm. */
LIBMISC_EXPORT char* logger_yyyymm();

/** 当前时间: hh:mi:ss. */
LIBMISC_EXPORT char* logger_hhmiss();

/** 当前时间: hh:mi:ss.mse. */
LIBMISC_EXPORT char* logger_hhmissmse();

#define __TRAC__(fd, format, ...) fprintf((fd), "%s[TRAC](%s %d)"format"", logger_hhmissmse(), __FUNCTION__, __LINE__,  ##__VA_ARGS__);
#define __DEBU__(fd, format, ...) fprintf((fd), "%s[DEGU](%s %d)"format"", logger_hhmissmse(), __FUNCTION__, __LINE__,  ##__VA_ARGS__);
#define __INFO__(fd, format, ...) fprintf((fd), "%s[INFO](%s %d)"format"", logger_hhmissmse(), __FUNCTION__, __LINE__,  ##__VA_ARGS__);
#define __WARN__(fd, format, ...) fprintf((fd), "%s[WARN](%s %d)"format"", logger_hhmissmse(), __FUNCTION__, __LINE__,  ##__VA_ARGS__);
#define __ERRO__(fd, format, ...) fprintf((fd), "%s[ERRO](%s %d)"format"", logger_hhmissmse(), __FUNCTION__, __LINE__,  ##__VA_ARGS__);
#define __FAUL__(fd, format, ...) fprintf((fd), "%s[FAUL](%s %d)"format"", logger_hhmissmse(), __FUNCTION__, __LINE__,  ##__VA_ARGS__);

#define LOG_PRINTF(format, ...) fprintf(stdout, ""format"", ##__VA_ARGS__);

#define LOG_TRACE(format, ...)	\
if(logger_istrace() == 0 && logger_isenable(__FUNCTION__, __LINE__) == 0) \
{	\
	FILE* __fd__ = logger_fd();	\
	if (__fd__ != NULL)	\
	{	\
		__TRAC__(__fd__, format, ##__VA_ARGS__)	\
		fclose(__fd__);	\
	}	\
	if (logger_isdaemon() != 0)	\
	{	\
		__TRAC__(stdout, format, ##__VA_ARGS__)	\
	}	\
}

#define LOG_DEBUG(format, ...) 	\
if(logger_isdebug() == 0 && logger_isenable(__FUNCTION__, __LINE__) == 0)	\
{	\
	FILE* __fd__ = logger_fd();	\
	if (__fd__ != NULL)	\
	{	\
		__DEBU__(__fd__, format, ##__VA_ARGS__)	\
		fclose(__fd__);	\
	}	\
	if (logger_isdaemon() != 0)	\
	{	\
		__DEBU__(stdout, format, ##__VA_ARGS__)	\
	}	\
}

#define LOG_INFO(format, ...) 	\
if(logger_isinfo() == 0 && logger_isenable(__FUNCTION__, __LINE__) == 0)	\
{	\
	FILE* __fd__ = logger_fd();	\
	if (__fd__ != NULL)	\
	{	\
		__INFO__(__fd__, format, ##__VA_ARGS__)	\
		fclose(__fd__);	\
	}	\
	if (logger_isdaemon() != 0)	\
	{	\
		__INFO__(stdout, format, ##__VA_ARGS__)	\
	}	\
}

#define LOG_WARN(format, ...)	\
if(logger_iswarn() == 0 && logger_isenable(__FUNCTION__, __LINE__) == 0)	\
{	\
	FILE* __fd__ = logger_fd();	\
	if (__fd__ != NULL)	\
	{	\
		__WARN__(__fd__, format, ##__VA_ARGS__)	\
		fclose(__fd__);	\
	}	\
	if (logger_isdaemon() != 0)	\
	{	\
		__WARN__(stdout, format, ##__VA_ARGS__)	\
	}	\
}

#define LOG_ERROR(format, ...)	\
if(logger_iserror() == 0 && logger_isenable(__FUNCTION__, __LINE__) == 0)	\
{	\
	FILE* __fd__ = logger_fd();	\
	if (__fd__ != NULL)	\
	{	\
		__ERRO__(__fd__, format, ##__VA_ARGS__)	\
		fclose(__fd__);	\
	}	\
	if (logger_isdaemon() != 0)	\
	{	\
		__ERRO__(stdout, format, ##__VA_ARGS__)	\
	}	\
}

#define LOG_FAULT(format, ...)	\
if(logger_isfault() == 0 && logger_isenable(__FUNCTION__, __LINE__) == 0)	\
{	\
	FILE* __fd__ = logger_fd();	\
	if (__fd__ != NULL)	\
	{	\
		__FAUL__(__fd__, format, ##__VA_ARGS__)	\
		fclose(__fd__);	\
	}	\
	if (logger_isdaemon() != 0)	\
	{	\
		__FAUL__(stdout, format, ##__VA_ARGS__)	\
	}	\
}

LIBMISC_END_DECLS

#endif /* LOGGER_H_ */
