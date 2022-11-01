import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2

Page{
    id: root
    property alias backgroundColor: backgroundRect.color;
    property alias buttonText: navButton.text;

    signal buttonClicked();

    background: Rectangle {
        id: backgroundRect;
    }
    Button{
        id: navButton
        anchors.margins: defMargin
        onClicked: {
            root.buttonClicked();
        }
    }

}
