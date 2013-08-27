/*
 * stmpenc.h
 *
 *  Created on: 2013-8-26
 *      Author: xuzewen
 */

#ifndef STMPENC_H_
#define STMPENC_H_

#if !defined (__LIBMISC_H__) && !defined (__LIBMISC__)
#error only libmisc.h can be included directly.
#endif

#include "stmp.h"

/** 向eb添加一个uchar值, t一定是一个简单体. */
void stmpenc_add_char(stmp_pdu* sp, ushort t, uchar v);

/** 向eb添加一个字符串值, t一定是一个简单体. */
void stmpenc_add_str(stmp_pdu* sp, ushort t, char* v);

/** 向eb添加一个ushort值, t一定是一个简单体. */
void stmpenc_add_short(stmp_pdu* sp, ushort t, ushort v);

/** 向eb添加一个uint值, t一定是一个简单体. */
void stmpenc_add_int(stmp_pdu* sp, ushort t, uint v);

/** 向eb添加一个ullong值, t一定是一个简单体. */
void stmpenc_add_long(stmp_pdu* sp, ushort t, ullong v);

/** 向eb添加一串二制值. */
void stmpenc_add_bin(stmp_pdu* sp, ushort t, uchar* v, uint l);

/** 向eb添加一个构造体tag. */
void stmpenc_add_tag(stmp_pdu* sp, ushort t);

/** 重置stmp_pdu, 以便重新填充内容. */
void stmpenc_reset(stmp_pdu* sp);

#endif /* STMPENC_H_ */
