package com.cby.service.impl;

import com.cby.dao.SensorDao;
import com.cby.dao.impl.SensorDaoImpl;
import com.cby.domain.Sensor;
import com.cby.service.SensorService;

public class SensorServiceImpl implements SensorService {

	SensorDao sDao = new SensorDaoImpl();
	
	public void subData(Sensor sensor) throws Exception {
		sDao.addData(sensor);
	}

	public Sensor findData() {
		Sensor u = null;
		try {
			sDao.findData();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return u;
	}

}
