package cn.stmp.util;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * 日期处理.
 * 
 * @author xuzewen
 * 
 */
public class Dateu
{
	public static final long SECOND = 1 * 1000;
	public static final long MINUTE = 60 * SECOND;
	public static final long HOUR = 60 * MINUTE;
	public static final long DAY = 24 * HOUR;
	public static final long WEEK = 7 * DAY;

	/** 入参格式:yyyyMMdd */
	public static Date parseDateyyyyMMdd(String date)
	{
		if (date == null)
			return null;
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
		try
		{
			return sdf.parse(date);
		} catch (ParseException e)
		{
			return null;
		}
	}

	public static Date parseDateyyyyMMddHH(String date)
	{
		if (date == null)
			return null;
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHH");
		try
		{
			return sdf.parse(date);
		} catch (ParseException e)
		{
			return null;
		}
	}

	public static Date parseDateyyyyMMddHHmm(String date)
	{
		if (date == null)
			return null;
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmm");
		try
		{
			return sdf.parse(date);
		} catch (ParseException e)
		{
			return null;
		}
	}

	public static Date parseDateyyyy_MM_dd_HH_mm_ss(String date)
	{
		if (date == null)
			return null;
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		try
		{
			return sdf.parse(date);
		} catch (ParseException e)
		{
			return null;
		}
	}

	/** 返回格式: yyyy-MM-dd */
	public static String parseDateyyyy_MM_dd(Date date)
	{
		return parse("yyyy-MM-dd", date);
	}

	/** 返回格式:yyyy-MM-dd HH:mm:ss */
	public static String parseDateyyyyMMddHHmmss(Date date)
	{
		return parse("yyyy-MM-dd HH:mm:ss", date);
	}

	/** 返回格式:yyyy/MM/dd HH:mm */
	public static String parseDateyyyyMMddHHmm2(Date date)
	{
		return parse("yyyy/MM/dd HH:mm", date);
	}

	/** 返回格式:yyyyMMdd */
	public static String parseDateyyyyMMdd(Date date)
	{
		return parse("yyyyMMdd", date);
	}

	/** 返回格式:yyyyMMddHH */
	public static String parseDateyyyyMMddHH(Date date)
	{
		return parse("yyyyMMddHH", date);
	}

	/** 返回格式:yyyyMMddHHmmss */
	public static String parseDateyyyyMMddHHmmss2(Date date)
	{
		return parse("yyyyMMddHHmmss", date);
	}

	/** 返回格式:yyyyMMddHHmm */
	public static String parseDateyyyyMMddHHmm(Date date)
	{
		return parse("yyyyMMddHHmm", date);
	}

	/** 返回格式:MMddHHmmss */
	public static String parseDateMMddHHmmss(Date date)
	{
		return parse("MMddHHmmss", date);
	}

	/** 返回格式:HH:mm:ss */
	public static String parseDateHHmmss(Date date)
	{
		return parse("HH:mm:ss", date);
	}

	public static String parseDateHHmmssms(Date date)
	{
		long ms = date.getTime() % 1000;
		return parse("HH:mm:ss", date) + "." + (ms > 99 ? ms : (ms > 9 ? ("0" + ms) : ("00" + ms)));
	}

	/** 置为凌晨00:00:00 000,Calendar提供的set函数, 并不能清除毫秒. */
	public static Date set000000(Date date)
	{
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		cal.set(cal.get(Calendar.YEAR), cal.get(Calendar.MONTH), cal.get(Calendar.DAY_OF_MONTH), 0, 0, 0);
		return clearMinute(cal.getTime());
	}

	public static int minuteInt(Date date)
	{
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		return cal.get(Calendar.MINUTE);
	}

	/** 当前时间的hour,小于10时前面补个零. */
	public static String hour(Date date)
	{
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		int hour = cal.get(Calendar.HOUR_OF_DAY);
		return hour > 9 ? hour + "" : "0" + hour;
	}

	/** 返回当天的小�? */
	public static int hourInt(Date date)
	{
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		return cal.get(Calendar.HOUR_OF_DAY);
	}

	/** 返回日期的天�? */
	public static int dayInt(Date date)
	{
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		return cal.get(Calendar.DAY_OF_MONTH);
	}

	/** 返回月份. */
	public static int monthInt(Date date)
	{
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		return cal.get(Calendar.MONTH) + 1;
	}

	/** 返回年份. */
	public static int yearInt(Date date)
	{
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		return cal.get(Calendar.YEAR);
	}

	/** 判断两个日期是否在同�?�� */
	public static boolean isSameDay(Date arg0, Date arg1)
	{
		return (Dateu.yearInt(arg0) == Dateu.yearInt(arg1)) && //
				(Dateu.monthInt(arg0) == Dateu.monthInt(arg1)) && //
				(Dateu.dayInt(arg0) == Dateu.dayInt(arg1));
	}

	/** 构�?�?��给定的时�? */
	public static Date createDate(int year, int month, int day, int hourOfDay, int minute, int second)
	{
		Calendar cal = Calendar.getInstance();
		cal.set(year, month, day, hourOfDay, minute, second);
		return cal.getTime();
	}

	/** 时间滚动.按分�?up==true向今后滚�?否则向以前滚�? */
	public static Date dateRollOfMinute(Date date, int amount, boolean up)
	{
		return up ? new Date(date.getTime() + amount * Dateu.MINUTE) : new Date(date.getTime() - amount * Dateu.MINUTE);
	}

	/** 时间滚动.按小�?up==true向今后滚�?否则向以前滚�? */
	public static Date dateRollOfHour(Date date, int amount, boolean up)
	{
		return up ? new Date(date.getTime() + amount * Dateu.HOUR) : new Date(date.getTime() - amount * Dateu.HOUR);
	}

	/** 时间滚动.按天,up==true向今后滚�?否则向以前滚�? */
	public static Date dateRollOfDay(Date date, int amount, boolean up)
	{
		return up ? new Date(date.getTime() + amount * Dateu.DAY) : new Date(date.getTime() - amount * Dateu.DAY);
	}

	/** 时间滚动.按月. */
	public static Date dateRollOfMonth(Date date, boolean up)
	{
		Calendar ca = Calendar.getInstance();
		ca.setTime(date);
		ca.roll(Calendar.MONTH, up);
		if (ca.getTime().getTime() < date.getTime())
			ca.roll(Calendar.YEAR, true);
		return ca.getTime();
	}

	/** 整点. */
	public static Date clearMinute(Date date)
	{
		return new Date(date.getTime() - (date.getTime() % Dateu.HOUR));
	}

	/** 整天. */
	public static Date clearHour(Date date)
	{
		return set000000(date);
	}

	/** parse */
	public static String parse(String format, Date date)
	{
		try
		{
			return date == null ? null : new SimpleDateFormat(format).format(date);
		} catch (Exception e)
		{
			return null;
		}
	}
}
