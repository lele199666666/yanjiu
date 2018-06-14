package com.cby.domain;

import java.io.Serializable;
import java.sql.Timestamp;

//import java.util.Date;

public class Sensor implements Serializable{
	private int id;
	private Timestamp time;
	private double tmp;
	private double hum;
	private int sensor_id;
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public Timestamp getTime() {
		return time;
	}
	public void setTime(Timestamp time) {
		this.time = time;
	}
	public double getTmp() {
		return tmp;
	}
	public void setTmp(double tmp) {
		this.tmp = tmp;
	}
	public double getHum() {
		return hum;
	}
	public void setHum(double hum) {
		this.hum = hum;
	}
	public int getSensor_id() {
		return sensor_id;
	}
	public void setSensor_id(int sensor_id) {
		this.sensor_id = sensor_id;
	}
	
	public Sensor(int id,Timestamp time,double tmp,double hum,int sensor_id) {
		super();
		this.id = id;
		this.time = time;
		this.tmp = tmp;
		this.hum = hum;
		this.sensor_id = sensor_id;
	}
}
