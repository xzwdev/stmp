/*
 * util.h
 *
 *  Created on: 2011-3-21
 *      Author: xuzewen
 */

#ifndef UTIL_H_
#define UTIL_H_

#if !defined (__LIBMISC_H__) && !defined (__LIBMISC__)
#error only libmisc.h can be included directly.
#endif

#include "macro.h"

LIBMISC_BEGIN_DECLS

/** 将字节流(dat)以大写16进制格式打印到str中, 无换行, 带空格. */
LIBMISC_EXPORT void m_hex2str0(unsigned char* dat, int length, char* str);

/** 将字节流(dat)以大写16进制格式打印到str中, 无换行, 无空格. */
LIBMISC_EXPORT void m_hex2str1(unsigned char* dat, int length, char* str);

/** 大写16进制整形字符串(一定是8字节, 如"FFFFFFFF")转换成整形. */
LIBMISC_EXPORT unsigned int m_hexstr2int(char* hex);

/** 整形转换成16进制字符串. */
LIBMISC_EXPORT void m_int2hexstr(unsigned int i, char* str);

/** 字节转换成可见字符, 如果不可转换, 置为'.'. */
LIBMISC_EXPORT char m_b2c(unsigned char chr);

/** 将字节流(dat)以经典大写16进制格式打印到标准输出. */
LIBMISC_EXPORT void m_printhex(unsigned char *dat, unsigned int length);

/** 将字节流(dat)以经典大写16进制格式打印到str. */
LIBMISC_EXPORT void m_printhex2str(unsigned char* dat, unsigned int length, char* str);

/** 将BCD编码转换成字符串形式. */
LIBMISC_EXPORT void m_bcd2str(unsigned char* dat, int length, char* str);

/** 将mobile identity转换成字符串形式,  见: 3GPP TS 24.008 10.5.1.4. */
LIBMISC_EXPORT void m_mi2str(unsigned char* mi, int length, char* str);

/** 将access point name转换成字符串形式, 见: 3GPP TS 23.003.  */
LIBMISC_EXPORT void m_apn2str(unsigned char* apn, int length, char* str);

/** 将小区ID转换成字符串形式. */
LIBMISC_EXPORT int m_cellid(unsigned char *cell, int len, char* str);

/** gettimeofday, 第二个参数永远置为NULL. */
LIBMISC_EXPORT void m_gettimeofday(struct timeval* tv, void* nll);

/** 返回当前时间戳, 微秒. */
LIBMISC_EXPORT unsigned long long int m_getts();

/** 返回两个时间点相差的微秒数, now应该大于old. */
LIBMISC_EXPORT int m_getelap(struct timeval* now, struct timeval* old);

/** 随机一个整形随机数. */
LIBMISC_EXPORT unsigned int m_randomint();

/** 生成一个128bit的随机数. */
LIBMISC_EXPORT void m_random128(unsigned char* r128);

/** 生成一个256位的随机数. */
LIBMISC_EXPORT void m_random256(unsigned char* r256);

/** 生成一个512位的随机数. */
LIBMISC_EXPORT void m_random512(unsigned char* r512);

/** 产生一个256位随机key, 内容为随机的 0 ~ 9, a ~ z, A ~ Z, _. */
LIBMISC_EXPORT void m_gen_0aA_key256(unsigned char* key);

/** 返回全路径文件中的文件名及对应的size(不超过4G). */
LIBMISC_EXPORT int m_getfileatt(char* path, char* name, unsigned long long int* size);

/** 毫秒级睡眠. */
LIBMISC_EXPORT void m_sleep(int mec);

LIBMISC_END_DECLS

#endif /* UTIL_H_ */
