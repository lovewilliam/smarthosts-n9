import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow
{
	id: appWindow
	
	initialPage: mainPage

	MainPage
	{
	        id: mainPage
	}
	showStatusBar: true
	showToolBar: true

	function updateBanner(text)
	{
		mainPage.infoBanner.text=text
		mainPage.infoBanner.show();
	}
	function updateCheckboxList(count)
	{
		mainPage.reloadCheckBoxList();
	}
	function ui_error(err_type,text)
	{
		if(err_type==0)
		{
			mainPage.showError(qsTr("Network error : ") + text);
		}else if(err_type==1)
		{
			mainPage.showError(qsTr("Filesys error : ") + text);
		}else
		{
			mainPage.showError(""+err_type+ " : "+text);
		}
	}
	function ui_process_update(percent,all)
	{
		mainPage.progress_to(percent,all);
	}
	function doneWriteToHosts()
	{
		mainPage.showSuccessWrite();
	}
	function hostsFileUpdated()
	{
		mainPage.hostFileUpdated();
	}
}



