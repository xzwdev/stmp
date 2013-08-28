package cn.stmp.imp;

import java.util.HashMap;

/**
 * 
 * @author xuzewen
 * 
 */
public final class Stmp
{
	public static final int STMP_PDU = 0x1F000;
	public static final byte __STMP_LEN_0xFE__ = (byte) 0xFE;
	public static final byte __STMP_LEN_0xFF__ = (byte) 0xFF;
	/** ----------------------------------------------------- */
	/**                                                       */
	/** 事务部分 */
	/**                                                       */
	/** ----------------------------------------------------- */
	/** 事务开始. */
	public static final short STMP_TAG_TRANS_BEGIN = 0x60;
	/** 事务结束. */
	public static final short STMP_TAG_TRANS_END = 0x61;
	/** 事务继续. */
	public static final short STMP_TAG_TRANS_CONTINUE = 0x62;
	/** 消息前转. */
	public static final short STMP_TAG_TRANS_SWITCH = 0x63;
	/** 事务中断. */
	public static final short STMP_TAG_TRANS_ABORT = 0x64;
	/** 事务取消. */
	public static final short STMP_TAG_TRANS_CANCEL = 0x65;
	/** 单向消息. */
	public static final short STMP_TAG_TRANS_UNI = 0x66;
	/** ----------------------------------------------------- */
	/**                                                       */
	/** 一般信元 */
	/**                                                       */
	/** ----------------------------------------------------- */
	/** 源事务ID. */
	public static final short STMP_TAG_STID = 0x00;
	/** 目的事务ID. */
	public static final short STMP_TAG_DTID = 0x01;
	/** 返回值. */
	public static final short STMP_TAG_RET = 0x02;
	/** 原因值. */
	public static final short STMP_TAG_REASON = 0x03;
	/** 状态. */
	public static final short STMP_TAG_STATUS = 0x04;
	/** 尺寸/长度. */
	public static final short STMP_TAG_SIZE = 0x05;
	/** 内容/数据. */
	public static final short STMP_TAG_DAT = 0x06;
	/** 名称. */
	public static final short STMP_TAG_NAME = 0x07;
	/** 主叫. */
	public static final short STMP_TAG_CALLING = 0x08;
	/** 被叫. */
	public static final short STMP_TAG_CALLED = 0x09;
	/** 类型. */
	public static final short STMP_TAG_TYPE = 0x0A;
	/** 格式. */
	public static final short STMP_TAG_FORMAT = 0x0B;
	/** 压缩标志. */
	public static final short STMP_TAG_Z = 0x0C;
	/** KEY. */
	public static final short STMP_TAG_KEY = 0x0D;
	/** 时间戳. */
	public static final short STMP_TAG_TIMESTAMP = 0x0E;
	/** 开始时间戳. */
	public static final short STMP_TAG_STIMESTAMP = 0x0F;
	/** 结束时间戳. */
	public static final short STMP_TAG_ETIMESTAMP = 0x10;
	/** IP地址. */
	public static final short STMP_TAG_IP = 0x11;
	/** 源IP. */
	public static final short STMP_TAG_SOURCE_IP = 0x12;
	/** 目的IP. */
	public static final short STMP_TAG_DEST_IP = 0x13;
	/** 端口. */
	public static final short STMP_TAG_PORT = 0x14;
	/** 源端口. */
	public static final short STMP_TAG_SOURCE_PORT = 0x15;
	/** 目的端口. */
	public static final short STMP_TAG_DEST_PORT = 0x16;
	/** 主机名称. */
	public static final short STMP_TAG_HOST_NAME = 0x17;
	/** 邮箱. */
	public static final short STMP_TAG_EMAIL = 0x18;
	/** 性别. */
	public static final short STMP_TAG_SEX = 0x19;
	/** 电话. */
	public static final short STMP_TAG_TEL = 0x1A;
	/** 密码. */
	public static final short STMP_TAG_PASSWORD = 0x1B;
	//
	/** 用户信息. */
	public static final short STMP_TAG_USERINFO = 0x70;
	/** 主机信息. */
	public static final short STMP_TAG_HOST = 0x71;
	/** 基本信息. */
	public static final short STMP_TAG_BASE = 0x72;

