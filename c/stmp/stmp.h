/*
 * stmp.h
 *
 *  Created on: 2013-8-26
 *      Author: xuzewen
 */

#ifndef STMP_H_
#define STMP_H_

#if !defined (__LIBMISC_H__) && !defined (__LIBMISC__)
#error only libmisc.h can be included directly.
#endif

#include "../macro.h"
#include "../logger.h"
#include "../util.h"

LIBMISC_BEGIN_DECLS

typedef struct
{
	ushort t;
	uint l;
	uchar* v;
} tlv;

typedef struct
{
	int rm;
	uint p;
#define STMP_PDU									0x1000
	uchar buff[STMP_PDU];
} stmp_pdu;

/*-----------------------------------------------------*/
/*                                                     */
/*                      事务部分                                                               */
/*                                                     */
/*-----------------------------------------------------*/
#define STMP_TAG_TRANS_BEGIN								0x60		/** 事务开始. */
#define STMP_TAG_TRANS_END									0x61		/** 事务结束. */
#define STMP_TAG_TRANS_CONTINUE								0x62		/** 事务继续. */
#define STMP_TAG_TRANS_SWITCH								0x63		/** 消息前转. */
#define STMP_TAG_TRANS_ABORT								0x64		/** 事务中断. */
#define STMP_TAG_TRANS_CANCEL								0x65		/** 事务取消. */
#define STMP_TAG_TRANS_UNI									0x66		/** 单向消息. */
/*-----------------------------------------------------*/
/*                                                     */
/*                      一般信元                                                               */
/*                                                     */
/*-----------------------------------------------------*/
#define STMP_TAG_STID										0x00		/** 源事务ID. */
#define STMP_TAG_DTID										0x01		/** 目的事务ID. */
#define STMP_TAG_RET										0x02		/** 返回值. */
#define STMP_TAG_REASON										0x03		/** 原因值. */
#define STMP_TAG_STATUS										0x04		/** 状态. */
#define STMP_TAG_SIZE										0x05		/** 尺寸/长度. */
#define STMP_TAG_DAT										0x06		/** 内容/数据. */
#define STMP_TAG_NAME										0x07		/** 名称. */
#define STMP_TAG_CALLING									0x08		/** 主叫. */
#define STMP_TAG_CALLED										0x09		/** 被叫. */
#define STMP_TAG_TYPE										0x0A		/** 类型. */
#define STMP_TAG_FORMAT										0x0B		/** 格式. */
#define STMP_TAG_Z											0x0C		/** 压缩标志. */
#define STMP_TAG_KEY										0x0D		/** KEY. */
#define STMP_TAG_TIMESTAMP									0x0E		/** 时间戳. */
#define STMP_TAG_STIMESTAMP									0x0F		/** 开始时间戳. */
#define STMP_TAG_ETIMESTAMP									0x10		/** 结束时间戳. */
#define STMP_TAG_IP											0x11		/** IP地址. */
#define STMP_TAG_SOURCE_IP									0x12		/** 源IP. */
#define STMP_TAG_DEST_IP									0x13		/** 目的IP. */
#define STMP_TAG_PORT										0x14		/** 端口. */
#define STMP_TAG_SOURCE_PORT								0x15		/** 源端口. */
#define STMP_TAG_DEST_PORT									0x16		/** 目的端口. */
#define STMP_TAG_HOST_NAME									0x17		/** 主机名称. */
#define STMP_TAG_EMAIL										0x18		/** 邮箱. */
#define STMP_TAG_SEX										0x19		/** 性别. */
#define STMP_TAG_TEL										0x1A		/** 电话. */
#define STMP_TAG_PASSWORD									0x1B		/** 密码. */
//
#define STMP_TAG_USERINFO									0x70		/** 用户信息. */
#define STMP_TAG_HOST										0x71		/** 主机信息. */
#define STMP_TAG_BASE										0x72		/** 基本信息. */

/** 返回tag的字符串描述形式. */
LIBMISC_EXPORT char* stmp_tag_desc(ushort t);

/** 获得len导致的length字段的长度. */
LIBMISC_EXPORT unsigned char stmp_tlv_len(uint len);

#include "stmpenc.h"
#include "stmpdec.h"

LIBMISC_END_DECLS

#endif /* STMP_H_ */
