import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Food List Manager"

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 10

        TextField {
            id: foodInput
            width: parent.width
            placeholderText: "Food name"
        }

        TextField {
            id: groupInput
            width: parent.width
            placeholderText: "Group (e.g., Fruits, Vegetables)"
        }

        Row {
            spacing: 10

            Button {
                text: "Add"
                onClicked: {
                    if (foodInput.text !== "" && groupInput.text !== "") {
                        foodModel.addFood(foodInput.text, groupInput.text);
                        foodInput.text = "";
                        groupInput.text = "";
                    }
                }
            }

            Button {
                text: "Remove"
                onClicked: {
                    if (listView.currentIndex !== -1)
                        foodModel.removeFood(listView.currentIndex);
                }
            }
        }

        ListView {
            id: listView
            width: parent.width
            height: 400
            model: foodModel

            delegate: Rectangle {
                width: parent.width
                height: 50
                color: listView.currentIndex === index ? "#ddd" : "#fff"
                border.color: "#ccc"
                border.width: 1

                Row {
                    anchors.fill: parent
                    spacing: 10
                    padding: 5

                    Column {
                        width: parent.width - 80
                        Text { text: "🍽 " + name; font.bold: true }
                        Text { text: "Group: " + group; font.italic: true }
                    }

                    Button {
                        text: "✏️"
                        onClicked: editDialog.openDlg(index, name, group)
                    }
                }
            }
        }
    }

    Dialog {
        id: editDialog
        title: "Edit Food"
        property int editIndex: -1
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        Column {
            spacing: 10
            padding: 10

            TextField { id: editName; placeholderText: "Food name" }
            TextField { id: editGroup; placeholderText: "Food group" }
        }

        function openDlg(index, name, group) {
            editIndex = index;
            editName.text = name;
            editGroup.text = group;
            editDialog.open();
        }

        onAccepted: {
            if (editIndex !== -1) {
                foodModel.editFood(editIndex, editName.text, editGroup.text);
            }
        }
    }
}
