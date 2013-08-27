package cn.stmp.util;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.lang.reflect.Method;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.security.Key;
import java.security.MessageDigest;
import java.text.DecimalFormat;
import java.util.Random;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

/**
 * 格式化和一些杂项.
 * 
 * @author xuzewen
 * 
 */
public final class Formatu
{
	public static final String UTF_8 = "UTF-8";
	public static final String GBK = "GBK";
	public static final String ISO_8859_1 = "ISO-8859-1";
	public static final String COMMA = ",";
	public static final String COMMA2 = ";";
	public static final String SPACE = " ";
	public static final String LINE = "\n";
	public static final String LINE_R_N = "\r\n";
	public static final String _LINE = "_";
	public static final String UNIX_FILE_SEPARATOR = "/";
	public static final int SUCCESS = 0;
	public static final int FAILED = -1;
	public static final DecimalFormat df = new DecimalFormat("#0.00");
	private static final PrintStream out = new PrintStream(System.out);
	private static final Random rand = new Random();

	public static final String trim(String arg)
	{
		return arg == null ? null : ("".equals(arg.trim()) ? null : arg.trim());
	}

	/** 异常时返回-1. */
	public static final int int_1(String arg)
	{
		try
		{
			return Integer.parseInt(trim(arg));
		} catch (Exception e)
		{
			return -1;
		}
	}

	/** 异常时返回-1,否则值总是>=-1 */
	public static final int forceInt_1(String arg)
	{
		try
		{
			int value = Integer.parseInt(trim(arg));
			return value < -1 ? -1 : value;
		} catch (Exception e)
		{
			return -1;
		}
	}

	/** 异常时返回零. */
	public static final int int0(String arg)
	{
		try
		{
			return Integer.parseInt(trim(arg));
		} catch (Exception e)
		{
			return 0;
		}
	}

	/** 异常时返回零,否则值总是>=0 */
	public static final int forceInt0(String arg)
	{
		try
		{
			int value = Integer.parseInt(trim(arg));
			return value < 0 ? 0 : value;
		} catch (Exception e)
		{
			return 0;
		}
	}

	/** 异常时返回1. */
	public static final int int1(String arg)
	{
		try
		{
			return Integer.parseInt(trim(arg));
		} catch (Exception e)
		{
			return 1;
		}
	}

	/** 异常时返回1,否则值总是>=1 */
	public static final int forceInt1(String arg)
	{
		try
		{
			int value = Integer.parseInt(trim(arg));
			return value < 1 ? 1 : value;
		} catch (Exception e)
		{
			return 1;
		}
	}

	/** 判断字符串是否为NULL */
	public static final boolean isNull(String arg)
	{
		return Formatu.trim(arg) == null;
	}

	/** parse为一个byte. */
	public static final Byte parseByte(String arg)
	{
		try
		{
			return Byte.parseByte(trim(arg));
		} catch (Exception e)
		{
			return null;
		}
	}

	/** return URLEncoder.encode(str, UTF_8); */
	public static final String encode(String str)
	{
		try
		{
			return URLEncoder.encode(trim(str), UTF_8);
		} catch (Exception e)
		{
			return str;
		}
	}

	/** return URLDecoder.decode(str, UTF_8); */
	public static final String decode(String str)
	{
		try
		{
			return URLDecoder.decode(trim(str), UTF_8);
		} catch (Exception e)
		{
			return str;
		}
	}

	/** 是不是一串数字. */
	public static final boolean isDigital(String arg)
	{
		arg = trim(arg);
		if (arg == null)
			return false;
		char[] array = arg.toCharArray();
		for (char chr : array)
		{
			if (!Character.isDigit(chr))
				return false;
		}
		return true;
	}

	/** 两个字转换成short. */
	public static final short byte2short(byte by[], int offset)
	{
		int value = 0;
		for (int i = offset; i < offset + 2; i++)
			value += ((by[i] & 0xFF) << (8 * (2 - (i - offset) - 1)));
		return (short) value;
	}

	/** 四字节转换成int. */
	public static final int byte2int(byte by[], int offset)
	{
		int value = 0;
		for (int i = offset; i < offset + 4; i++)
			value += ((by[i] & 0xFF) << (8 * (4 - (i - offset) - 1)));
		return value;
	}

	/** 八字节转换成long. */
	public static final long byte2long(byte by[], int offset)
	{
		long value = 0;
		for (int i = offset; i < offset + 8; i++)
			value += (long) ((long) (by[i] & 0xFF)) << (8 * (8 - (i - offset) - 1));
		return value;
	}

	/** short转两字节, 小头在前. */
	public static final byte[] short2byte(short arg)
	{
		return new byte[] { (byte) ((arg >> 8) & 0xFF), (byte) (arg & 0xFF) };
	}

