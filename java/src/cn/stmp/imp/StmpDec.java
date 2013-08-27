package cn.stmp.imp;

import cn.stmp.util.Formatu;
import cn.stmp.util.Log;

/**
 * 
 * @author xuzewen
 * 
 */
public final class StmpDec
{
	/** 从dat中解析出一个stmp_node结构. */
	public static final StmpNode unpack(byte dat[])
	{
		StmpNode node = new StmpNode();
		return unpack__(dat, 0, dat.length, node) == 0 ? node : null;
	}

	/** 报文解析. */
	private static final int unpack__(byte dat[], int offset, int size, StmpNode node)
	{
		int ret = 1;
		int x[] = StmpDec.genTl(dat, offset, size);
		if (x == null)
			return ret;
		node.self.t = (short) x[0];
		node.self.l = x[3];
		if (((node.self.t & 0xFF00) != 0) ? ((node.self.t & 0x4000) != 0) : ((node.self.t & 0x40) != 0)) /** 构造体. */
		{
			node.c = new StmpNode();
			if (StmpDec.unpack__(dat, offset + x[1] + x[2], node.self.l, node.c) != 0)
				return ret;
		} else
		{
			node.self.v = new byte[node.self.l];
			System.arraycopy(dat, offset + x[1] + x[2], node.self.v, 0, node.self.v.length);
		}
		int cur = (x[1] + x[2] + node.self.l);
		int rem = size - cur;
		if (rem != 0)
		{
			node.s = new StmpNode();
			return StmpDec.unpack__(dat, offset + cur, rem, node.s);
		}
		return 0;
	}

	/** 获得tag(t), tag字段长度(tl), length字段长度(ll), value长度(l). */
	private static final int[] genTl(byte dat[], int offset, int size)
	{
		if (size < 2)
		{
			Log.error("without enough size for unpack tag-field and length-field, size: %08X, offset: %d\n", size, offset);
			return null;
		}
		int x[] = new int[4];
		if ((dat[offset] & 0x80) != 0)
		{
			if (size < 3)
			{
				Log.error("without enough size for unpack length-field, size: %08X\n", size);
				return null;
			}
			x[0] = (Formatu.byte2short(dat, offset) & 0x0000FFFF);
			x[1] = 2;
		} else
		{
			x[0] = (dat[offset] & 0x000000FF);
			x[1] = 1;
		}
		x[2] = (dat[offset + x[1]] == Stmp.__STMP_LEN_0xFE__ ? 3 : (dat[offset + x[1]] == Stmp.__STMP_LEN_0xFF__ ? 5 : 1));
		if (size < x[1] + x[2])
		{
			Log.error("without enough size for unpack length-field, size: %08X, tl: %02X, ll: %02X, offset: %d\n", size, (byte) x[1], (byte) x[2], offset);
			return null;
		}
		if (x[2] == 1) /** 一个字节表示长度. */
		{
			x[3] = (dat[offset + x[1]] & 0x000000FF);
			if (size < x[1] + x[2] + x[3])
			{
				Log.error("without enough size for unpack length-field, size: %08X, tl: %02X, ll: %02X, l: %02X, offset: %d\n", size, x[1], x[2], x[3], offset);
				return null;
			}
			return x;
		}
		if (x[2] == 3) /** 两个字节表示长度. */
		{
			x[3] = (Formatu.byte2short(dat, offset + x[1] + 1) & 0x0000FFFF);
			if (size < x[1] + x[2] + x[3])
			{
				Log.error("without enough size for unpack length-field, size: %08X, tl: %02X, ll: %02X, l: %02X, offset: %d\n", size, x[1], x[2], x[3], offset);
				return null;
			}
			return x;
		}
		if (x[2] == 5) /** 四个字节表示长度. */
		{
			/** limited 0x7FFFFFFF. */
			x[3] = (Formatu.byte2int(dat, offset + x[1] + 1) & 0x7FFFFFFF);
			if (size < x[1] + x[2] + x[3])
			{
				Log.error("without enough size for unpack length-field, size: %08X, tl: %02X, ll: %02X, l: %02X, offset: %d\n", size, x[1], x[2], x[3], offset);
				return null;
			}
			return x;
		}
		return null;
	}

