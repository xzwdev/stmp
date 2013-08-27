/*
 * util.c
 *
 *  Created on: 2011-3-21
 *      Author: xuzewen
 */

#include "util.h"

/** 0 ~ 9, a ~ z, A ~ Z, _. */
static char __0aA__[] = { '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
/** 0 ~ F. */
static char __0F__[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

#ifdef WIN32
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS) || defined(__WATCOMC__)
#define DELTA_EPOCH_IN_USEC 11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_USEC 11644473600000000ULL
#endif
typedef unsigned __int64 u_int64_t;
static u_int64_t filetime_to_unix_epoch(const FILETIME *ft)
{
	u_int64_t res = (u_int64_t) ft->dwHighDateTime << 32;
	res |= ft->dwLowDateTime;
	res /= 10;
	res -= DELTA_EPOCH_IN_USEC;
	return (res);
}
#endif

/** 将字节流(dat)以大写16进制格式打印到str中, 无换行, 带空格. */
void m_hex2str0(unsigned char* dat, int length, char* str)
{
	int i = 0;
	for (; i < length; ++i)
	{
		str[i * 3 + 0] = __0F__[((dat[i] >> 4) & 0x0F)];
		str[i * 3 + 1] = __0F__[(dat[i] & 0x0F)];
		str[i * 3 + 2] = 0x20;
	}
	str[i * 3 - 1] = 0;
}

/** 将字节流(dat)以大写16进制格式打印到str中, 无换行, 无空格. */
void m_hex2str1(unsigned char* dat, int length, char* str)
{
	int i = 0;
	for (; i < length; ++i)
	{
		str[i * 2 + 0] = __0F__[((dat[i] >> 4) & 0x0F)];
		str[i * 2 + 1] = __0F__[(dat[i] & 0x0F)];
	}
}

/** 大写16进制整形字符串(一定是8字节, 如"FFFFFFFF")转换成整形. */
unsigned int m_hexstr2int(char* hex)
{
	unsigned int ret = 0x00;
	int i = 0;
	for (; i < 8; ++i)
		ret += (hex[i] < 65 ? hex[i] - 0x30 : (hex[i] < 97 ? hex[i] - 55 : hex[i] - 87)) << (7 - i) * 4;
	return ret;
}

/** 整形转换成16进制字符串. */
void m_int2hexstr(unsigned int i, char* str)
{
	str[0] = __0F__[((i >> 28) & 0x0F)];
	str[1] = __0F__[((i >> 24) & 0x0F)];
	str[2] = __0F__[((i >> 20) & 0x0F)];
	str[3] = __0F__[((i >> 16) & 0x0F)];
	str[4] = __0F__[((i >> 12) & 0x0F)];
	str[5] = __0F__[((i >> 8) & 0x0F)];
	str[6] = __0F__[((i >> 4) & 0x0F)];
	str[7] = __0F__[(i & 0x0F)];
}

/** 字节转换成可见字符, 如果不可转换, 置为'.'. */
char m_b2c(unsigned char chr)
{
	return (chr > 0x20 && chr < 0x7F) ? chr : '.';
}

/** 将字节流(dat)以经典大写16进制格式打印到标准输出. */
void m_printhex(unsigned char *dat, unsigned int length)
{
	int rows = length / 16;
	int ac = length % 16;
	int i;
	for (i = 0; i < rows; ++i)
		printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", dat[(16 * i) + 0], dat[(16 * i) + 1], dat[(16 * i) + 2], dat[(16 * i) + 3], dat[(16 * i) + 4], dat[(16 * i) + 5], dat[(16 * i) + 6], dat[(16 * i) + 7], dat[(16 * i) + 8], dat[(16 * i) + 9], dat[(16 * i) + 10], dat[(16 * i) + 11], dat[(16 * i) + 12], dat[(16 * i) + 13], dat[(16 * i) + 14], dat[(16 * i) + 15], m_b2c(dat[(16 * i) + 0]), m_b2c(dat[(16 * i) + 1]), m_b2c(dat[(16 * i) + 2]), m_b2c(dat[(16 * i) + 3]), m_b2c(dat[(16 * i) + 4]), m_b2c(dat[(16 * i) + 5]), m_b2c(dat[(16 * i) + 6]), m_b2c(dat[(16 * i) + 7]), m_b2c(dat[(16 * i) + 8]), m_b2c(dat[(16 * i) + 9]), m_b2c(dat[(16 * i) + 10]), m_b2c(dat[(16 * i) + 11]), m_b2c(dat[(16 * i) + 12]), m_b2c(dat[(16 * i) + 13]), m_b2c(dat[(16 * i) + 14]), m_b2c(dat[(16 * i) + 15]));
	for (i = 0; i < ac; i++)
		printf("%02X ", dat[rows * 16 + i]);
	for (i = 0; ac > 0 && i < 16 - ac; i++)
		printf("%s", "   ");
	for (i = 0; i < ac; i++)
		printf("%c", m_b2c(dat[rows * 16 + i]));
	printf("\n");
}

/** 将字节流(dat)以经典大写16进制格式打印到str. */
void m_printhex2str(unsigned char *dat, unsigned int length, char* str)
{
	int rows = length / 16;
	int ac = length % 16;
	int i;
	if (rows > 0)
	{
		for (i = 0; i < rows; ++i)
			sprintf(str + 0x41 * i, "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", dat[(16 * i) + 0], dat[(16 * i) + 1], dat[(16 * i) + 2], dat[(16 * i) + 3], dat[(16 * i) + 4], dat[(16 * i) + 5], dat[(16 * i) + 6], dat[(16 * i) + 7], dat[(16 * i) + 8], dat[(16 * i) + 9], dat[(16 * i) + 10], dat[(16 * i) + 11], dat[(16 * i) + 12], dat[(16 * i) + 13], dat[(16 * i) + 14], dat[(16 * i) + 15], m_b2c(dat[(16 * i) + 0]), m_b2c(dat[(16 * i) + 1]), m_b2c(dat[(16 * i) + 2]), m_b2c(dat[(16 * i) + 3]), m_b2c(dat[(16 * i) + 4]), m_b2c(dat[(16 * i) + 5]), m_b2c(dat[(16 * i) + 6]), m_b2c(dat[(16 * i) + 7]), m_b2c(dat[(16 * i) + 8]), m_b2c(dat[(16 * i) + 9]), m_b2c(dat[(16 * i) + 10]), m_b2c(dat[(16 * i) + 11]), m_b2c(dat[(16 * i) + 12]), m_b2c(dat[(16 * i) + 13]), m_b2c(dat[(16 * i) + 14]), m_b2c(dat[(16 * i) + 15]));
	}
	int offset = 0x41 * rows;
	if (ac != 0)
	{
		for (i = 0; i < 0x30 + ac; ++i)
			str[offset + i] = ' ';
		for (i = 0; i < ac; ++i)
		{
			sprintf(str + offset + (i * 3), "%02X ", dat[(rows * 16) + i]);
			sprintf(str + offset + (0x30 + i), "%c", m_b2c(dat[(rows * 16) + i]));
		}
		str[offset + (i * 3)] = 0x20;
		str[offset + (0x30 + i)] = '\n';
	}
}

/** BCD编码转换成字符串. */
void m_bcd2str(unsigned char* src, int length, char* str)
{
	int index = 0;
	int i = 0;
	for (; i < length; ++i)
	{
		unsigned char bit = (src[i] & 0xF);
		if (bit > 0x09)
			break;
		str[index++] = (bit + 0x30);
		bit = ((src[i] >> 0x04) & 0xF);
		if (bit > 0x09)
			break;
		str[index++] = (bit + 0x30);
	}
}

/** mobile identity转换成字符串,  见: 3GPP TS 24.008 10.5.1.4. */
void m_mi2str(unsigned char* mi, int length, char* str)
{
	unsigned char toi = mi[0] & 0x07;
	if (toi == 0x01 || toi == 0x02 || toi == 0x03)
	{
		str[0] = ((mi[0] >> 4) & 0x0F) + 0x30;
		int i = 1;
		for (; i < length; ++i)
		{
			unsigned char low = (mi[i] & 0x0F);
			unsigned char hig = ((mi[i] >> 0x04) & 0x0F);
			if (hig > 0x09)
			{
				str[i * 2 - 1] = low + 0x30;
				return;
			}
			str[i * 2 - 1] = low + 0x30;
			str[i * 2] = hig + 0x30;
		}
		return;
	}
}

/** access point name转换成字符串形式, 见: 3GPP TS 23.003.  */
void m_apn2str(unsigned char* apn, int length, char* str)
{
	if (apn[0] >= length)
		return;
	memcpy(str + strlen(str), apn + 1, apn[0]);
	if (length - 1 > apn[0])
	{
		sprintf(str + strlen(str), "%c", '.');
		m_apn2str(apn + apn[0] + 1, length - apn[0] - 1, str);
	}
}

/** 将小区ID转换成字符串形式. */
int m_cellid(unsigned char *cell, int len, char* str)
{
	short idx = 0, j = 0;
	unsigned short tmp = 0;
	for (; idx < len; idx++)
	{
		if (idx <= 2)
		{
			str[j++] = (cell[idx] & 0x0F) + '0';
			str[j++] = ((cell[idx] & 0xF0) >> 4) + '0';
		} else
		{
			str[j++] = '-';
			tmp = ((cell[idx] & 0xFF) << 8) + (cell[idx + 1] & 0xFF);
			idx++;
			sprintf(str + j, "%d", (tmp));
			j += strlen(str + j);
		}
	}
	str[3] = '-';
	str[j] = 0;
	return 0;
}

/** gettimeofday, 第二个参数永远置为NULL. */
void m_gettimeofday(struct timeval* tv, void* nll)
{
#ifdef WIN32
	FILETIME ft;
	u_int64_t tim;
	GetSystemTimeAsFileTime(&ft);
	tim = filetime_to_unix_epoch(&ft);
	tv->tv_sec = (long) (tim / 1000000ULL);
	tv->tv_usec = (long) (tim % 1000000ULL);
#else
	gettimeofday(tv, NULL);
#endif
}

/** 返回当前时间戳, 微秒. */
unsigned long long int m_getts()
{
	struct timeval tv;
	m_gettimeofday(&tv, NULL);
	unsigned long long int ts = tv.tv_sec;
	ts *= 1000000ULL;
	ts += tv.tv_usec;
	return ts;
}

/** 返回两个时间点相差的微秒数, now应该大于old. */
int m_getelap(struct timeval* now, struct timeval* old)
{
	long int sec = now->tv_sec - old->tv_sec;
	long int use = now->tv_usec - old->tv_usec;
	sec = use < 0 ? (sec > 0 ? sec - 1 : sec) : sec; /** 获得秒.*/
	use = use < 0 ? (1000000 - old->tv_usec + now->tv_usec) : (now->tv_usec - old->tv_usec);
	return (int) (sec * 1000000 + use);
}

/** 随机一个整形随机数. */
unsigned int m_randomint()
{
	return (((rand() & 0xFFFF) << 16) | (rand() & 0xFFFF)) * (((rand() & 0xFFFF) << 16) | (rand() & 0xFFFF));
}

/** 生成一个128bit的随机数. */
void m_random128(unsigned char* r128)
{
	int i = 0;
	unsigned int x = 0x00;
	for (; i < 4; ++i)
	{
		x = m_randomint();
		memcpy(r128 + (i * 4), &x, 4);
	}
}

/** 生成一个256位的随机数. */
void m_random256(unsigned char* r256)
{
	m_random128(r256);
	m_random128(r256 + 0x10);
}

/** 生成一个512位的随机数. */
void m_random512(unsigned char* r512)
{
	m_random256(r512);
	m_random256(r512 + 0x20);
}

/** 产生一个256位随机key, 内容为随机的 0 ~ 9, a ~ z, A ~ Z, _. */
void m_gen_0aA_key256(unsigned char* key)
{
	int i = 0;
	for (; i < 8; ++i)
	{
		unsigned int x = m_randomint();
		key[4 * i + 0] = __0aA__[(x) % sizeof(__0aA__)];
		key[4 * i + 1] = __0aA__[(x >> 0x08) % sizeof(__0aA__)];
		key[4 * i + 2] = __0aA__[(x >> 0x10) % sizeof(__0aA__)];
		key[4 * i + 3] = __0aA__[(x >> 0x18) % sizeof(__0aA__)];
	}
}

/** 返回全路径文件中的文件名及对应的size(不超过4G). */
int m_getfileatt(char* file, char* name, unsigned long long int* size)
{
	int i = strlen(file) - 1;
	int indx = -1;
	for (; i >= 0; --i)
	{
#ifdef WIN32
		if (file[i] == '\\')
#else
		if(file[i] == '/')
#endif
		{
			indx = i;
			break;
		}
	}
	if (name != NULL)
	{
		if (indx != -1)
			memcpy(name, file + indx + 1, strlen(file) - indx - 1);
		else
			memcpy(name, file, strlen(file));
	}
#ifdef WIN32
	struct _stati64 s64;
	if (_stati64(file, &s64) != 0)
		return -1;
	*size = s64.st_size;
	return 0;
#else
	struct stat x;
	if(stat(file, &x) != 0)
	return -1;
	*size = x.st_size;
	return 0;
#endif
}

/** 毫秒级睡眠. */
void m_sleep(int mec)
{
#ifdef WIN32
	Sleep(mec);
#else
	usleep(1000 * mec);
#endif
}
