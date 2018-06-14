package com.cby.dao;

import java.util.List;

import com.cby.domain.Sensor;

public interface SensorDao {
	/**
	 * 添加传感器信息
	 * @param user
	 * @throws Exception
	 */
	public void addData(Sensor sensor) throws Exception;//1
	
	/**
	 * 查询数据
	 * @param user
	 * @return
	 * @throws Exception
	 */
	public List findData()throws Exception;//2
}
