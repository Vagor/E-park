var express = require('express');
var app = express();
var middleware = 0;

app.listen(3000, function() {
  console.log('HTTP server listening on port 3000');
});
// 创建TCP server
require('net').createServer(function(socket) {
  // new connection
  socket.on('data', function(data) {
    // console.log(data.toString());
    middleware = data.toString()
  });
  socket.on('connect', function(data) {
    console.log("there's a new connection");
  });
  socket.on('end', function(data) {
    // connection closed
  });
  socket.write('Some string');
}).listen(4001, function() {
  console.log('TCP server listening on port 4001');
});

app.all('/getData', function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header('Access-Control-Allow-Methods', 'PUT, GET, POST, DELETE, OPTIONS');
  res.header("Access-Control-Allow-Headers", "X-Requested-With");
  res.header('Access-Control-Allow-Headers', 'Content-Type');
  next();
});

// route
app.post('/getData', function(req, res) {
  res.send(middleware);
});

// route
app.get('/getData', function(req, res) {
  if (middleware == "123123sdaf1") {}
  res.send(middleware);
});
