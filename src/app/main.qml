import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import QtQuick.Layouts

Rectangle {
  id: root
  color: "black"
  property real zoomLevel: 1.0
  property int setHeight: 40

  GridLayout {
    id: gridLayout
    anchors.left: parent.left
    anchors.right: parent.right
    rows: 6
    columns: 3

    rowSpacing: 2
    columnSpacing: 2
    TextButtone {
      Layout.fillWidth: true
      Layout.columnSpan: 3
      height: 20
      title: "Open File"
      onClicked: fileDialog.open()
    }
    Rectangle {
      Layout.fillWidth: true
      Layout.columnSpan: 3
      height: 1
    }
    TitleLabel {
      id: titleZoom

      Layout.fillWidth: true
      height: 20
      Layout.columnSpan: 3
      title: "Zoom:"
    }
    TextButtone {
      id: zoomPluse
      Layout.fillWidth: true
      height: 20
      title: "-"
      onClicked: if (root.zoomLevel > 0.1) {
                   root.zoomLevel -= 0.1
                   AppControler.setFigurSize(root.zoomLevel)
                 }
    }
    TextButtone {
      id: zoomMinus
      Layout.fillWidth: true
      height: 20
      title: "+"
      onClicked: if (root.zoomLevel < 10.0) {
                   root.zoomLevel += 0.1
                   AppControler.setFigurSize(root.zoomLevel)
                 }
    }
    TextButtone {
      id: resultZoom
      Layout.fillWidth: true
      height: 20
      title: zoomLevel.toFixed(1)
    }
    Rectangle {
      Layout.fillWidth: true
      Layout.columnSpan: 3
      height: 1
    }
  }

  ListButtone {
    id: listColorBox
    anchors.topMargin: 2
    anchors.top: gridLayout.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    height: frontBoxHeight + setingBoxHeight
    frontBoxHeight: 20
  }
  TitleLabel {
    anchors.topMargin: 2
    anchors.top: listColorBox.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    id: titleProgrcton
    title: "Projection:"
    height: 20
  }

  TextButtone {
    id: pers
    anchors.topMargin: 2
    anchors.top: titleProgrcton.bottom
    anchors.left: parent.left
    height: 20
    width: 49
    hoverEnabled: false
    enabled: false
    title: "Pers"
    onClicked: {
      pers.enabled = false
      orto.enabled = true
      pers.hoverEnabled = false
      orto.hoverEnabled = true
      AppControler.setProgection()
    }
  }
  TextButtone {
    id: orto
    anchors.topMargin: 2
    anchors.leftMargin: 2
    anchors.top: titleProgrcton.bottom
    anchors.right: parent.righ
    anchors.left: pers.right
    height: 20
    width: 49
    title: "Orto"
    onClicked: {
      pers.hoverEnabled = true
      orto.hoverEnabled = false
      pers.enabled = true
      orto.enabled = false
      AppControler.setProgection()
    }
  }
  Rectangle {
    id: line2
    color: "white"
    anchors.top: pers.bottom
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.topMargin: 2
    height: 1
  }
  ListButtoneForSize {
    id: sizeListButton
    anchors.top: line2.bottom
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.topMargin: 2
    height: frontBoxHeight + setingBoxHeight
    frontBoxHeight: 20
  }
  MySlider {
    id: slider
    anchors.topMargin: 40
    anchors.top: sizeListButton.bottom
    anchors.right: parent.right
    anchors.left: parent.left
  }
  TitleLabel {
    id: titleV
    anchors.bottomMargin: 15
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    title: "V:" + String(AppControler.myIntProperty)
    color: "black"
  }
  TitleLabel {
    id: tileFile
    anchors.bottomMargin: 25
    anchors.bottom: titleV.top
    anchors.left: parent.left
    anchors.right: parent.right
    title: String(AppControler.nameFile)
    color: "black"
  }

  FileDialog {
    id: fileDialog
    title: "Please choose a file"
    onAccepted: {
      var filePath = fileDialog.file.toString()
      AppControler.setFile(urlToPath(filePath))
    }
    onRejected: {
      console.log("Canceled")
    }
  }

  ColorDialog {
    id: colorDialog
    title: "Please choose a color"
    onAccepted: {
      rotationAnimation.start()
      color1.color = colorDialog.color
      AppControler.setFoneColor(color1.color)
    }
  }

  function urlToPath(urlString) {
    var s
    if (urlString.startsWith("file:///")) {
      var k = urlString.charAt(9) === ':' ? 8 : 7
      s = urlString.substring(k)
    } else {
      s = urlString
    }
    return decodeURIComponent(s)
  }
}
