package com.cby.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;

import com.cby.dao.SensorDao;
import com.cby.domain.Sensor;
import com.cby.utils.DBUtils;
import java.sql.ResultSet;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

public class SensorDaoImpl implements SensorDao {

	public void addData(Sensor sensor) throws Exception {
		Connection conn = null;
		PreparedStatement ps = null;

		try {
			conn = DBUtils.getConnection();
			ps = conn.prepareStatement("INSERT INTO data(time,tmp,hum,sensor_id) VALUES(?,?,?,?)");
			ps.setTimestamp(1, sensor.getTime());
			ps.setDouble(2, sensor.getTmp());
			ps.setDouble(3, sensor.getHum());
			ps.setInt(4, sensor.getSensor_id());
			
			ps.executeUpdate();
			
			ps = conn.prepareStatement("DELETE FROM data where TO_DAYS(NOW())-TO_DAYS(time)>7");
			
			int i = ps.executeUpdate();		//exeUpdate÷¥––INSERT,UPDATE,DELETE
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			throw new RuntimeException("ÃÌº” ß∞‹");
		}finally {
			DBUtils.closeAl(null, ps, conn);
		}
		
	}

	public List findData() throws Exception {
		List<Sensor> list = new ArrayList<Sensor>();
		
		Connection conn = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		
		conn = DBUtils.getConnection();
		ps = conn.prepareStatement("SELECT * FROM data order by id desc limit 30");
		
		rs = ps.executeQuery();
		
		while(rs.next()) {
			int id = rs.getInt("id");
			Timestamp time = rs.getTimestamp("time");
			double tmp = rs.getDouble("tmp");
			double hum = rs.getDouble("hum");
			int sensor_id = rs.getInt("sensor_id");
			Sensor u = new Sensor(id,time,tmp,hum,sensor_id);
			list.add(u);
		}
		return list;
	}

}
