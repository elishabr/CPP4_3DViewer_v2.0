import QtQuick

Item {
  id: root
  property alias title: titleText.text
  property alias border: rectengle.border.width
  property alias color: rectengle.color
  property alias hoverEnabled: buttonMouseArea.hoverEnabled
  signal clicked
  //opacity: buttonMouseArea.containsMouse ? 0.75 : 1
  Rectangle {
    id: rectengle
    anchors.fill: parent
    color: "black"
    border.color: "white"
    border.width: 1
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
    onEntered: rectengle.color = "gray" // Изменение цвета при наведении
    onExited: rectengle.color = "black" // Возвращение к исходному цвету
    onClicked: root.clicked() //fileDialog.open()
  }
}