	/** int转四字节, 小头在前. */
	public static final byte[] int2byte(int arg)
	{
		byte by[] = new byte[4];
		for (int i = 0; i < 4; i++)
			by[i] = (byte) (arg >> (24 - i * 8));
		return by;
	}

	/** long转8字节, 小头在前. */
	public static final byte[] long2byte(long arg)
	{
		byte by[] = new byte[8];
		for (int i = 0; i < 8; i++)
			by[i] = (byte) (arg >> (56 - i * 8));
		return by;
	}

	/** 将int字节序倒换. */
	public static final int h2l_int(int h)
	{
		return ((h >> 24) & 0xFF) + ((((h >> 16) & 0xFF) << 8) & 0xFF00) + ((((h >> 8) & 0xFF) << 16) & 0xFF0000) + (((h & 0xFF) << 24) & 0xFF000000);
	}

	/** 将short字节序倒换. */
	public static final short h2l_short(short h)
	{
		return (short) (((h >> 8) & 0xFF) + (((h & 0xFF) << 8) & 0xFF00));
	}

	/** 0x字符串转换成实际的十六进制�?. */
	public static final int str2hex(String str)
	{
		char by[] = str.toCharArray();
		int value = 0;
		for (int i = 0; i < by.length; i++)
		{
			int bit = by[i] < 65 ? by[i] - 0x30 : (by[i] < 97 ? by[i] - 55 : by[i] - 87);
			value += (bit << (by.length - i - 1) * 4);
		}
		return value;
	}

	/** 替代c的printf. */
	public static final void printf(String format, Object... args)
	{
		out.printf(format, args);
	}

	/** 打印byte[]到标准输出. */
	public static final void printf(byte by[])
	{
		Formatu.printf(Formatu.printBytes(by, 0, by.length));
	}

	/** 打印byte[]到标准输出. */
	public static final void printf(byte by[], int offset, int length)
	{
		Formatu.printf(Formatu.printBytes(by, offset, length));
	}

	private static final char toc(byte chr)
	{
		return (chr > 0x20 && chr < 0x7F) ? (char) chr : '.';
	}

	/** 替代c的printf, 但将打印的结果以字符串方式返回. */
	public static final String printf2Str(String format, Object... args)
	{
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		PrintStream ps = new PrintStream(bos);
		ps.printf(format, args);
		return bos.toString();
	}

	/** 将字节流转换成十六进制字符串. */
	public static final String bytes2HexStr(byte by[])
	{
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		PrintStream ps = new PrintStream(bos);
		for (int i = 0; i < by.length; i++)
			ps.printf("%02X", by[i]);
		return bos.toString();
	}

	/** 将字节流转换成十六进制字符串. */
	public static final String printBytes(byte by[])
	{
		return printBytes(by, 0, by.length);
	}

