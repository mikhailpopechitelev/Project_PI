import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2

Window {
    id: window
    visible:  true
    width: 1920
    height: 1080
    title: qsTr("Plague simulation")

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: menu
    }

    Page {
        id: menu
        Rectangle{
            //anchors.fill: parent
            color: "gray"
        }
        Column {
            spacing: 15
            anchors.centerIn: parent
            Button{
                width: 500
                height: 75
                id: startButton
                Text{
                    anchors.centerIn: startButton
                    text: "Start"
                    font{
                        pointSize: 20
                    }
                }
                onClicked: stackView.push(start)
            }
            Button{
                width: 500
                height: 75
                id: authorsButton
                Text{
                    anchors.centerIn: authorsButton
                    text: "Authors"
                    font{
                        pointSize: 20
                    }
                }
                onClicked: stackView.push(authors)
            }

            Button{
                width: 500
                height: 75
                id: quitButton
                signal quiteClicked()
                objectName: "QuiteButton"
                onClicked: quiteClicked()
                Text{
                    anchors.centerIn: quitButton
                    text: "Quit"
                    font{
                        pointSize: 20
                    }
                }

            }
        }
    }





    SimplePage {
        id: start
        visible: false
        backgroundColor: "white"
        buttonText: "back"
        onButtonClicked: {
            stackView.pop()
        }
        Rectangle{
            width: 400
            height: 1080
            color: "gray"
        }
        Rectangle{
            anchors.right: parent.right
            width: 400
            height: 1080
            color: "gray"
        }
    }





    SimplePage {
        id: authors
        visible: false
        backgroundColor: "blue"
        buttonText: "back"
        onButtonClicked: {
            stackView.pop()
        }
    }


}



