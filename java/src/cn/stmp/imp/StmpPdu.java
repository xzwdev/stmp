package cn.stmp.imp;

/**
 * 
 * @author xuzewen
 * 
 */
public class StmpPdu
{
	public int rm = Stmp.STMP_PDU;
	public byte buff[] = new byte[Stmp.STMP_PDU];

	public String toString()
	{
		return StmpDec.printPdu2Str(this);
	}
}
