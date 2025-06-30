#include "HtmlTemplateBuilder.h"
#include <fstream>
#include <string>
#include <iostream>
#include <tchar.h>

using namespace std;
#define HEAD_HTML							_T("\\01_head.html")
#define JQUERY_HTML							_T("\\02_jquery.html")
#define KEYMASTER_HTML						_T("\\03_keymaster.html")
#define ISCROLL_HTML						_T("\\04_iscroll.html")
#define HWV_HTML							_T("\\05_hwv.html")
#define JQUERY_MINICOLORS_HTML				_T("\\06_jquery_minicolors.html")
#define HWV_SERVER_HTML						_T("\\07_hwv_server.html")
#define HWV_SAMPLE_HTML						_T("\\08_hwv_sample.html")
#define STYLE_MODELTREE_HTML				_T("\\09_style_modelTree.html")
#define STYLE_TOOLBAR_HTML					_T("\\10_style_toolBar.html")
#define STYLE_COMMON_HTML					_T("\\11_style_common.html")
#define STYLE_DESKTOP_HTML					_T("\\12_style_desktop.html")
#define STYLE_MOBILE_HTML					_T("\\13_style_mobile.html")
#define STYLE_NOTE_HTML						_T("\\14_style_note.html")
#define STYLE_JQUERY_HTML					_T("\\15_style_jquery.html")
#define STYLE_PROPERTY_HTML					_T("\\16_style_property.html")
#define STYLE_VIEWERSETTINGS_HTML			_T("\\17_style_viewerSettings.html")
#define STYLE_JQUERY_MINICOLORS_HTML		_T("\\18_style_jquery_minicolors.html")
#define SCRIPT_CUSTOM_HTML					_T("\\19_script_custom.html")
#define SCRIPT_HTML							_T("\\20_script.html")
#define SCRIPT_CUSTOM_BEFORE_START_VIEWER	_T("\\21_script_custom_before_start_viewer.js")
#define BODY_TOOLBAR_HTML					_T("\\22_body_toolbar.html")
#define BODY_VIEWERSETTINGS_HTML			_T("\\23_body_viewerSettings.html")
#define BODY_SNAPSHOT_DIALOG_HTML			_T("\\24_body_snapshot_dialog.html")
#define BODY_CUSTOM_HTML					_T("\\25_body_custom.html")

void addFile(ofstream &ofs, const wchar_t *inFile)
{
	ifstream ifs;
	string str;

	ifs.open(inFile);
	while (getline(ifs, str))
	{
		ofs << str << endl;
	}
	ifs.close();
}

HtmlTemplateBuilder::HtmlTemplateBuilder()
{
}

HtmlTemplateBuilder::~HtmlTemplateBuilder()
{
}

