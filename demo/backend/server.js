var express = require('express');
var app = express();

// 定义构造函数
function UserDataModel(rfid, latitude, longitude, name, gender, carNumber, openid,parkFlag) {
  this.rfid = rfid;
  this.latitude = latitude;
  this.longitude = longitude;
  this.name = name;
  this.gender = gender;
  this.carNumber = carNumber;
  this.openid = openid; //微信的用户唯一id，可用于识别用户
  this.parkFlag = parkFlag; //判断是否停车 1==>停车，0==>未停车
}

// 伪造数据 用户1
var user1 = new UserDataModel("A560691B", 123.9123, 23.9123, '沈丹凤', 'Female', '沪BSH366', 'o1qIl0d430JuNJ0fmONW3xOHgfB4', false)

// 伪造数据 用户2
var user2 = new UserDataModel("asd22fa", 223.9223, 23.9223, '朱超', 'Female', '沪U12366', 'o1qIl0d430JuNJ0fmONW3xOHgfB4',false)

// 伪造数据 用户3
var user3 = new UserDataModel("asd312fa", 323.9323, 23.9323, '吕秀萍', 'Female', '沪L14306', 'o1qIl0d430JuNJ0fmONW3xOHgfB4',false)

// 伪造数据 用户4
var user4 = new UserDataModel("asd42f3a", 423.9423, 23.9423, '范佳敏', 'Female', '沪G54876', 'o1qIl0d430JuNJ0fmONW3xOHgfB4',false)

// 伪造数据 用户5
var user5 = new UserDataModel("asd52f5a", 523.9523, 23.9523, '朱正国', 'Male', '沪AH3636', 'o1qIl0d430JuNJ0fmONW3xOHgfB4',false)

// 创建TCP server
require('net').createServer(function(socket) {
  // new connection
  socket.on('data', function(data) {
    // 硬件传过来的data只有rfid卡号
    var tempRFID = data.toString()
    console.log(tempRFID);

    switch (tempRFID) {
      case user1.rfid:
        user1.parkFlag = !user1.parkFlag;
        break;
      case user2.rfid:
        user2.parkFlag = !user2.parkFlag;
        break;
      case user3.rfid:
        user3.parkFlag = !user3.parkFlag;
        break;
      case user4.rfid:
        user4.parkFlag = !user4.parkFlag;
        break;
      case user5.rfid:
        user5.parkFlag = !user5.parkFlag;
        break;
      default:

    }
  });
  socket.on('connection', function(data) {
    console.log("there's a new connection");
  });
  socket.on('end', function(data) {
    // connection closed
  });
  socket.write('Some string');
}).listen(3000, function() {
  console.log('TCP server listening on port 3000');
});

// HTTP服务器内容

app.all('/getData', function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header('Access-Control-Allow-Methods', 'PUT, GET, POST, DELETE, OPTIONS');
  res.header("Access-Control-Allow-Headers", "X-Requested-With");
  res.header('Access-Control-Allow-Headers', 'Content-Type');
  next();
});

// route
app.get('/getData', function(req, res) {
  switch (req.query.openid) {
    case user1.openid:
      res.send(user1)
      break;
    case user2.openid:
      res.send(user2)
      break;
    case user3.openid:
      res.send(user3)
      break;
    case user4.openid:
      res.send(user4)
      break;
    case user5.openid:
      res.send(user5)
      break;
    default:
      res.send(null)
  }
});
app.listen(80, function() {
  console.log('HTTP server listening on port 80');
});
