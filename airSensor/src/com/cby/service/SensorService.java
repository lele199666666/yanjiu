package com.cby.service;

import com.cby.domain.Sensor;

public interface SensorService {
	/**
	 * ��Ӵ�������Ϣ
	 * @param user
	 * @throws Exception
	 */
	public void subData(Sensor sensor) throws Exception;
	
	/**
	 * ��ѯ����
	 * @param user
	 * @return
	 */
	public Sensor findData();//2
}
