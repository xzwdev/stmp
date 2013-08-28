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
		StmpPdu begin = new StmpPdu();
		/** ------------------------- */
		/**                           */
		/** 主机信息 */
		/**                           */
		/** ------------------------- */
		StmpEnc.addShort(begin, Stmp.STMP_TAG_PORT, (short) 8080);
		StmpEnc.addStr(begin, Stmp.STMP_TAG_IP, "127.0.0.1");
		StmpEnc.addStr(begin, Stmp.STMP_TAG_HOST_NAME, "stmp.domain");
		StmpEnc.addTag(begin, Stmp.STMP_TAG_HOST);
		/** ------------------------- */
		/**                           */
		/** 基本信息 */
		/**                           */
		/** ------------------------- */
		for (int i = 0; i < 0x04; ++i)
		{
			StmpEnc.setPoint(begin);
			StmpEnc.addStr(begin, Stmp.STMP_TAG_EMAIL, "xzwdev@qq.com");
			StmpEnc.addStr(begin, Stmp.STMP_TAG_PASSWORD, "password");
			StmpEnc.addStr(begin, Stmp.STMP_TAG_NAME, "stmp");
			StmpEnc.addTag4Point(begin, Stmp.STMP_TAG_BASE);
		}
		/** ------------------------- */
		/**                           */
		/** 业务层 */
		/**                           */
		/** ------------------------- */
		StmpEnc.addTag(begin, Stmp.STMP_TAG_USERINFO);
		/** ------------------------- */
		/**                           */
		/** 事务层 */
		/**                           */
		/** ------------------------- */
		int stid = 0xBEEFBEEF;
		StmpEnc.addInt(begin, Stmp.STMP_TAG_STID, stid);
		StmpEnc.addTag(begin, Stmp.STMP_TAG_TRANS_BEGIN);
		System.out.println(begin);
	}
}
