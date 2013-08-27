package cn.stmp.main;

import cn.stmp.imp.Stmp;
import cn.stmp.imp.StmpEnc;
import cn.stmp.imp.StmpPdu;

/**
 * 
 * @author xuzewen
 * 
 */
public class Main
{
	public static void main(String[] args)
	{
		/** ------------------------- */
		/**                           */
		/** 基本信息 */
		/**                           */
		/** ------------------------- */
		StmpPdu base = new StmpPdu();
		StmpEnc.addStr(base, Stmp.STMP_TAG_EMAIL, "xzwdev@qq.com");
		StmpEnc.addStr(base, Stmp.STMP_TAG_PASSWORD, "password");
		StmpEnc.addStr(base, Stmp.STMP_TAG_NAME, "stmp");
		/** ------------------------- */
		/**                           */
		/** 主机信息 */
		/**                           */
		/** ------------------------- */
		StmpPdu host = new StmpPdu();
		StmpEnc.addShort(host, Stmp.STMP_TAG_PORT, (short) 8080);
		StmpEnc.addStr(host, Stmp.STMP_TAG_IP, "127.0.0.1");
		StmpEnc.addStr(host, Stmp.STMP_TAG_HOST_NAME, "stmp.domain");
		/** ------------------------- */
		/**                           */
		/** 业务层 */
		/**                           */
		/** ------------------------- */
		StmpPdu usr = new StmpPdu();
		StmpEnc.addPdu(usr, Stmp.STMP_TAG_HOST, host);
		StmpEnc.addPdu(usr, Stmp.STMP_TAG_BASE, base);
		/** ------------------------- */
		/**                           */
		/** 事务层 */
		/**                           */
		/** ------------------------- */
		StmpPdu begin = new StmpPdu();
		StmpEnc.addPdu(begin, Stmp.STMP_TAG_USERINFO, usr);
		//
		int stid = 0xBEEFBEEF;
		StmpEnc.addInt(begin, Stmp.STMP_TAG_STID, stid);
		StmpEnc.addTag(begin, Stmp.STMP_TAG_TRANS_BEGIN);
		//
		System.out.println(begin);
	}
}
