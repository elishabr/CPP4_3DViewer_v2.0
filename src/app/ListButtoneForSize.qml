import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Image {
  id: root
  property real zoomLevel1: 0.0
  property real zoomLevel2: 4.0
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
      text: "Size:"
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
          gapSize.height = 0
          gapSize.title = ""
          zoomPluse.height = 0
          zoomMinus.height = 0
          line1.height = 1
          line2.height = 0
          // line3.height = 0
          line4.height = 0
          line5.height = 0
          resultZoom.height = 0
          zoomPluse.title = ""
          zoomMinus.title = ""
          resultZoom.title = ""
          dashSize.height = 0
          dashSize.title = ""
          zoomPluse1.title = ""
          zoomPluse1.height = 0
          zoomMinus1.height = 0
          zoomMinus1.title = ""
          resultZoom2.title = ""
          resultZoom2.height = 0
        } else {
          setingBox.height = 100
          gapSize.height = 20
          zoomPluse.height = 20
          zoomPluse.title = "-"
          zoomMinus.title = "+"
          resultZoom.title = zoomLevel1
          zoomMinus.height = 20
          line1.height = 0
          line2.height = 1
          // line3.height = 1
          line4.height = 1
          line5.height = 1
          resultZoom.height = 20
          gapSize.title = "Gap Size"
          dashSize.height = 20
          dashSize.title = "Point Size"
          zoomPluse1.title = "-"
          zoomPluse1.height = 20
          zoomMinus1.height = 20
          zoomMinus1.title = "+"
          resultZoom2.title = zoomLevel2
          resultZoom2.height = 20
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
      anchors {
        top: setingBox.top
        left: setingBox.left
        right: setingBox.right
      }
      id: line1
      height: 1
    }
    TitleLabel {
      anchors {
        topMargin: 2
        top: line1.bottom
        left: setingBox.left
        right: setingBox.right
      }
      id: gapSize
      height: 0
      color: "black"
    }
    Rectangle {
      id: line2
      anchors {
        topMargin: 2
        top: gapSize.bottom
        left: setingBox.left
        right: setingBox.right
      }
    }
    TextButtone {
      id: zoomPluse
      anchors {
        topMargin: 2
        rightMargin: 2
        top: line2.bottom
        left: setingBox.left
      }
      width: 32
      onClicked: if (root.zoomLevel1 > 0.0) {
                   root.zoomLevel1 -= 1.0
                   resultZoom.title = root.zoomLevel1
                   AppControler.setGapSize(root.zoomLevel1)
                 }
    }
    TextButtone {
      id: zoomMinus
      anchors {
        topMargin: 2
        rightMargin: 2
        leftMargin: 2
        top: line2.bottom
        left: zoomPluse.right
        right: resultZoom.left
      }
      width: 32
      onClicked: if (root.zoomLevel1 < 10.0) {
                   root.zoomLevel1 += 1.0
                   resultZoom.title = root.zoomLevel1
                   AppControler.setGapSize(root.zoomLevel1)
                 }
    }
    TextButtone {

      id: resultZoom
      anchors {
        topMargin: 2
        top: line2.bottom
        right: setingBox.right
      }
      width: 32
    }
    // Rectangle {
    //   id: line3
    //   color: "white"
    //   anchors {
    //     topMargin: 2
    //     top: zoomPluse.bottom
    //   }
    //   width: 100
    // }
    TitleLabel {
      anchors {
        topMargin: 2
        top: zoomPluse.bottom
        left: setingBox.left
        right: setingBox.right
      }
      id: dashSize
      height: 0
      color: "black"
    }
    Rectangle {
      id: line4
      anchors {
        topMargin: 2
        top: dashSize.bottom
      }
      width: 100
    }
    TextButtone {
      id: zoomPluse1
      anchors {
        topMargin: 2
        rightMargin: 2
        top: line4.bottom
        left: setingBox.left
      }
      width: 32
      onClicked: if (root.zoomLevel2 > 0.0) {
                   root.zoomLevel2 -= 2.0
                   resultZoom2.title = root.zoomLevel2
                   AppControler.setPointSize(root.zoomLevel2)
                 }
    }
    TextButtone {
      id: zoomMinus1
      anchors {
        topMargin: 2
        rightMargin: 2
        leftMargin: 2
        top: line4.bottom
        left: zoomPluse.right
        right: resultZoom.left
      }
      width: 32
      onClicked: if (root.zoomLevel2 < 20.0) {
                   root.zoomLevel2 += 2.0
                   resultZoom2.title = root.zoomLevel2
                   AppControler.setPointSize(root.zoomLevel2)
                 }
    }
    TextButtone {

      id: resultZoom2
      anchors {
        topMargin: 2
        top: line4.bottom
        right: setingBox.right
      }
      width: 32
    }
    Rectangle {
      id: line5
      anchors {
        topMargin: 2
        top: zoomPluse1.bottom
      }
      width: 100
    }
  }
}
