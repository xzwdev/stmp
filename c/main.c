/*
 * main.c
 *
 *  Created on: 2013-8-26
 *      Author: xuzewen
 */

#include "libmisc.h"

int main(int argc, char **argv)
{
	logger_init();
	/*-------------------------*/
	/*                         */
	/*         基本信息                      */
	/*                         */
	/*-------------------------*/
	stmp_pdu base = { STMP_PDU, { } };
	stmpenc_add_str(&base, STMP_TAG_EMAIL, (char*) "xzwdev@qq.com");
	stmpenc_add_str(&base, STMP_TAG_PASSWORD, (char*) "password");
	stmpenc_add_str(&base, STMP_TAG_NAME, (char*) "stmp");
	/*-------------------------*/
	/*                         */
	/*         主机信息                       */
	/*                         */
	/*-------------------------*/
	stmp_pdu host = { STMP_PDU, { } };
	stmpenc_add_short(&host, STMP_TAG_PORT, 8080);
	stmpenc_add_str(&host, STMP_TAG_IP, (char*) "127.0.0.1");
	stmpenc_add_str(&host, STMP_TAG_HOST_NAME, (char*) "stmp.domain");
	/*-------------------------*/
	/*                         */
	/*         业务层                            */
	/*                         */
	/*-------------------------*/
	stmp_pdu usr = { STMP_PDU, { } };
	stmpenc_add_bin(&usr, STMP_TAG_HOST, host.buff + host.rm, STMP_PDU - host.rm);
	stmpenc_add_bin(&usr, STMP_TAG_BASE, base.buff + base.rm, STMP_PDU - base.rm);
	/*-------------------------*/
	/*                         */
	/*         事务层                            */
	/*                         */
	/*-------------------------*/
	stmp_pdu begin = { STMP_PDU, { } };
	stmpenc_add_bin(&begin, STMP_TAG_USERINFO, usr.buff + usr.rm, STMP_PDU - usr.rm);
	//
	uint stid = 0xBEEFBEEF;
	stmpenc_add_int(&begin, STMP_TAG_STID, stid);
	stmpenc_add_tag(&begin, STMP_TAG_TRANS_BEGIN);
	//
	stmpdec_printpdu(&begin);
	return EXIT_SUCCESS;
}
