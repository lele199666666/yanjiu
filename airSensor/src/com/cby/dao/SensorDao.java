package com.cby.dao;

import java.util.List;

import com.cby.domain.Sensor;

public interface SensorDao {
	/**
	 * ��Ӵ�������Ϣ
	 * @param user
	 * @throws Exception
	 */
	public void addData(Sensor sensor) throws Exception;//1
	
	/**
	 * ��ѯ����
	 * @param user
	 * @return
	 * @throws Exception
	 */
	public List findData()throws Exception;//2
}
