import QtQuick
import QtQuick.Controls

Image {
  id: root
  property alias frontBoxHeight: frontBox.height
  property alias setingBoxHeight: setingBox.height
  signal clicked
  Rectangle {
    id: frontBox
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    color: "#2E2E2E"
    Text {
      id: titleText
      text: "Color:"
      color: "white"
      anchors.centerIn: parent
      font.family: "Deja Vu" // Моноширинный шрифт
      font.pointSize: 10 // Размер шрифта
    }
    TextButtone {
      id: buttoneOpen
      anchors.left: frontBox.left
      anchors.top: frontBox.top
      width: 24
      height: 20
      border: 0
      title: setingBox.height ? "\\/" : "/\\"
      onClicked: {
        if (setingBox.height) {
          setingBox.height = 0
          choseColor1.height = 0
          fone.height = 0
          fone.title = ""
          ribs.height = 0
          ribs.title = ""
          choseColor2.height = 0
          tops.height = 0
          tops.title = ""
          choseColor3.height = 0
          line1.height = 1
          line2.height = 0
        } else {
          setingBox.height = 130
          choseColor1.height = 40
          fone.height = 40
          fone.title = "Fone"
          ribs.height = 40
          ribs.title = "Ribs"
          choseColor2.height = 40
          tops.height = 40
          tops.title = "Tops"
          choseColor3.height = 40
          line1.height = 0
          line2.height = 1
        }
        root.clicked()
      }
    }
  }

  Rectangle {
    id: setingBox
    anchors.top: frontBox.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    color: "black"
    Rectangle {
      id: line1
      color: "white"
      anchors.top: setingBox.top
      anchors.right: setingBox.right
      anchors.left: setingBox.left
      height: 1
    }
    ColorButtone {
      id: choseColor1
      anchors {
        top: line1.top
        right: setingBox.right
        leftMargin: 2
        topMargin: 2
      }
      width: 46
      height: 0
      onClicked: AppControler.setFoneColor(choseColor1.color)
    }
    TitleLabel {
      anchors {
        top: setingBox.top
        left: setingBox.left
        topMargin: 2
      }
      id: fone
      height: 0
      width: 52
      color: "black"
    }
    ColorButtone {
      id: choseColor2
      anchors {
        top: choseColor1.bottom
        right: setingBox.right
        leftMargin: 2
        topMargin: 2
      }
      width: 46
      height: 0
      color: "#ff0000"
      onClicked: AppControler.setRibsColor(choseColor2.color)
    }
    TitleLabel {
      anchors {
        top: fone.bottom
        left: setingBox.left
        topMargin: 2
      }
      id: ribs
      height: 0
      width: 52
      color: "black"
    }
    ColorButtone {
      id: choseColor3
      anchors {
        top: choseColor2.bottom
        right: setingBox.right
        leftMargin: 2
        topMargin: 2
      }
      width: 46
      height: 0
      color: "#00ff00"
      onClicked: AppControler.setVertexColor(choseColor3.color)
    }
    TitleLabel {
      anchors {
        top: ribs.bottom
        left: setingBox.left
        topMargin: 2
      }
      id: tops
      height: 0
      width: 52
      color: "black"
    }
    Rectangle {
      id: line2
      color: "white"
      anchors.top: tops.bottom
      anchors.right: setingBox.right
      anchors.left: setingBox.left
      anchors.topMargin: 2
      height: 0
    }
  }
}
