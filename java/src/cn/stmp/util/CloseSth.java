package cn.stmp.util;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.RandomAccessFile;
import java.net.Socket;
import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

/**
 * Close Something
 * 
 * @author xuzewen
 * 
 */
public class CloseSth
{
	public static void closeConn(Connection conn, PreparedStatement pst, ResultSet rst, CallableStatement call)
	{
		if (rst != null)
		{
			try
			{
				rst.close();
			} catch (Exception e)
			{
				Log.error(Log.trace(e));
			}
		}
		rst = null;
		if (pst != null)
		{
			try
			{
				pst.close();
			} catch (Exception e)
			{
				Log.error(Log.trace(e));
			}
		}
		pst = null;
		if (call != null)
		{
			try
			{
				call.close();
			} catch (Exception e)
			{
				Log.error(Log.trace(e));
			}
		}
		call = null;
		if (conn != null)
		{
			try
			{
				conn.close();
			} catch (Exception e)
			{
				Log.error(Log.trace(e));
			}
		}
		conn = null;
	}

	public static void closeInputStream(InputStream ins)
	{
		if (ins != null)
		{
			try
			{
				ins.close();
			} catch (IOException e)
			{
				Log.error(Log.trace(e));
			}
		}
		ins = null;
	}

	public static void closeOutputStream(OutputStream ops)
	{
		try
		{
			if (ops != null)
				ops.close();
		} catch (Exception e)
		{
			Log.error(Log.trace(e));
		}
		ops = null;
	}

	public static void closeSocket(Socket s)
	{
		if (s != null)
		{
			try
			{
				s.close();
			} catch (Exception e)
			{
				Log.error(Log.trace(e));
			}
		}
		s = null;
	}

	public static void closeRaf(RandomAccessFile raf)
	{
		try
		{
			if (raf != null)
				raf.close();
		} catch (Exception e)
		{
			Log.error(Log.trace(e));
		}
		raf = null;
	}
}
