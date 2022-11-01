import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2

Page {
    id: root
    Rectangle{
        anchors.fill: parent
        color: "gray"
    }
    Column {
        spacing: 15
        //anchors.centerIn: parent
        Button{
            width: 500
            height: 75
            id: startButton
            Text{
                //anchors.centerIn: startButton
                text: "Start"
                font{
                    pointSize: 20
                }
            }
            //onClicked: stackView.push(start)
        }
        Button{
            width: 500
            height: 75
            id: authorsButton
            Text{
                //anchors.centerIn: authorsButton
                text: "Authors"
                font{
                    pointSize: 20
                }
            }
            //onClicked: stackView.push(authors)
        }

        Button{
            width: 500
            height: 75
            id: quitButton
            signal quiteClicked()
            objectName: "QuiteButton"
            //onClicked: quiteClicked()
            Text{
                //anchors.centerIn: quitButton
                text: "Quit"
                font{
                    pointSize: 20
                }
            }

        }
    }
}
