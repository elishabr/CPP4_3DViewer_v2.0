import QtQuick
import QtQuick.Controls

Item {
  id: root
  property alias tile: titleX.title

  TitleLabel {
    id: titleX
    anchors.top: parent.top
    anchors.left: parent.left
    title: "X:"
    color: "black"
    height: 20
    width: 20
  }

  Slider {
    id: slider
    anchors.topMargin: 2
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.left: titleX.right
    from: -1
    to: 1
    value: 0
    stepSize: 0.01
    onValueChanged: {
      AppControler.setPositonX(value.toFixed(2))
    }
  }

  TitleLabel {
    id: titleY
    anchors.topMargin: 2
    anchors.top: titleX.bottom
    anchors.left: parent.left
    title: "Y:"
    color: "black"
    height: 20
    width: 20
  }

  Slider {
    id: slider2
    anchors.topMargin: 4
    anchors.top: slider.bottom
    anchors.right: parent.right
    anchors.left: titleY.right
    from: -1
    to: 1
    value: 0
    stepSize: 0.01
    onValueChanged: {
      AppControler.setPositonY(value.toFixed(2))
    }
  }
  TitleLabel {
    id: titleZ
    anchors.topMargin: 2
    anchors.top: titleY.bottom
    anchors.left: parent.left
    title: "Z:"
    color: "black"
    height: 20
    width: 20
  }

  Slider {
    id: slider3
    anchors.topMargin: 4
    anchors.top: slider2.bottom
    anchors.right: parent.right
    anchors.left: titleZ.right
    from: 0.1
    to: -10
    value: -5
    stepSize: 0.1
    onValueChanged: {
      AppControler.setPositonZ(value.toFixed(2))
    }
  }
}
