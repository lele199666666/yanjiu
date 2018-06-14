<%@ page language="java" import="java.util.*" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

   
<%@page import="com.cby.domain.Sensor,com.cby.dao.SensorDao,com.cby.dao.impl.SensorDaoImpl,java.sql.ResultSet" %>
    
	<%
    		SensorDao sDao = new SensorDaoImpl();
    	    	    	    			List<Sensor> list= sDao.findData();
    	%>
		{
		"data":[
	<%
		for(int i = 0;i<list.size()-1;i++)
		{%>
			{
				"data_id":<%=list.get(i).getId() %>,
				"datatime":"<%=list.get(i).getTime() %>",
				"temperature":<%=list.get(i).getTmp() %>,
				"humidity":<%=list.get(i).getHum() %>,
				"sensor_id":<%=list.get(i).getSensor_id() %>
			},
		<%}
		
	%> 
			{
				"data_id":<%=list.get(list.size()-1).getId() %>,
				"datatime":"<%=list.get(list.size()-1).getTime() %>",
				"temperature":<%=list.get(list.size()-1).getTmp() %>,
				"humidity":<%=list.get(list.size()-1).getHum() %>,
				"sensor_id":<%=list.get(list.size()-1).getSensor_id() %>
			}
	]
	}