	private static final void print(StmpNode node, StringBuilder strb, int space)
	{
		int i = 0;
		for (; i < space; ++i)
			strb.append(Formatu.printf2Str("%s", i == space - 1 ? " |" : " "));
		String tstr = Stmp.tagDesc(node.self.t);
		int ll = Stmp.tlvLen(node.self.t);
		if (((node.self.t & 0xFF00) != 0) ? ((node.self.t & 0x4000) != 0) : ((node.self.t & 0x40) != 0)) /** 构造体. */
		{
			space += 4;
			if (ll == 1)
				strb.append(Formatu.printf2Str(((node.self.t & 0xFF00) != 0) ? ("--%04X(%s)[%02X]\n") : ("----%02X(%s)[%02X]\n"), node.self.t, tstr, node.self.l));
			else if (ll == 3)
				strb.append(Formatu.printf2Str(((node.self.t & 0xFF00) != 0) ? ("--%04X(%s)[%04X]\n") : ("----%02X(%s)[%04X]\n"), node.self.t, tstr, node.self.l));
			else
				strb.append(Formatu.printf2Str(((node.self.t & 0xFF00) != 0) ? ("--%04X(%s)[%08X]\n") : ("----%02X(%s)[%08X]\n"), node.self.t, tstr, node.self.l));
			i = 0;
			for (; i < space; ++i)
				strb.append(Formatu.printf2Str("%s", i == space - 1 ? " |\n" : " "));
		} else
		{
			if (ll == 1)
				strb.append(Formatu.printf2Str(((node.self.t & 0xFF00) != 0) ? ("--%04X(%s)[%02X]={") : ("----%02X(%s)[%02X]={"), node.self.t, tstr, node.self.l));
			else if (ll == 3)
				strb.append(Formatu.printf2Str(((node.self.t & 0xFF00) != 0) ? ("--%04X(%s)[%04X]={") : ("----%02X(%s)[%04X]={"), node.self.t, tstr, node.self.l));
			else
				strb.append(Formatu.printf2Str(((node.self.t & 0xFF00) != 0) ? ("--%04X(%s)[%08X]={") : ("----%02X(%s)[%08X]={"), node.self.t, tstr, node.self.l));
			i = 0;
			for (; i < node.self.l; ++i)
			{
				if (i == node.self.l - 1)
					strb.append(Formatu.printf2Str("%02X", node.self.v[i]));
				else
					strb.append(Formatu.printf2Str("%02X ", node.self.v[i]));
			}
			strb.append(Formatu.printf2Str("%s", "}\n"));
			space += 4;
		}
		if (node.c != null)
			StmpDec.print(node.c, strb, space);
		if (node.s != null)
			StmpDec.print(node.s, strb, space - 4);
	}

	/** 打印一个节点到str. */
	public static final String printNode2Str(StmpNode node)
	{
		StringBuilder strb = new StringBuilder();
		StmpDec.print(node, strb, 0);
		return strb.toString();
	}

	/** 打印一个节点到标准输出. */
	public static final void printNode(StmpNode node)
	{
		System.out.println(StmpDec.printNode2Str(node));
	}

	/** 解包, 并打印到标准输出. */
	public static final void printf(byte by[])
	{
		System.out.println(StmpDec.print2Str(by));
	}

	/** 解包, 并打印到标准输出. */
	public static final void printPdu(StmpPdu pdu)
	{
		System.out.println(StmpDec.printPdu2Str(pdu));
	}

	/** 解包, 并打印到str. */
	public static final String print2Str(byte by[])
	{
		StringBuilder strb = new StringBuilder(Formatu.printBytes(by)).append("\n");
		StmpNode root = StmpDec.unpack(by);
		if (root != null)
			strb.append(StmpDec.printNode2Str(root));
		else
			Log.error("can not unpack this STMP PDU.\n");
		return strb.toString();
	}

	/** 解包, 并打印到str. */
	public static final String printPdu2Str(StmpPdu pdu)
	{
		byte by[] = new byte[Stmp.STMP_PDU - pdu.rm];
		System.arraycopy(pdu.buff, pdu.rm, by, 0, by.length);
		return StmpDec.print2Str(by);
	}
}
