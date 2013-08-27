/*
 * logger.c
 *
 *  Created on: 2010-12-1
 *      Author: xuzewen
 */

#include "logger.h"
#include "chashstr.h"

#define LOG_PATH 											"./"
#define MAX_LOGFILE_SIZE									1024 * 1024 * 2000		//~=2G.
enum
{
	LOG_LEVEL_TRACE = 0x00, LOG_LEVEL_DEBUG, LOG_LEVEL_INFO, LOG_LEVEL_WARN, LOG_LEVEL_ERROR, LOG_LEVEL_FAULT
};
typedef struct
{
	int ppid;
	int level;
#define LOG_ENABLE_ALL										0x00			/** log使能全部. */
#define LOG_ENABLE_XXX										0x01			/** log使能一部分. */
#define LOG_DISABLE_XXX										0x02			/** log使不能一部分. */
#define LOG_DISABLE_ALL										0x03			/** log使不能分部. */
	int ed;
	pthread_mutex_t mutex;
	chashstr* lx;
} logger_obj;

static logger_obj lo;
static void logger_setlevel(int le);
/*--------------------------------------------------------------------*/
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/** 日志功能总是应该先初始化后再使用. */
void logger_init()
{
	memset(&lo, 0, sizeof(logger_obj));
	lo.ppid = 0x00;
	lo.level = LOG_LEVEL_INFO; /** default INFO. */
	lo.ed = LOG_ENABLE_ALL; /** default log all. */
	pthread_mutex_init(&lo.mutex, NULL);
	lo.lx = chashstr_new();
#ifdef LINUX
	sleep(1);
	lo.ppid = getppid();
#endif
}

/** 获得日志文件句柄. */
FILE* logger_fd()
{
	char yymmdd[0x10] = { 0 };
	logger_yyyy_mm_dd_now(yymmdd);
	char logfilename[0x20] = { 0 };
	sprintf(logfilename, "%s%s.log", LOG_PATH, yymmdd);
	struct stat filestat;
	if (stat(logfilename, &filestat) != -1 && filestat.st_size > MAX_LOGFILE_SIZE)
	{
		char newlogfilename[0x20] = { 0 };
		sprintf(newlogfilename, "%s.bak", logfilename);
		remove(newlogfilename);
		rename(logfilename, newlogfilename);
	}
	FILE *fp;
	if ((fp = fopen(logfilename, "a+")) == NULL)
		return NULL;
	return fp;
}

/** 是否为后台进程. */
int logger_isdaemon()
{
	return lo.ppid == 1 ? 0 : 1;
}

/** 设置日志级别到TRACE. */
void logger_set2trace()
{
	logger_setlevel(LOG_LEVEL_TRACE);
}

/** 设置日志级别到DEBUG. */
void logger_set2debug()
{
	logger_setlevel(LOG_LEVEL_DEBUG);
}

/** 设置日志级别到INFO. */
void logger_set2info()
{
	logger_setlevel(LOG_LEVEL_INFO);
}

/** 设置日志级别到WARN. */
void logger_set2warn()
{
	logger_setlevel(LOG_LEVEL_WARN);
}

/** 设置日志级别到ERROR. */
void logger_set2error()
{
	logger_setlevel(LOG_LEVEL_ERROR);
}

/** 设置日志级别到FAULT. */
void logger_set2fault()
{
	logger_setlevel(LOG_LEVEL_FAULT);
}

void logger_setlevel(int le)
{
	if (le <= LOG_LEVEL_FAULT && le >= LOG_LEVEL_TRACE)
		lo.level = le;
}

/*--------------------------------------------------------------------*/
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/** TRACE是否可写. */
int logger_istrace()
{
	return (lo.level <= LOG_LEVEL_TRACE) ? 0 : 1;
}

/** DEBUG是否可写. */
int logger_isdebug()
{
	return (lo.level <= LOG_LEVEL_DEBUG) ? 0 : 1;
}

/** INFO是否可写. */
int logger_isinfo()
{
	return (lo.level <= LOG_LEVEL_INFO) ? 0 : 1;
}

/** WARN是否可写. */
int logger_iswarn()
{
	return (lo.level <= LOG_LEVEL_WARN) ? 0 : 1;
}

/** ERROR是否可写. */
int logger_iserror()
{
	return (lo.level <= LOG_LEVEL_ERROR) ? 0 : 1;
}

/** FAULT是否可写. */
int logger_isfault()
{
	return (lo.level <= LOG_LEVEL_FAULT) ? 0 : 1;
}

/** 函数与行是否可写. */
int logger_isenable(const char* fun, int line)
{
	int ret = 1;
	char key[0x80] = { 0 };
	sprintf(key, "%s%u", fun, line);
	pthread_mutex_lock(&lo.mutex);
	switch (lo.ed)
	{
	case LOG_ENABLE_ALL: /** 已使能全部. */
		ret = 0;
		break;
	case LOG_ENABLE_XXX:
		ret = chashstr_get(lo.lx, key, NULL); /** 已使能一部分, 找到即输出. */
		break;
	case LOG_DISABLE_ALL: /** 已使不能全部. */
		ret = 1;
		break;
	case LOG_DISABLE_XXX:
		ret = chashstr_get(lo.lx, key, NULL) == 0 ? 1 : 0; /** 已使不能一部分, 找不到即输出. */
		break;
	default:
		break;
	}
	pthread_mutex_unlock(&lo.mutex);
	return ret;
}

