import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2

Window {
    visible:  true
    width: 150
    height: 150
    Column{
        anchors.centerIn: parent
        Button{
            id: button1
            signal infoclicked(string str)
            objectName: "InfoButton"
            text: "Info"
            onClicked: infoclicked("Information")
        }
        Button{
            id: button2
            signal quiteClicked()
            objectName: "QuiteButton"
            text: "Quite"
            onClicked: quiteClicked()
        }
        Button{
            id: button3
            signal colorChanClicked()
            objectName: "ColorChanButton"
            text: "NotChanged"
            background: Rectangle{
                implicitWidth: 100
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                color: "blue"
            }
            onClicked: colorChanged("red")
        }
    }

}




