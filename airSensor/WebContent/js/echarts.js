/*var data_sensor=[
   {
       data_id:1,
       datatime: "2018-5-31 11:34:30",
       temperature: 27,
       humidity: 50,
       sensor_id: 1,
       sensor_location: "home",
       sensor_state: "onwork",
       last_submit: "2018-5-31 11:34:30"
   },
   {
       data_id:1,
       datatime: "2018-5-31 11:35:30",
       temperature: 30,
       humidity: 40,
       sensor_id: 1,
       sensor_location: "home",
       sensor_state: "onwork",
       last_submit: "2018-5-31 11:36:30"
   },
   {
       data_id:1,
       datatime: "2018-5-31 11:34:30",
       temperature: 27,
       humidity: 50,
       sensor_id: 1,
       sensor_location: "home",
       sensor_state: "onwork",
       last_submit: "2018-5-31 11:34:30"
   },
   {
       data_id:1,
       datatime: "2018-5-31 11:35:30",
       temperature: 30,
       humidity: 40,
       sensor_id: 1,
       sensor_location: "home",
       sensor_state: "onwork",
       last_submit: "2018-5-31 11:36:30"
   }
]*/
var data_sensor = []
$(function () {
    //var data_sensor = null

    var ajax = new XMLHttpRequest()
    ajax.open('get', 'http://47.106.143.61:8080/airSensor/query.jsp')
    ajax.onreadystatechange = () => {
        if(ajax.readyState == 4){
            if (ajax.status == 200) {
                console.log("test")
                //console.log(ajax.response)
                var reg = /[\w\[\]:""{}\.,]/i
                var temp = ajax.response
                for(let i=0;i<temp.length;i++){
                    //console.log(i,temp[i])
                    if(temp[i].match(reg)!=null){
                        data_sensor.push(temp[i])
                    }
                }
                data_sensor = data_sensor.join("")
                console.log("接收到数据",typeof data_sensor,ajax.responseType,data_sensor);
                data_sensor = JSON.parse(data_sensor).data
                //data_sensor = JSON.parse(ajax.response)
                render()
            }
        }
    }
    ajax.send()
})
function render() {

    echarts_3();
    echarts_4();

    function echarts_3() {
        // 基于准备好的dom，初始化echarts实例
        var myChart = echarts.init(document.getElementById('echarts_3'));

        option = {

            tooltip: {
                trigger: 'axis'
            },
            legend: {
                orient: 'vertical',
                data: ['简易程序案件数']
            },
            grid: {
                left: '3%',
                right: '3%',
                top: '8%',
                bottom: '5%',
                containLabel: true
            },
            color: ['#a4d8cc', '#25f3e6'],
            toolbox: {
                show: false,
                feature: {
                    mark: { show: true },
                    dataView: { show: true, readOnly: false },
                    magicType: { show: true, type: ['line', 'bar', 'stack', 'tiled'] },
                    restore: { show: true },
                    saveAsImage: { show: true }
                }
            },

            calculable: true,
            xAxis: [
                {
                    type: 'category',

                    axisTick: { show: false },

                    boundaryGap: false,
                    axisLabel: {
                        textStyle: {
                            color: '#ccc',
                            fontSize: '12'
                        },
                        lineStyle: {
                            color: '#2c3459',
                        },
                        interval: { default: 0 },
                        rotate: 60,
                        /*formatter: function (params) {
                            var newParamsName = "";// 最终拼接成的字符串
                            var paramsNameNumber = params.length;// 实际标签的个数
                            var provideNumber = 4;// 每行能显示的字的个数
                            var rowNumber = Math.ceil(paramsNameNumber / provideNumber);// 换行的话，需要显示几行，向上取整
                            /**
                             * 判断标签的个数是否大于规定的个数， 如果大于，则进行换行处理 如果不大于，即等于或小于，就返回原标签
                             */
                            // 条件等同于rowNumber>1*/
                            //if (paramsNameNumber > provideNumber) {
                                /** 循环每一行,p表示行 */
                                /*var tempStr = "";
                                tempStr = params.substring(0, 4);
                                newParamsName = tempStr + "...";// 最终拼成的字符串
                            } else {
                                // 将旧标签的值赋给新标签
                                newParamsName = params;
                            }
                            //将最终的字符串返回
                            return newParamsName
                        }*/

                    },
                    data: []
                }
            ],
            yAxis: {

                type: 'value',
                axisLabel: {
                    textStyle: {
                        color: '#ccc',
                        fontSize: '12',
                    }
                },
                axisLine: {
                    lineStyle: {
                        color: 'rgba(160,160,160,0.3)',
                    }
                },
                splitLine: {
                    lineStyle: {
                        color: 'rgba(160,160,160,0.3)',
                    }
                },
                max: 50

            }
            ,
            series: [
                {
                    // name:'简易程序案件数',
                    type: 'line',
                    areaStyle: {

                        normal: {
                            type: 'default',
                            color: new echarts.graphic.LinearGradient(0, 0, 0, 0.8, [{
                                offset: 0,
                                color: '#25f3e6'
                            }, {
                                offset: 1,
                                color: '#0089ff'
                            }], false)
                        }
                    },
                    smooth: true,
                    itemStyle: {
                        normal: { areaStyle: { type: 'default' } }
                    },
                    data: []


                }
            ]
        };
        for (let i = 0; i < data_sensor.length; i++) {
            option.series[0].data.push(data_sensor[i].temperature)

        }
        for (let i = 0; i < data_sensor.length; i++) {
            option.xAxis[0].data.push(data_sensor[i].datatime.slice(4,6)+"月"+data_sensor[i].datatime.slice(6,8)+"日 "+data_sensor[i].datatime.slice(8,13))

        }
        console.log("温度数据注入成功",option.series[0].data)
        // 使用刚指定的配置项和数据显示图表。
        myChart.setOption(option);
        window.addEventListener("resize", function () {
            myChart.resize();
        });
    }

    function echarts_4() {
        // 基于准备好的dom，初始化echarts实例
        var myChart = echarts.init(document.getElementById('echarts_4'));

        option = {

            tooltip: {
                trigger: 'axis'
            },
            legend: {
                orient: 'vertical',
                data: ['简易程序案件数']
            },
            grid: {
                left: '3%',
                right: '3%',
                top: '8%',
                bottom: '5%',
                containLabel: true
            },
            color: ['#a4d8cc', '#25f3e6'],
            toolbox: {
                show: false,
                feature: {
                    mark: { show: true },
                    dataView: { show: true, readOnly: false },
                    magicType: { show: true, type: ['line', 'bar', 'stack', 'tiled'] },
                    restore: { show: true },
                    saveAsImage: { show: true }
                }
            },

            calculable: true,
            xAxis: [
                {
                    type: 'category',

                    axisTick: { show: false },

                    boundaryGap: false,
                    axisLabel: {
                        textStyle: {
                            color: '#ccc',
                            fontSize: '12'
                        },
                        lineStyle: {
                            color: '#2c3459',
                        },
                        interval: { default: 0 },
                        rotate: 60,


                    },
                    data: []
                }
            ],
            yAxis: {

                type: 'value',
                axisLabel: {
                    textStyle: {
                        color: '#ccc',
                        fontSize: '12',
                    }
                },
                axisLine: {
                    lineStyle: {
                        color: 'rgba(160,160,160,0.3)',
                    }
                },
                splitLine: {
                    lineStyle: {
                        color: 'rgba(160,160,160,0.3)',
                    }
                },
                max: 100

            }
            ,
            series: [
                {
                    // name:'简易程序案件数',
                    type: 'line',
                    areaStyle: {

                        normal: {
                            type: 'default',
                            color: new echarts.graphic.LinearGradient(0, 0, 0, 0.8, [{
                                offset: 0,
                                color: '#25f3e6'
                            }, {
                                offset: 1,
                                color: '#0089ff'
                            }], false)
                        }
                    },
                    smooth: true,
                    itemStyle: {
                        normal: { areaStyle: { type: 'default' } }
                    },
                    data: []


                }
            ]
        };
        for (let i = 0; i < data_sensor.length; i++) {
            option.series[0].data.push(data_sensor[i].humidity)
        }
        for (let i = 0; i < data_sensor.length; i++) {
            option.xAxis[0].data.push(data_sensor[i].datatime.slice(4,6)+"月"+data_sensor[i].datatime.slice(4,6)+"日 "+data_sensor[i].datatime.slice(8,13))

        }
        // 使用刚指定的配置项和数据显示图表。
        myChart.setOption(option);
        window.addEventListener("resize", function () {
            myChart.resize();
        });
    }
}

