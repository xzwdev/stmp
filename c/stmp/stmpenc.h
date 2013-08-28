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

LIBMISC_BEGIN_DECLS

/** 向sp添加一个uchar值, t一定是一个简单体. */
LIBMISC_EXPORT void stmpenc_add_char(stmp_pdu* sp, ushort t, uchar v);

/** 向sp添加一个字符串值, t一定是一个简单体. */
LIBMISC_EXPORT void stmpenc_add_str(stmp_pdu* sp, ushort t, char* v);

/** 向sp添加一个ushort值, t一定是一个简单体. */
LIBMISC_EXPORT void stmpenc_add_short(stmp_pdu* sp, ushort t, ushort v);

/** 向sp添加一个uint值, t一定是一个简单体. */
LIBMISC_EXPORT void stmpenc_add_int(stmp_pdu* sp, ushort t, uint v);

/** 向sp添加一个ullong值, t一定是一个简单体. */
LIBMISC_EXPORT void stmpenc_add_long(stmp_pdu* sp, ushort t, ullong v);

/** 向sp添加一串二制值. */
LIBMISC_EXPORT void stmpenc_add_bin(stmp_pdu* sp, ushort t, uchar* v, uint l);

/** 向sp添加一个构造体tag. */
LIBMISC_EXPORT void stmpenc_add_tag(stmp_pdu* sp, ushort t);

/** 记住sp的当前位置, 将从这里准备开始添加一个子构造体的信元(这些信元必需都是简单体). */
LIBMISC_EXPORT void stmpenc_set_point(stmp_pdu* sp);

/** 向sp添加一个构造体tag, stmpenc_set_point总是应该在此函数之前调用. */
LIBMISC_EXPORT void stmpenc_add_tag4point(stmp_pdu* sp, ushort t);

/** 重置stmp_pdu, 以便重新填充内容. */
LIBMISC_EXPORT void stmpenc_reset(stmp_pdu* sp);

LIBMISC_END_DECLS

#endif /* STMPENC_H_ */
