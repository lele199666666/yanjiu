package com.cby.web.servlet;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.sql.Timestamp;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;

import com.cby.domain.Sensor;
import com.cby.service.SensorService;
import com.cby.service.impl.SensorServiceImpl;

/**
 * Servlet implementation class SubServlet
 */
//@WebServlet(name = "/servlet/subServlet",urlPatterns = "/subServlet")
public class SubServlet extends HttpServlet {

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html;charset=UTF-8");
		Date da = new Date();
		
		Timestamp t = new Timestamp(new Date().getTime());
		//获取表单数据
		Sensor sensor = new Sensor(0, t, 0, 0, 0);
		try {
			BeanUtils.populate(sensor, request.getParameterMap());
		
		//调用业务逻辑
		SensorService us = new SensorServiceImpl();
		us.subData(sensor);
		} catch (Exception e) {
			e.printStackTrace();
		}
		//分发转向
		response.getWriter().write("提交成功！1s后跳转到主页");
		response.setHeader("refresh", "1;url="+request.getContextPath()+"/index.jsp");
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
