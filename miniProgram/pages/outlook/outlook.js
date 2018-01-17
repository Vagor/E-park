var helloData = {
  name: ' '
}

// Register a Page.
Page({
  data: helloData,
  changeName: function (e) {
    // sent data change to view
    this.setData({
      name: 'A01'
    })
  }
})