void HtmlTemplateBuilder::Create(const wchar_t *templateDirPath)
{
	ofstream ofs;
	ifstream ifs;
	string str;
	wchar_t path[2048];

	wcscpy(path, templateDirPath);
	wcscat(path, _T("\\_htmltemplate.html"));
	ofs.open(path, ios::out | ios::trunc);
	
	wcscpy(path, templateDirPath);
	wcscat(path, HEAD_HTML);
	addFile(ofs, path);

	//if (options.standardUI || options.toolBar)
	wcscpy(path, templateDirPath);
	wcscat(path, JQUERY_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, KEYMASTER_HTML);
	addFile(ofs, path);

	if (options.standardUI) {
		wcscpy(path, templateDirPath);
		wcscat(path, ISCROLL_HTML);
		addFile(ofs, path);
	}

	wcscpy(path, templateDirPath);
	wcscat(path, HWV_HTML);
	addFile(ofs, path);

	//if (options.standardUI || options.toolBar)
	wcscpy(path, templateDirPath);
	wcscat(path, JQUERY_MINICOLORS_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, HWV_SERVER_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, HWV_SAMPLE_HTML);
	addFile(ofs, path);

	if (options.standardUI) {
		wcscpy(path, templateDirPath);
		wcscat(path, STYLE_MODELTREE_HTML);
		addFile(ofs, path);
	}

	if (options.standardUI || options.toolBar) {
		wcscpy(path, templateDirPath);
		wcscat(path, STYLE_TOOLBAR_HTML);
		addFile(ofs, path);
	}

	wcscpy(path, templateDirPath);
	wcscat(path, STYLE_COMMON_HTML);
	addFile(ofs, path);

	if (options.standardUI)
	{
		wcscpy(path, templateDirPath);
		wcscat(path, STYLE_DESKTOP_HTML);
		addFile(ofs, path);
	}

	if (options.standardUI)
	{
		wcscpy(path, templateDirPath);
		wcscat(path, STYLE_MOBILE_HTML);
		addFile(ofs, path);
	}

	if (options.standardUI) {
		wcscpy(path, templateDirPath);
		wcscat(path, STYLE_NOTE_HTML);
		addFile(ofs, path);
	}
	//if (options.standardUI || options.toolBar)
	wcscpy(path, templateDirPath);
	wcscat(path, STYLE_JQUERY_HTML);
	addFile(ofs, path);

	if (options.standardUI) {
		wcscpy(path, templateDirPath);
		wcscat(path, STYLE_PROPERTY_HTML);
		addFile(ofs, path);
	}

	if (options.standardUI || options.toolBar)
	{
		wcscpy(path, templateDirPath);
		wcscat(path, STYLE_VIEWERSETTINGS_HTML);
		addFile(ofs, path);
	}

	wcscpy(path, templateDirPath);
	wcscat(path, STYLE_JQUERY_MINICOLORS_HTML);
	addFile(ofs, path);

	if (options.customScript) {
		wcscpy(path, templateDirPath);
		wcscat(path, SCRIPT_CUSTOM_HTML);
		addFile(ofs, path);
	}

	wcscpy(path, templateDirPath);
	wcscat(path, SCRIPT_HTML);
	ifs.open(path);
	while (getline(ifs, str)) 
	{
		if (str == "//BEFORE_START_VIEWER") {
			if (options.standardUI) {
				ofs << "    ui = new Communicator.Ui.Desktop.DesktopUi(hwv, {" << endl;
				ofs << "        containerId: \"content\"," << endl;
				ofs << "    });" << endl;
			}
			else {
				ofs << "    hwv.setCallbacks({" << endl;
				ofs << "        sceneReady: () => {" << endl;
				if (options.toolBar) {
					ofs << "            var cuttingPlaneCtr = new Communicator.Ui.CuttingPlaneController(hwv);" << endl;
					ofs << "            var toolbar = new Communicator.Ui.Toolbar(hwv, cuttingPlaneCtr, axisTriad, Communicator.ScreenConfiguration.Desktop);" << endl;
					ofs << "            toolbar.init();" << endl;
				}

				if (options.axisTriad) {
					ofs << "            var axisTriad = hwv.view.getAxisTriad().enable();" << endl;
				}

				if (options.navCube) {
					ofs << "            var navCube = hwv.view.getNavCube().enable();" << endl;
				}
				ofs << "        }" << endl;
				ofs << "    });" << endl;
			}

			if (options.customScriptBeforeStartViewer) {
				wcscpy(path, templateDirPath);
				wcscat(path, SCRIPT_CUSTOM_BEFORE_START_VIEWER);
				addFile(ofs, path);
			}
		}
		else
		{
			ofs << str << endl;
		}
		
	}
	ifs.close();

	if (options.standardUI || options.toolBar)
	{
		wcscpy(path, templateDirPath);
		wcscat(path, BODY_TOOLBAR_HTML);
		addFile(ofs, path);

		wcscpy(path, templateDirPath);
		wcscat(path, BODY_VIEWERSETTINGS_HTML);
		addFile(ofs, path);
	}

	if (options.customBody) {
		wcscpy(path, templateDirPath);
		wcscat(path, BODY_CUSTOM_HTML);
		addFile(ofs, path);
	}

	if (options.standardUI) {
		wcscpy(path, templateDirPath);
		wcscat(path, BODY_SNAPSHOT_DIALOG_HTML);
		addFile(ofs, path);
	}

	ofs << " </body>\n</html>" << endl;

	ofs.close();
}