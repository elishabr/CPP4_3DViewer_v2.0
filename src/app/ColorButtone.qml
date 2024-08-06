import QtQuick
import QtQuick.Controls
import Qt.labs.platform

Item {
  id: root
  property alias color: colorBox.color
  signal clicked
  Rectangle {
    id: colorBox
    anchors.fill: parent
    width: 46
    height: 40
    color: "black"
    border.color: "white"
    property int rotationAngle: 180

    transform: Rotation {
      origin.x: 23
      origin.y: 20
      axis {
        x: 0
        y: 1
        z: 0
      }
      angle: colorBox.rotationAngle
    }

    MouseArea {
      anchors.fill: parent
      onClicked: {
        rotationAnimation.start()
        colorDialog.open()
      }
    }

    PropertyAnimation {
      id: rotationAnimation
      target: colorBox
      property: "rotationAngle"
      to: colorBox.rotationAngle + 180 // Увеличиваем угол на 54 градуса
      duration: 500 // Длительность анимации в миллисекундах
    }
  }
  ColorDialog {
    id: colorDialog
    title: "Please choose a color"
    onAccepted: {
      rotationAnimation.start()
      colorBox.color = colorDialog.color
      root.clicked()
    }
  }
}
