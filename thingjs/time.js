
//加载场景代码
var app = new THING.App({ 
    // 场景地址
    "url": "/api/scene/3540ae80b3d9a5cd41ed6979"
});
var is_refresh_data = 0;
// 详见ThingJS教程 —— 界面 —— 快捷界面库 相关内容
// 界面组件
var panel = new THING.widget.Panel({
    titleText: 'mpu6050三轴数据',
    closeIcon: true, // 是否有关闭按钮 
    dragable: true, // 是否可以拖拽 
    retractable: true, // 是否可折叠
    opacity: 0.9, // 透明度 
    hasTitle: true, // 是否有标题
    zIndex: 999 // 设置层级
});

// 创建数据对象 
var dataObj = {
    x_axis: '0.00000',
    y_axis: '0.00000',
    z_axis: '0.00000',
    open: false,
};
// 界面绑定对象 
var x_axis = panel.addString(dataObj, 'x_axis').caption('x轴数据');
var y_axis = panel.addString(dataObj, 'y_axis').caption('y轴数据');
var z_axis = panel.addString(dataObj, 'z_axis').caption('z轴数据');
var open = panel.addBoolean(dataObj, 'open').caption('启动数据模拟');

open.on('change', function (ev) {
    if (ev) {
        is_refresh_data = 1;
        console.log("三轴数据跟踪使能");
    }
    else {
        is_refresh_data = 0;
        console.log("三轴数据跟踪关闭");
    }
});
// 创建Thing 
var box = app.create({ 
   type: 'Thing', 
   name: '井盖_污水',
   url: '/api/models/7ca44474756c4720b730af6e16f8159e/0/gltf/', 
   // 模型地址 
   position: [0, 0, 0],
   // 位置 
   angle: 0,

    width: 5,
    height: 0.1,
    position: [12, 78, 99], // 箱子坐标
   // 旋转 
   complete: function () {
       console.log('thing created: ' + this.id);
   }
});


// 创建箱子

var count = 0;
var number = 0;
app.on('update', function () {
    if (is_refresh_data == 1) {
        count = count + 1;
        
        if (count == 5) {
            // 箱子自转
            number = number + 1;
            $.ajax({
                'headers': {
                    "token": '31415926'// 请求头中带上了token数据
                },
                'url': "http://175.24.105.191:8080/axis", //Ajax请求服务的地址
                'type': "GET", //请求方式 "POST" 或 "GET"，默认为 "GET"
                'dataType': "json",    //服务返回的数据类型，推荐使用标准JSON数据格式
                //发送到服务器的数据
                'data': { 'id': number },
                //请求成功后的回调函数
                'success': function (data) {
                    if (data == 0) {
                        number = number - 1;
                        console.log('数据库没有数据了...');
                        return;
                    }
                    dataObj.x_axis = data.x - 180;
                    dataObj.y_axis = data.y - 180;
                    dataObj.z_axis = data.z - 180;
                    
                    box.rotateTo({
                        'angles': [data.x - 180, data.y - 180 , data.z- 180],
                        'time': 0,
                        'complete': function () {
                            console.log('rotateto completed');
                        }
                    });
                    console.log(data);
                    // 处理返回的数据
                },
                //请求失败时调用的函数 有以下三个参数：XMLHttpRequest 对象、错误信息、（可选）捕获的异常对象
                'error': function (xhr, status, error) {
                    console.log(xhr);
                },
            });
            count = 0
        }
    } else {

    }


});

function createPanel(obj) {
    // 界面组件
    var panel = new THING.widget.Panel({
        titleText: 'mpu6050三轴数据',
        hasTitle: true
    });

    var monitorControl = panel.addBoolean({ 'isOpen': true }, "isOpen").caption("监控开关");
    // 将物体的monitor对象中的数据 与 panel 进行绑定
    panel.add(obj.x, '温度').name('x-轴角度');
    panel.add(obj.y, '温度').name('y-轴角度');
    panel.add(obj.z, '温度').name('z-轴角度');

    monitorControl.on('change', function (ev) {
        if (ev) {
            updateData(obj);
        }
        else {
            stopUpdate();
        }
    })
}


// 设置最佳观看位置
app.camera.fit();
app.camera.lookAt(box);

// 设置主灯光 开启阴影
var mainLight = {
    shadow: false
};
app.lighting = { mainLight };