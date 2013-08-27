package cn.stmp.util;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.io.RandomAccessFile;
import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Date;

/**
 * 日志.
 * 
 * @author xuzewen
 * 
 */
public class Log
{
	public static final byte TRACE = 0x00, DEBUG = 0x01, INFO = 0x02, WARN = 0x03, ERROR = 0x04, FAULT = 0x05;
	private static byte level = DEBUG;
	private static boolean stdout = true;

	public static final void init(boolean stdout)
	{
		Log.stdout = stdout;
	}

	public static final void setLevel(byte level)
	{
		switch (level)
		{
		case TRACE:
		case DEBUG:
		case INFO:
		case WARN:
		case ERROR:
		case FAULT:
			Log.level = level;
			break;
		}
	}

	public static final boolean isTrace()
	{
		return Log.level <= TRACE;
	}

	public static final boolean isDebug()
	{
		return Log.level <= DEBUG;
	}

	public static final boolean isInfo()
	{
		return Log.level <= INFO;
	}

	public static final boolean isWarn()
	{
		return Log.level <= WARN;
	}

	public static final boolean isError()
	{
		return Log.level <= ERROR;
	}

	public static final boolean isFault()
	{
		return Log.level <= FAULT;
	}

	public static final void trace(String format, Object... args)
	{
		if (Log.level <= TRACE)
			log("TRAC", format, args);
	}

	public static final void debug(String format, Object... args)
	{
		if (Log.level <= DEBUG)
			log("DEBU", format, args);
	}

	public static final void info(String format, Object... args)
	{
		if (Log.level <= INFO)
			log("INFO", format, args);
	}

	public static final void warn(String format, Object... args)
	{
		if (Log.level <= WARN)
			log("WARN", format, args);
	}

	public static final void error(String format, Object... args)
	{
		if (Log.level <= ERROR)
			log("ERRO", format, args);
	}

	public static final void fault(String format, Object... args)
	{
		if (Log.level <= FAULT)
			log("FAUL", format, args);
	}

	public static final String trace(Exception e)
	{
		StringBuilder strb = new StringBuilder(0x200);
		StackTraceElement ste[] = e.getStackTrace();
		strb.append(e).append(Formatu.LINE);
		for (int i = 0; i < ste.length; i++)
			strb.append(ste[i].toString()).append(Formatu.LINE);
		return strb.toString();
	}

	public static void logBean(Object bean, String className, StringBuilder strb)
	{
		Method method[] = bean.getClass().getDeclaredMethods();
		Field field[] = bean.getClass().getDeclaredFields();
		Field ff = null;
		for (int i = 0; i < field.length; i++)
		{
			for (int j = field.length - 1; j > i; j--)
			{
				if (field[j].getName().compareTo(field[j - 1].getName()) < 0)
				{
					ff = field[j];
					field[j] = field[j - 1];
					field[j - 1] = ff;
				}
			}
		}
		for (int i = 0; i < field.length; i++)
		{
			try
			{
				String f = field[i].getName().toLowerCase();
				for (int j = 0; j < method.length; j++)
				{
					String fieldName = null;
					if (method[j].getName().equalsIgnoreCase("get" + f) || method[j].getName().toLowerCase().equalsIgnoreCase("is" + f))
					{
						fieldName = field[i].getName();
						Object o = null;
						try
						{
							o = method[j].invoke(bean);
						} catch (Exception e)
						{
							o = null;
						}
						Class<?> t = method[j].getReturnType();
						if (o != null && t.isArray())
						{
							int arr_length = Array.getLength(o);
							for (int k = 0; k < arr_length; k++)
							{
								Object obj = Array.get(o, k);
								if (obj != null && obj.getClass().isInstance(obj) && !isSimpleObject(obj))
								{
									String index = o.getClass().getSimpleName();
									index = index.substring(0, index.length() - 1) + k + "]";
									logBean(obj, className + "." + index + "." + obj.getClass().getSimpleName(), strb);
								} else
									strb.append(className + "." + fieldName + "[" + k + "] == " + obj).append(Formatu.LINE_R_N);
							}
						} else if (o != null && o instanceof Date)
							strb.append(className + "." + fieldName + " == " + Dateu.parseDateyyyyMMddHHmmss((Date) o)).append(Formatu.LINE_R_N);
						else if (o != null && t.isInstance(o) && !isSimpleObject(o))
							logBean(o, className + "." + o.getClass().getSimpleName(), strb);
						else
							strb.append(className + "." + fieldName + " == " + o).append(Formatu.LINE_R_N);
					}
				}
			} catch (Exception e)
			{
				e.printStackTrace();
			}
		}
	}

	private static void log(String level, String format, Object... args)
	{
		RandomAccessFile raf = null;
		ByteArrayOutputStream bos = null;
		try
		{
			Date now = new Date();
			StringBuilder prefix = new StringBuilder();
			StackTraceElement[] stacks = new Throwable().getStackTrace();
			prefix.append(Dateu.parseDateHHmmssms(now)).append(" [").append(level).append("](").append(stacks[2].getClassName()).append(" ").append(stacks[2].getMethodName()).append(" ").append(stacks[2].getLineNumber()).append(") ");
			//
			bos = new ByteArrayOutputStream();
			PrintStream ps = new PrintStream(bos);
			ps.printf("%s", prefix);
			ps.printf(format, args);
			if (Log.stdout)
				System.out.print(bos.toString());
		} catch (Exception e)
		{
			e.printStackTrace();
		} finally
		{
			CloseSth.closeRaf(raf);
		}
	}

	private static final boolean isSimpleObject(Object o)
	{
		return o instanceof String || o instanceof Number || o instanceof Character || o instanceof Boolean;
	}
}
