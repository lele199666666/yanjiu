package com.cby.service;

import com.cby.domain.Sensor;

public interface SensorService {
	/**
	 * 添加传感器信息
	 * @param user
	 * @throws Exception
	 */
	public void subData(Sensor sensor) throws Exception;
	
	/**
	 * 查询数据
	 * @param user
	 * @return
	 */
	public Sensor findData();//2
}
