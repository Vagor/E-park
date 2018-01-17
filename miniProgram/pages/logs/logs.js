Page({
  data: {
    //name: "waiting......"
    //if(name)
    //{
    markers: [],
    //},
    name: "waiting......"
  },
  changeName: function (e) {
    // sent data change to view
    this.setData({
      name: 'A01',
      markers: [{
        iconPath: "/image/地标1.png",
        id: 0,
        latitude: 31.31352,
        longitude: 121.409,
        width: 35,
        height: 35
      }]
    })
  },
 /* onLoad: function () {
    this.setData({
      logs: (wx.getStorageSync('logs') || []).map(log => {
        return util.formatTime(new Date(log))
      })
    })
  }*/
})