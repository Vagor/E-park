var http = require('http')

// 发送一个请求到代理服务器
const options = {
  port: 4001,
  hostname: '127.0.0.1',
  path: 'www.google.com:80'
};

const req = http.request(options);
req.end();

req.on('connect', (res, socket, head) => {
  console.log('已连接！');

  // 通过代理服务器发送一个请求
  socket.write('GET / HTTP/1.1\r\n' +
               'Host: www.baidu.com:80\r\n' +
               'Connection: close\r\n' +
               '\r\n');
  socket.on('data', (chunk) => {
    console.log(chunk.toString());
  });
  socket.on('end', () => {
    proxy.close();
  });
});
