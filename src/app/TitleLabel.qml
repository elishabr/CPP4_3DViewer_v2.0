import QtQuick

Item {
  id: root
  property alias title: titleText.text
  property alias color: rectangle.color
  signal clicked
  Rectangle {
    id: rectangle
    anchors.fill: parent
    color: "#2E2E2E"
    //border.color: "white"
  }
  Text {
    id: titleText
    color: "white"
    anchors.centerIn: parent
    font.family: "Deja Vu" // Моноширинный шрифт
    font.pointSize: 10 // Размер шрифта
  }
  MouseArea {
    id: buttonMouseArea
    anchors.fill: parent
    hoverEnabled: true
    onClicked: root.clicked() //fileDialog.open()
  }
}
