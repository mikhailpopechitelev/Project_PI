import QtQuick 2.15
import QtQuick.Window 2.15



Window {
    width: 640
    height: 480
    visible: true
    color: "blue"
    Text {
        text: "Hello!"
        x: 300
        y: 30
        font.pointSize: 24; font.bold: true
    }
    title: qsTr("Hello")
    Button{
        Text {
            id: helloText
            text: "Hello world!"
            y: 30
            font.pointSize: 24; font.bold: true
        }
    }
}




