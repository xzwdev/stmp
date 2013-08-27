/*
 * stmp.c
 *
 *  Created on: 2013-8-26
 *      Author: xuzewen
 */

#include "stmp.h"

typedef struct
{
	ushort t;
	char d[0x20];
} stmp_ieis; /** 信元描述. */

/** 事务部分. */
static stmp_ieis __t_ieis__[] = { //
		/**0x60*/{ STMP_TAG_TRANS_BEGIN, "TRANS_BEGIN" },
		/**0x61*/{ STMP_TAG_TRANS_END, "TRANS_END" },
		/**0x62*/{ STMP_TAG_TRANS_CONTINUE, "TRANS_CONTINUE" },
		/**0x63*/{ STMP_TAG_TRANS_SWITCH, "TRANS_SWITCH" },
		/**0x64*/{ STMP_TAG_TRANS_ABORT, "TRANS_ABORT" },
		/**0x65*/{ STMP_TAG_TRANS_CANCEL, "TRANS_CANCEL" },
		/**0x66*/{ STMP_TAG_TRANS_UNI, "TRANS_UNI" }, };

/** 一般信元, 简单体. */
static stmp_ieis __gs_ieis__[] = { //
		/**0x00*/{ STMP_TAG_STID, "STID" },
		/**0x01*/{ STMP_TAG_STID, "DTID" },
		/**0x02*/{ STMP_TAG_RET, "RET" },
		/**0x03*/{ STMP_TAG_REASON, "REASON" },
		/**0x04*/{ STMP_TAG_STATUS, "STATUS" },
		/**0x05*/{ STMP_TAG_SIZE, "SIZE" },
		/**0x06*/{ STMP_TAG_DAT, "DAT" },
		/**0x07*/{ STMP_TAG_NAME, "NAME" },
		/**0x08*/{ STMP_TAG_CALLING, "CALLING" },
		/**0x09*/{ STMP_TAG_CALLED, "CALLED" },
		/**0x0A*/{ STMP_TAG_TYPE, "TYPE" },
		/**0x0B*/{ STMP_TAG_FORMAT, "FORMAT" },
		/**0x0C*/{ STMP_TAG_Z, "Z" },
		/**0x0D*/{ STMP_TAG_KEY, "KEY" },
		/**0x0E*/{ STMP_TAG_TIMESTAMP, "TIMESTAMP" },
		/**0x0F*/{ STMP_TAG_STIMESTAMP, "STIMESTAMP" },
		/**0x10*/{ STMP_TAG_ETIMESTAMP, "ETIMESTAMP" },
		/**0x11*/{ STMP_TAG_IP, "IP" },
		/**0x12*/{ STMP_TAG_SOURCE_IP, "SOURCE_IP" },
		/**0x13*/{ STMP_TAG_DEST_IP, "DEST_IP" },
		/**0x14*/{ STMP_TAG_PORT, "PORT" },
		/**0x15*/{ STMP_TAG_SOURCE_PORT, "SOURCE_PORT" },
		/**0x16*/{ STMP_TAG_DEST_PORT, "DEST_PORT" },
		/**0x17*/{ STMP_TAG_HOST_NAME, "HOST_NAME" },
		/**0x18*/{ STMP_TAG_EMAIL, "EMAIL" },
		/**0x19*/{ STMP_TAG_SEX, "SEX" },
		/**0x1A*/{ STMP_TAG_TEL, "TEL" },
		/**0x1B*/{ STMP_TAG_PASSWORD, "PASSWORD" } };

/** 一般信元, 构造体. */
static stmp_ieis __gc_ieis__[] = { //
		/**0x70*/{ STMP_TAG_USERINFO, "USERINFO" },
		/**0x71*/{ STMP_TAG_HOST, "HOST" },
		/**0x72*/{ STMP_TAG_BASE, "BASE" } };

static const char* __STMP_IU__ = "IEI_UNKNOWN";

/** 返回tag的字符串表现形式, 用于日志. */
char* stmp_tag_desc(ushort t)
{
	/*-------------------------*/
	/*                         */
	/*         事务部分                      */
	/*                         */
	/*-------------------------*/
	if (t >= STMP_TAG_TRANS_BEGIN && t < STMP_TAG_TRANS_UNI)
		return __t_ieis__[t - STMP_TAG_TRANS_BEGIN].d;
	/*-------------------------*/
	/*                         */
	/*         一般信元                      */
	/*                         */
	/*-------------------------*/
	if (t <= STMP_TAG_PASSWORD)
		return __gs_ieis__[t].d;
	if (t <= STMP_TAG_BASE)
		return __gc_ieis__[t - STMP_TAG_USERINFO].d;
	return (char*) __STMP_IU__;
}

/** 获得len影响的l字段的长度, 可能的返回值是1, 表示l只需一个字表示, 3, 表示需两个字节表示(ushort), 5, 表示需4个字节表示(uint). */
unsigned char stmp_tlv_len(uint len)
{
	return len < 0x000000FE ? 1 : (len <= 0x0000FFFF ? 3 : 5);
}
