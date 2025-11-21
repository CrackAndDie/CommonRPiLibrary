package io.github.softv.internal.common;

public class JavaWrapper
{
	private static native int Java_StartSPI(String path, int channel, int speed, int mode);
	private static native int Java_StartUSB(String path, int baud);
	private static native void Java_StopSPI();
	private static native void Java_StopUSB();
	private static native byte[] Java_ReadWriteSPI(byte[] data, int len);
	private static native byte[] Java_ReadWriteUSB(byte[] data, int len);
	
	public JavaWrapper(){}
	
	public int StartSPI(String path, int channel, int speed, int mode){
		return Java_StartSPI(path, channel, speed, mode);
	}
	
	public int StartUSB(String path, int baud){
		return Java_StartUSB(path, baud);
	}
	
	public byte[] ReadWriteSPI(byte[] data, int len){
		return Java_ReadWriteSPI(data, len);
	}
	
	public byte[] ReadWriteUSB(byte[] data, int len){
		return Java_ReadWriteUSB(data, len);
	}
	
	public void StopSPI(){
		Java_StopSPI();
	}
	
	public void StopUSB(){
		Java_StopUSB();
	}
}