/** 设置函数与行可写. */
void logger_enable(const char* fun, int line)
{
	char key[0x80] = { 0 };
	sprintf(key, "%s%u", fun, line);
	pthread_mutex_lock(&lo.mutex);
	switch (lo.ed)
	{
	case LOG_ENABLE_ALL: /** 已使能全部, 无效操作. */
		break;
	case LOG_ENABLE_XXX: /** 已使能一部分, 追加. */
		chashstr_put(lo.lx, key, NULL);
		break;
	case LOG_DISABLE_ALL: /** 已使不能全部, 开启使能一部分, 追加. */
		lo.ed = LOG_ENABLE_XXX;
		chashstr_put(lo.lx, key, NULL);
		break;
	case LOG_DISABLE_XXX: /** 已使不能一部分, 移除. */
		chashstr_remove(lo.lx, key);
		break;
	default:
		break;
	}
	pthread_mutex_unlock(&lo.mutex);
}

/** 设置全部函数与行可写. */
void logger_enable_all()
{
	lo.ed = LOG_ENABLE_ALL;
	chashstr_remove_all(lo.lx);
}

/** 设置函数与行不可写. */
void logger_disable(const char* fun, int line)
{
	char key[0x80] = { 0 };
	sprintf(key, "%s%u", fun, line);
	pthread_mutex_lock(&lo.mutex);
	switch (lo.ed)
	{
	case LOG_ENABLE_ALL: /** 已使能全部, 开启使不能一部分, 追加. */
		lo.ed = LOG_DISABLE_XXX;
		chashstr_put(lo.lx, key, NULL);
		break;
	case LOG_ENABLE_XXX: /** 已使能一部分, 移除. */
		chashstr_remove(lo.lx, key);
		break;
	case LOG_DISABLE_ALL: /** 已使不能全部, 无效操作. */
		lo.ed = LOG_ENABLE_XXX;
		chashstr_put(lo.lx, key, NULL);
		break;
	case LOG_DISABLE_XXX: /** 已使不能一部分, 追加. */
		chashstr_put(lo.lx, key, NULL);
		break;
	default:
		break;
	}
	pthread_mutex_unlock(&lo.mutex);
}

/** 设置全部函数与行不可写. */
void logger_disable_all()
{
	lo.ed = LOG_DISABLE_ALL;
	chashstr_remove_all(lo.lx);
}

/*--------------------------------------------------------------------*/
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/** 当前时间: yyyy-mm-dd hh. */
char* logger_yyyy_mm_dd_hh_now()
{
	static char buff[0x0F];
	buff[0x0E] = 0;
	time_t now;
	time(&now);
	struct tm *t = localtime(&now);
	sprintf(buff, "%04d-%02d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour);
	return buff;
}

/** 当前时间: yyyy-mm-dd hh:mi:ss. */
char* logger_yyyy_mm_dd_hh_mi_ss_now()
{
	static char buff[0x14];
	buff[0x13] = 0;
	time_t now;
	time(&now);
	struct tm *t = localtime(&now);
	sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	return buff;
}

/** 当前时间: yyyy-mm-dd. */
char* logger_yyyy_mm_dd_now()
{
	static char buff[0x0B];
	buff[0x0A] = 0;
	time_t now;
	time(&now);
	struct tm *t = localtime(&now);
	sprintf(buff, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
	return buff;
}

/** 当前时间: yyyymm. */
char* logger_yyyymm()
{
	static char buff[0x07];
	buff[0x06] = 0;
	time_t now;
	time(&now);
	struct tm *t = localtime(&now);
	sprintf(buff, "%04d%02d", t->tm_year + 1900, t->tm_mon + 1);
	return buff;
}

/**last month.*/
char* logger_yyyymm_lm()
{
	static char buff[0x07];
	buff[0x06] = 0;
	time_t now;
	time(&now);
	struct tm *t = localtime(&now);
	int y = t->tm_year + 1900;
	int m = t->tm_mon + 1;
	if (m > 1)
		m -= 1;
	else
	{
		y -= 1;
		m = 12;
	}
	sprintf(buff, "%04d%02d", y, m);
	return buff;
}

/** 当前时间: hh:mi:ss. */
char* logger_hhmiss()
{
	static char buff[0x09];
	buff[0x08] = 0;
	time_t now;
	time(&now);
	struct tm *t = localtime(&now);
	strftime(buff, 0x10, "%X", t);
	return buff;
}

/** 当前时间: hh:mi:ss.mse. */
char* logger_hhmissmse()
{
	static char buff[0x0D];
#if defined(WIN32) || defined(_WIN32)
	SYSTEMTIME t;
	GetLocalTime(&t);
	sprintf(buff, "%02d:%02d:%02d.%03d", t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	struct tm *t = localtime((time_t*) &(tv.tv_sec));
	sprintf(buff, "%02d:%02d:%02d.%03d", t->tm_hour, t->tm_min, t->tm_sec, (int) (tv.tv_usec / 1000));
#endif
	return buff;
}
