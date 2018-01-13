var net = require('net')
var socket = net.createConnection(4001, () => {
  console.log("connection success");
})
socket.write("the data from client", () => {
  console.log("write OK");
})
