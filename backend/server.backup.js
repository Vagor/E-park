var express = require('express');
var app = express();
var middleware = 0;
var mongoose = require('mongoose');

var DBURL = "mongodb://localhost/e-park"
// connect mongodb
mongoose.connect(DBURL);
// Schema
var EPARKCARSchema = new mongoose.Schema({
  rfid: String, latitude: Number, longitude: Number,
  name: String, gender: String, carNumber: String,
});
EPARKCARSchema.statics.findByRFID = function(rfid, cb) {
  this.findOne({
    rfid: rfid
  }, cb);
}
// Model
var EPARKCARModel = mongoose.model('eparkcar', EPARKCARSchema);

// test get api
app.get('/test', function(req, res) {
  var rfid = req.params.rfid;
  EPARKCARModel.findByRFID(rfid, function(err, eparkcar) {
    if (eparkcar) {
      console.log(eparkcar);
      res.json({success: 1, code: eparkcar.code})
    } else {
      res.json({success: 0})
    }
  })
})

// search
app.post('/search', function(req, res) {
  var plateNumber = req.body.plateNumber;
  OFOModel.findByPN(plateNumber, function(err, eparkcar) {
    if (ofo) {
      console.log(ofo);
      res.json({success: 1, code: ofo.code})
    } else {
      res.json({success: 0})
    }
  })
})

// save
app.post('/save', function(req, res) {
  var code = req.body.codeSave;
  var plateNumber = req.body.plateNumberSave;

  console.log(code);
  // create an ofo entity
  ofoEntity = new OFOModel({pn: plateNumber, code: code})
  ofoEntity.save();
  res.json({success: '1'})
})


app.listen(3000, function() {
  console.log('HTTP server listening on port 3000');
});

//
// // 创建TCP server
// require('net').createServer(function(socket) {
//   // new connection
//   socket.on('data', function(data) {
//     // console.log(data.toString());
//     middleware = data.toString()
//   });
//   socket.on('connect', function(data) {
//     console.log("there's a new connection");
//   });
//   socket.on('end', function(data) {
//     // connection closed
//   });
//   socket.write('Some string');
// }).listen(4001, function() {
//   console.log('TCP server listening on port 4001');
// });
//
// app.all('/getData', function(req, res, next) {
//   res.header("Access-Control-Allow-Origin", "*");
//   res.header('Access-Control-Allow-Methods', 'PUT, GET, POST, DELETE, OPTIONS');
//   res.header("Access-Control-Allow-Headers", "X-Requested-With");
//   res.header('Access-Control-Allow-Headers', 'Content-Type');
//   next();
// });
//
// // route
// app.post('/getData', function(req, res) {
//   res.send(middleware);
// });
//
// // route
// app.get('/getData', function(req, res) {
//   if (middleware == "123123sdaf1") {}
//   res.send(middleware);
// });
//
