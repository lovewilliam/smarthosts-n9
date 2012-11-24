import QtQuick 1.1
import com.nokia.meego 1.0
import QtMobility.location 1.2

Page
{
	id: settingPage
	
	orientationLock: PageOrientation.LockPortrait

	Header
	{
		id: s_header
		statusText: qsTr("Setting")
	}

        function openFile(file)
        {
                var component = Qt.createComponent(file)

                if (component.status == Component.Ready)
                        pageStack.push(component);
                else
                        console.log("Error loading component:", component.errorString());
        }
	
	Column
	{
		spacing: 16
		anchors.top: s_header.bottom
		anchors.left: settingPage.left
		anchors.right: settingPage.right
                Row
                {
                        Label
                        {
                                text: qsTr("Select Hosts File")
                                anchors.verticalCenter: method_button.verticalCenter
                                width: parent.parent.width / 4
                        }
                        ButtonColumn
                        {
                                id: method_button
                                Button
                                {
                                        text: qsTr("PC")
                                        checked: util_engine.getHostsFileType()=="PC" ? true : false
                                        onClicked: util_engine.setHostsFileType("PC")
                                }
                                Button
                                {
                                        text: qsTr("Android")
                                        checked: util_engine.getHostsFileType()=="ANDROID" ? true : false
                                        onClicked: util_engine.setHostsFileType("ANDROID")
                                }
                                Button
                                {
                                        text: qsTr("IOS")
                                        checked: util_engine.getHostsFileType()=="IOS" ? true : false
                                        onClicked: util_engine.setHostsFileType("IOS")
                                }
                        }
		}
		Row
		{
			Label
			{
				text: qsTr("<font color=\"red\">Don't forget to check update \n after selecting new hosts file.</font>")
			}
                }

	}
	
	ToolBarLayout
	{
		id: settingTools
		visible: false
		ToolIcon
		{
			iconId: "toolbar-back";
			onClicked:
			{
				//TODO emit an restart daemon signal?
				pageStack.pop();
			}
		}
	}
	tools: settingTools
}

