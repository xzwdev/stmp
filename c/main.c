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
	stmp_pdu begin = { STMP_PDU, 0, { } };
	/*-------------------------*/
	/*                         */
	/*         主机信息                       */
	/*                         */
	/*-------------------------*/
	stmpenc_add_short(&begin, STMP_TAG_PORT, 8080);
	stmpenc_add_str(&begin, STMP_TAG_IP, (char*) "127.0.0.1");
	stmpenc_add_str(&begin, STMP_TAG_HOST_NAME, (char*) "stmp.domain");
	stmpenc_add_tag(&begin, STMP_TAG_HOST);
	/*-------------------------*/
	/*                         */
	/*         基本信息                      */
	/*                         */
	/*-------------------------*/
	int i = 0;
	for (; i < 0x04; ++i)
	{
		stmpenc_set_point(&begin);
		stmpenc_add_str(&begin, STMP_TAG_EMAIL, (char*) "xzwdev@qq.com");
		stmpenc_add_str(&begin, STMP_TAG_PASSWORD, (char*) "password");
		stmpenc_add_str(&begin, STMP_TAG_NAME, (char*) "stmp");
		stmpenc_add_tag4point(&begin, STMP_TAG_BASE);
	}
	/*-------------------------*/
	/*                         */
	/*         业务层                            */
	/*                         */
	/*-------------------------*/
	stmpenc_add_tag(&begin, STMP_TAG_USERINFO);
	/*-------------------------*/
	/*                         */
	/*         事务层                            */
	/*                         */
	/*-------------------------*/
	//
	uint stid = 0xBEEFBEEF;
	stmpenc_add_int(&begin, STMP_TAG_STID, stid);
	stmpenc_add_tag(&begin, STMP_TAG_TRANS_BEGIN);
	//
	stmpdec_printpdu(&begin);
	return EXIT_SUCCESS;
}
