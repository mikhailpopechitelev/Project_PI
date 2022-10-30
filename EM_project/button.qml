import QtQuick 2.0

Rectangle {

    width: 100
    height: 100
    color: "red"
    border.color: "black"
    border.width: 5
    radius: 10
    Text {
        objectName: "lext"
        //anchors.centerIn: parent
        color: "red"
        text: qsTr("Hello eblan")
        function setFontSize(newSize){
            font.pixelSize = newSize
            return font.family + "Size=" + newSize
        }
    }
}