	/** ----------------------------------------------------- */
	/**                                                       */
	/**  */
	/**                                                       */
	/** ----------------------------------------------------- */
	private static final HashMap<Short, String> tags = new HashMap<Short, String>();

	static
	{
		tags.put(Stmp.STMP_TAG_TRANS_BEGIN, "TRANS_BEGIN");
		tags.put(Stmp.STMP_TAG_TRANS_END, "TRANS_END");
		tags.put(Stmp.STMP_TAG_TRANS_CONTINUE, "TRANS_CONTINUE");
		tags.put(Stmp.STMP_TAG_TRANS_SWITCH, "TRANS_SWITCH");
		tags.put(Stmp.STMP_TAG_TRANS_ABORT, "TRANS_ABORT");
		tags.put(Stmp.STMP_TAG_TRANS_CANCEL, "TRANS_CANCEL");
		tags.put(Stmp.STMP_TAG_TRANS_UNI, "TRANS_UNI");
		//
		tags.put(Stmp.STMP_TAG_STID, "STID");
		tags.put(Stmp.STMP_TAG_DTID, "DTID");
		tags.put(Stmp.STMP_TAG_RET, "RET");
		tags.put(Stmp.STMP_TAG_REASON, "REASON");
		tags.put(Stmp.STMP_TAG_STATUS, "STATUS");
		tags.put(Stmp.STMP_TAG_SIZE, "SIZE");
		tags.put(Stmp.STMP_TAG_DAT, "DAT");
		tags.put(Stmp.STMP_TAG_NAME, "NAME");
		tags.put(Stmp.STMP_TAG_CALLING, "CALLING");
		tags.put(Stmp.STMP_TAG_CALLED, "CALLED");
		tags.put(Stmp.STMP_TAG_TYPE, "TYPE");
		tags.put(Stmp.STMP_TAG_FORMAT, "FORMAT");
		tags.put(Stmp.STMP_TAG_Z, "Z");
		tags.put(Stmp.STMP_TAG_KEY, "KEY");
		tags.put(Stmp.STMP_TAG_TIMESTAMP, "TIMESTAMP");
		tags.put(Stmp.STMP_TAG_STIMESTAMP, "STIMESTAMP");
		tags.put(Stmp.STMP_TAG_ETIMESTAMP, "ETIMESTAMP");
		tags.put(Stmp.STMP_TAG_IP, "IP");
		tags.put(Stmp.STMP_TAG_SOURCE_IP, "SOURCE_IP");
		tags.put(Stmp.STMP_TAG_DEST_IP, "DEST_IP");
		tags.put(Stmp.STMP_TAG_PORT, "PORT");
		tags.put(Stmp.STMP_TAG_SOURCE_PORT, "SOURCE_PORT");
		tags.put(Stmp.STMP_TAG_DEST_PORT, "DEST_PORT");
		tags.put(Stmp.STMP_TAG_HOST_NAME, "HOST_NAME");
		tags.put(Stmp.STMP_TAG_EMAIL, "EMAIL");
		tags.put(Stmp.STMP_TAG_SEX, "SEX");
		tags.put(Stmp.STMP_TAG_TEL, "TEL");
		tags.put(Stmp.STMP_TAG_PASSWORD, "PASSWORD");
		//
		tags.put(Stmp.STMP_TAG_USERINFO, "USERINFO");
		tags.put(Stmp.STMP_TAG_HOST, "HOST");
		tags.put(Stmp.STMP_TAG_BASE, "BASE");
	}

	/** 返回tag的字符串表现形式, 用于日志. */
	public static final String tagDesc(short t)
	{
		String desc = Stmp.tags.get(t);
		return desc == null ? "STMP_UNKNOWN" : desc;
	}

	/** 获得len影响的l字段的长度, 可能的返回值是1, 表示l只需一个字表示, 3, 表示需两个字节表示(ushort), 5, 表示需4个字节表示(uint). */
	public static final int tlvLen(int len)
	{
		return len < 0x000000FE ? 1 : (len <= 0x0000FFFF ? 3 : 5);
	}
}
