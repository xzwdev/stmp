/*
 * stmpenc.c
 *
 *  Created on: 2013-8-26
 *      Author: xuzewen
 */

#include "stmpenc.h"

const uchar __STMP_LEN_0xFE__ = 0xFE;
const uchar __STMP_LEN_0xFF__ = 0xFF;

void stmpenc_add_char(stmp_pdu* sp, ushort t, uchar v)
{
	stmpenc_add_bin(sp, t, &v, 1);
}

void stmpenc_add_str(stmp_pdu* sp, ushort t, char* v)
{
	stmpenc_add_bin(sp, t, (uchar*) v, strlen(v));
}

void stmpenc_add_short(stmp_pdu* sp, ushort t, ushort v)
{
	ushort x = htons(v);
	stmpenc_add_bin(sp, t, (uchar*) &x, sizeof(ushort));
}

void stmpenc_add_int(stmp_pdu* sp, ushort t, uint v)
{
	uint x = htonl(v);
	stmpenc_add_bin(sp, t, (uchar*) &x, sizeof(uint));
}

void stmpenc_add_long(stmp_pdu* sp, ushort t, ullong v)
{
	uchar x[8];
	x[0] = (v >> 56) & 0xFF;
	x[1] = (v >> 48) & 0xFF;
	x[2] = (v >> 40) & 0xFF;
	x[3] = (v >> 32) & 0xFF;
	x[4] = (v >> 24) & 0xFF;
	x[5] = (v >> 16) & 0xFF;
	x[6] = (v >> 8) & 0xFF;
	x[7] = (v) & 0xFF;
	stmpenc_add_bin(sp, t, x, 8);
}

void stmpenc_add_bin(stmp_pdu* sp, ushort t, uchar* v, uint l)
{
	uchar ll = stmp_tlv_len(l);
	uchar tl;
	if (t & 0xFF00)
	{
		tl = 2;
		ushort tag = htons(t);
		sp->rm -= (ll + tl + l);
		memcpy(sp->buff + sp->rm, &tag, 2);
	} else
	{
		tl = 1;
		uchar tag = (uchar) t;
		sp->rm -= (ll + tl + l);
		memcpy(sp->buff + sp->rm, &tag, 1);
	}
	if (ll == 1)
	{
		uchar len = (uchar) l;
		memcpy(sp->buff + sp->rm + tl, &len, 1);
	} else if (ll == 3)
	{
		ushort len = htons(l);
		memcpy(sp->buff + sp->rm + tl, &__STMP_LEN_0xFE__, 1);
		memcpy(sp->buff + sp->rm + tl + 1, &len, 2);
	} else if (ll == 5)
	{
		uint len = htonl(l);
		memcpy(sp->buff + sp->rm + tl, &__STMP_LEN_0xFF__, 1);
		memcpy(sp->buff + sp->rm + tl + 1, &len, 4);
	}
	memcpy(sp->buff + sp->rm + tl + ll, v, l);
}

void stmpenc_add_tag(stmp_pdu* sp, ushort t)
{
	uint len = STMP_PDU - sp->rm;
	uchar ll = stmp_tlv_len(len);
	uchar tl;
	if (t & 0xFF00)
	{
		tl = 2;
		ushort tag = htons(t);
		sp->rm -= (ll + tl);
		memcpy(sp->buff + sp->rm, &tag, 2);
	} else
	{
		tl = 1;
		uchar tag = (uchar) t;
		sp->rm -= (ll + tl);
		memcpy(sp->buff + sp->rm, &tag, 1);
	}
	if (ll == 1)
	{
		uchar x = (uchar) len;
		memcpy(sp->buff + sp->rm + tl, &x, 1);
	} else if (ll == 3)
	{
		ushort x = htons(len);
		memcpy(sp->buff + sp->rm + tl, &__STMP_LEN_0xFE__, 1);
		memcpy(sp->buff + sp->rm + tl + 1, &x, 2);
	} else if (ll == 5)
	{
		uint x = htonl(len);
		memcpy(sp->buff + sp->rm + tl, &__STMP_LEN_0xFF__, 1);
		memcpy(sp->buff + sp->rm + tl + 1, &x, 4);
	}
}

void stmpenc_reset(stmp_pdu* sp)
{
	sp->rm = STMP_PDU;
}