	/** 将字节流转换成十六进制字符串. */
	public static String printBytes(byte by[], int offset, int length)
	{
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		PrintStream ps = new PrintStream(bos);
		int rows = length / 16;
		int ac = length % 16;
		for (int i = 0; i < rows; ++i)
			ps.printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", //
					by[offset + (16 * i) + 0], //
					by[offset + (16 * i) + 1], //
					by[offset + (16 * i) + 2], //
					by[offset + (16 * i) + 3], //
					by[offset + (16 * i) + 4], //
					by[offset + (16 * i) + 5], //
					by[offset + (16 * i) + 6], //
					by[offset + (16 * i) + 7], //
					by[offset + (16 * i) + 8], //
					by[offset + (16 * i) + 9], //
					by[offset + (16 * i) + 10], //
					by[offset + (16 * i) + 11], //
					by[offset + (16 * i) + 12], //
					by[offset + (16 * i) + 13], //
					by[offset + (16 * i) + 14], //
					by[offset + (16 * i) + 15], //
					toc(by[offset + (16 * i) + 0]), //
					toc(by[offset + (16 * i) + 1]), //
					toc(by[offset + (16 * i) + 2]), //
					toc(by[offset + (16 * i) + 3]), //
					toc(by[offset + (16 * i) + 4]), //
					toc(by[offset + (16 * i) + 5]), //
					toc(by[offset + (16 * i) + 6]), //
					toc(by[offset + (16 * i) + 7]), //
					toc(by[offset + (16 * i) + 8]), //
					toc(by[offset + (16 * i) + 9]), //
					toc(by[offset + (16 * i) + 10]), //
					toc(by[offset + (16 * i) + 11]), //
					toc(by[offset + (16 * i) + 12]), //
					toc(by[offset + (16 * i) + 13]), //
					toc(by[offset + (16 * i) + 14]), //
					toc(by[offset + (16 * i) + 15]));
		for (int i = 0; i < ac; i++)
			ps.printf("%02X ", by[offset + rows * 16 + i]);
		for (int i = 0; ac > 0 && i < 16 - ac; i++)
			ps.printf("%s", "   ");
		for (int i = 0; i < ac; i++)
			ps.printf("%c", toc(by[offset + rows * 16 + i]));
		return bos.toString();
	}

	/** format to #0.00 */
	public static final String decimalformat(double val)
	{
		return df.format(val);
	}

	/** Formatu.byte2ip(socket.getInetAddress()) */
	public static final long byte2ip(byte addr[])
	{
		if (addr == null || addr.length != 0x04)
		{
			Log.error("ipv6?");
			return 0;
		}
		return ((addr[0] << 24) & 0xFF000000L) + ((addr[1] << 16) & 0x00FF0000L) + ((addr[2] << 8) & 0x0000FF00L) + (addr[3] & 0x000000FFL);
	}

	/** 将IP地址转换成字符串表现形式. */
	public static final String ip2str(long ip)
	{
		return ((ip >> 24) & 0xFF) + "." + ((ip >> 16) & 0xFF) + "." + ((ip >> 8) & 0xFF) + "." + (ip & 0xFF);
	}

	/** 字符串(如电话号码)转成bcd数组. */
	public static final byte[] str2bcd(String str)
	{
		try
		{
			if (!Formatu.isDigital(str))
				return null;
			byte by[] = str.getBytes("ISO-8859-1");
			int k = by.length / 2;
			byte ret[] = new byte[(by.length % 2) + k];
			for (int i = 0; i < k; ++i)
				ret[i] = (byte) ((by[i * 2] & 0x0F) + (((by[i * 2 + 1] & 0x0F) << 4) & 0xF0));
			if (by.length % 2 == 1)
				ret[ret.length - 1] = (byte) ((by[by.length - 1] & 0x0F) + 0xF0);
			return ret;
		} catch (Exception e)
		{
			return null;
		}
	}

	/** 判断是不是一个可能合法的email格式. */
	public static final boolean isEmail(String email)
	{
		if (email == null)
			return false;
		byte by[] = email.getBytes();
		for (int i = 0; i < by.length; i++)
		{
			if (by[i] != 0x2E && by[i] != 0x40 && (by[i] < 0x30 || by[i] > 0x39) && (by[i] < 0x61 || by[i] > 0x7A))
				return false;
		}
		return true;
	}

	/** 生成一个随机数. */
	public static final long rand()
	{
		return rand.nextLong() & 0x7FFFFFFFFFFFFFFFL;
	}

	/** sleep, 毫秒. */
	public static final void sleep(long ms)
	{
		try
		{
			Thread.sleep(ms);
		} catch (Exception e)
		{
			Log.error(Log.trace(e));
		}
	}

	/** 导致当前线程挂起. */
	public static final void hold()
	{
		try
		{
			Thread.currentThread().join();
		} catch (Exception e)
		{
			e.printStackTrace();
		}
	}

	/** RC4加密. */
	public static byte[] rc4enc(byte key[], byte[] org)
	{
		try
		{
			Key k = new SecretKeySpec(key, "RC4");
			Cipher cip = Cipher.getInstance("RC4");
			cip.init(Cipher.ENCRYPT_MODE, k);
			return cip.doFinal(org);
		} catch (Exception e)
		{
			Log.error("call RC4-enc function failed.\n");
			return null;
		}
	}

	/** RC4解密. */
	public static byte[] rc4dec(byte key[], byte[] crypto)
	{
		try
		{
			Key k = new SecretKeySpec(key, "RC4");
			Cipher cip = Cipher.getInstance("RC4");
			cip.init(Cipher.DECRYPT_MODE, k);
			return cip.doFinal(crypto);
		} catch (Exception e)
		{
			Log.error("call RC4-dec function failed.\n");
			return null;
		}
	}

	/** MD5摘要算法. */
	public static byte[] md5(byte[] org)
	{
		try
		{
			return MessageDigest.getInstance("MD5").digest(org);
		} catch (Exception ex)
		{
			Log.error("call MD5 function failed.\n");
			return null;
		}
	}

	/** SHA-512摘要算法. */
	public static byte[] sha512(byte[] org)
	{
		try
		{
			return MessageDigest.getInstance("SHA-512").digest(org);
		} catch (Exception ex)
		{
			ex.printStackTrace();
			Log.error("call MD5 function failed.\n");
			return null;
		}
	}

	/** 以JNI标准格式返回函数的参数列表. */
	public static String getMethodPars(Class<?> cls, String funName)
	{
		Method m[] = cls.getDeclaredMethods();
		StringBuilder strb = new StringBuilder();
		for (int i = 0; m != null && i < m.length; i++)
		{
			if (m[i].getName().equals(funName))
			{
				Class<?> x[] = m[i].getParameterTypes();
				for (int j = 0; x != null && j < x.length; j++)
					strb.append("L").append(x[j].getName()).append(";");
			}
		}
		String str = strb.toString();
		if (str.length() < 2)
			return null;
		return strb.toString().replace('.', '/');
	}
}
