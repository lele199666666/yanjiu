<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
		<form action="${pageContext.request.contextPath }/servlet/regServlet" method="get">
			<!-- 数据采集时间：<input type="text" name="time"/><br/> -->
			温度：<input type="text" name="tmp"/><br/>
			湿度：<input type="text" name="hum"/><br/>
			传感器ID：<input type="text" name="sensor_id"/><br/>
			<input type="submit" value="上传"/><br/>
		</form>
</body>
</html>