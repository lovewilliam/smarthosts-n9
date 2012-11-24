import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0


Page
{
	id:mainPage
	
	property alias infoBanner: banner

	orientationLock: PageOrientation.LockPortrait
	
	Header
	{
		id: header;
	}

	Component.onCompleted :
	{
		if(!util_engine.isRoot())
		{
			showError("Must run as root!")
		}
	}

	function setStatusText()
	{
		header.statusText =  qsTr("")
	}

	function openFile(file)
	{
		var component = Qt.createComponent(file)

		if (component.status == Component.Ready)
			pageStack.push(component);
		else
			console.log("Error loading component:", component.errorString());
	}

	function showError(text)
	{
		waitDialogue.visible = false
	
		errorDialog.titleText = qsTr("Error")
		errorDialog.message = text
		errorDialog.open();
	}

	QueryDialog
	{
		id: errorDialog
		icon: ""
		titleText:qsTr("Error");
		message:qsTr("")
		acceptButtonText: qsTr("OK")
	}

	function showSuccessWrite()
	{
		waitDialogue.visible = false
		errorDialog.titleText = qsTr("Done !")
		errorDialog.message = qsTr("Changes has been made to\n hosts file !")
		errorDialog.open();
	}
	
	function hostFileUpdated()
	{
	//TODO! update label here
		waitDialogue.visible = false
		label_lastUpdate.text = qsTr("LastUpdate:")+util_engine.getLastUpdateTime()
		label_svnHostsDate.text = qsTr("Hosts File Date:")+util_engine.getHostsDate()
	}

	InfoBanner
	{
		id: banner
		x: 0
		y: 0
	 	z: 10
		text: qsTr("");
	}
	
	Rectangle
	{
		id:label_bg
		color:"Black"
		width: parent.width
		height: 60
		Label
		{
			id:label_lastUpdate
			text: qsTr("LastUpdate:")+util_engine.getLastUpdateTime()
			width:parent.width * 8/10
			height:20
			anchors
			{
				horizontalCenter: parent.horizontalCenter
				top:parent.top
			}
			color:"white"
		}
		Label
		{
			id:label_svnHostsDate
			text: qsTr("Hosts File Date:")+util_engine.getHostsDate()
			width:parent.width * 8/10
			height:20
			anchors
			{
				horizontalCenter: parent.horizontalCenter
				top:label_lastUpdate.bottom
				bottom:parent.bottom
				topMargin:10
			}
			color:"white"
		}
		anchors
		{
			top: header.bottom
			horizontalCenter: parent.horizontalCenter
			topMargin:0
		}
	}

	ListView
	{
		id:list
		clip:true
		width: parent.width
		anchors
		{
			horizontalCenter: parent.horizontalCenter
			top:label_bg.bottom
			bottom:btn_writeToSys.top
			topMargin:10
		}
		model: itemModel
		spacing: 2
		delegate: Component
			{
				Item
				{
					height: 64
					width: parent.width
					CheckBox
					{
						text:model.modelData.name
						checked: model.modelData.ticked
						onClicked:
						{
							model.modelData.ticked = checked
						}
					}
				}
			}
		//highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
	}

	SectionScroller
	{
		listView: list
	}

	ScrollDecorator
	{
		flickableItem: list
	}

	Button
	{
		id:btn_writeToSys
		text:qsTr("Add to hosts")
		width:parent.width * 8/10
		height:parent.height /10
		anchors
		{
			horizontalCenter: parent.horizontalCenter
			bottom:parent.bottom
			leftMargin: 20
			rightMargin: 20
			topMargin: 20
			bottomMargin:10
		}
		onClicked:
		{
			util_engine.slot_writeHosts();
		}
	}

	QueryDialog
	{
		id:aboutDialog
		icon: "/opt/smarthosts/icons/smarthosts_128x128.png"
		titleText:qsTr("About smarthosts")
		message:qsTr("smarthosts by\nlovewilliam<lovewilliam@gmail.com>\nhttp://code.google.com/p/smarthosts-n9")
		acceptButtonText: qsTr("OK")
	}

	//////////////////////////////////////////////////////////
	
	Item
	{
		id: waitDialogue
		visible: false
		anchors.fill: parent;
		z:100
		property bool progbarRunning: false
		property int pvalue: 0
		
		Rectangle
		{
			id:shaderLayer
			anchors.bottom: parent.bottom
			width: parent.width
			height: parent.height
			color: "darkgray"
			opacity: 0.7
			MouseArea
			{
				anchors.fill: parent
			}
		}
		Label
		{
			id:label_progress
			text: qsTr("<center>contacting server...</center>")
			anchors
			{
				left: parent.left
				right: parent.right
				top: parent.top
				topMargin: 460
			}
			font.pixelSize: 34
			
		}
		ProgressBar
		{
			id: progressBar
			width: parent.width
			maximumValue: 100
			minimumValue: 0
			indeterminate: parent.progbarRunning
			value: parent.pvalue
			anchors
			{
				left: parent.left
				right: parent.right
				top: label_progress.bottom
				topMargin: 20
			}
		}
	}
	
	function progress_to(percent,all)
	{
		waitDialogue.pvalue = percent/all * 100
		if(percent==0)
		{
			waitDialogue.progbarRunning = true
			waitDialogue.visible = true
		}else if(percent == all)
		{
			waitDialogue.visible = false
		}else
		{
			waitDialogue.progbarRunning = false
		}
	}
///////////////////////////////////////////////////////////////
	
	ToolBarLayout
	{
	        id: commonTools
        	visible: true
	        ToolIcon
		{
        		platformIconId: "toolbar-view-menu"
        		anchors.right: (parent === undefined) ? undefined : parent.right
			onClicked: (myMenu.status == DialogStatus.Closed) ? myMenu.open() : myMenu.close();
	        }
	}
	Menu
	{
        	id: myMenu
        	visualParent: pageStack
	        MenuLayout
		{
			MenuItem
			{
				id: miAbout
				text: qsTr("About")
				onClicked:
				{
					aboutDialog.open();
				}
			}
			MenuItem
			{
				id: miRevert
				text: qsTr("Revert to clean hosts")
				onClicked:
				{
					util_engine.slot_writeCleanHosts();
				}
			}
			MenuItem
			{
				id: miCheckUpdate
				text: qsTr("Check Update")
				onClicked:
				{
					util_engine.slot_updateSavedHostFile();
				}
			}
			MenuItem
			{
				id: miSettings
				text: qsTr("Settings")
				onClicked:
				{
					mainPage.openFile("Settings.qml");
				}
			}
		}
	}
	tools: commonTools
}



