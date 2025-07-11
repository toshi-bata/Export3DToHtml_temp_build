#include "HtmlTemplateBuilder.h"
#include <fstream>
#include <string>
#include <iostream>
#include <tchar.h>

using namespace std;
#define HEAD_HTML							_T("01_head.html")
#define SCRIPT_JQUERY_HTML					_T("02_script_jquery.html")
#define SCRIPT_UI_HTML						_T("03_script_UI_interaction.html")
#define SCRIPT_HWV_HTML						_T("04_script_HWV.html")
#define SCRIPT_JQUERY_MINICOLORS_HTML		_T("05_script_jquery_minicolors.html")
#define SCRIPT_HWV_SERVER_HTML				_T("06_script_HWV_server.html")
#define SCRIPT_HWV_SAMPLE_HTML				_T("07_script_HWV_sample.html")
#define STYLE_MODELTREE_HTML				_T("08_style_modelTree.html")
#define STYLE_TOOLBAR_HTML					_T("09_style_toolBar.html")
#define STYLE_COMMON_HTML					_T("10_style_common.html")
#define STYLE_JQUERY_HTML					_T("11_style_jquery.html")
#define STYLE_VIEWER_DIALOGS_HTML			_T("12_style_viewer_dialogs.html")
#define STYLE_JQUERY_MINICOLORS_HTML		_T("13_style_jquery_minicolors.html")
#define STYLE_RELATIONSHIPA_HTML			_T("14_style_relationships.html")
#define CUSTOM_STYLE_SCRIPT_HTML			_T("15_custom_style_script.html")
#define SCRIPT_START_VIEWER_HTML			_T("16_script_start_viewer.html")
#define CUSTOM_SCRIPT_BEFORE_START_VIEWER	_T("17_custom_script_before_start_viewer.js")
#define BODY_TOOLBAR_HTML					_T("18_body_toolbar.html")
#define BODY_VIEWERSETTINGS_HTML			_T("19_body_viewerSettings.html")
#define BODY_SNAPSHOT_DIALOG_HTML			_T("20_body_snapshot_dialog.html")
#define CUSTOM_BODY_HTML					_T("21_custom_body.html")

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
	wcscat(path, _T("_htmltemplate.html"));
	ofs.open(path, ios::out | ios::trunc);
	
	wcscpy(path, templateDirPath);
	wcscat(path, HEAD_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, SCRIPT_JQUERY_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, SCRIPT_UI_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, SCRIPT_HWV_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, SCRIPT_JQUERY_MINICOLORS_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, SCRIPT_HWV_SERVER_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, SCRIPT_HWV_SAMPLE_HTML);
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

	wcscpy(path, templateDirPath);
	wcscat(path, STYLE_JQUERY_HTML);
	addFile(ofs, path);

	if (options.standardUI || options.toolBar) {
		wcscpy(path, templateDirPath);
		wcscat(path, STYLE_VIEWER_DIALOGS_HTML);
		addFile(ofs, path);
	}

	wcscpy(path, templateDirPath);
	wcscat(path, STYLE_JQUERY_MINICOLORS_HTML);
	addFile(ofs, path);

	wcscpy(path, templateDirPath);
	wcscat(path, STYLE_RELATIONSHIPA_HTML);
	addFile(ofs, path);

	if (options.customScript) {
		wcscpy(path, templateDirPath);
		wcscat(path, CUSTOM_STYLE_SCRIPT_HTML);
		addFile(ofs, path);
	}

	wcscpy(path, templateDirPath);
	wcscat(path, SCRIPT_START_VIEWER_HTML);
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
					ofs << "            var cuttingPlaneCtr = new Communicator.Ui.CuttingPlane.Controller(hwv);" << endl;
					ofs << "            var toolbar = new Communicator.Ui.Toolbar(hwv, cuttingPlaneCtr, Communicator.ScreenConfiguration.Desktop);" << endl;
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
				wcscat(path, CUSTOM_SCRIPT_BEFORE_START_VIEWER);
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

	if (options.standardUI) {
		wcscpy(path, templateDirPath);
		wcscat(path, BODY_SNAPSHOT_DIALOG_HTML);
		addFile(ofs, path);
	}

	if (options.customBody) {
		wcscpy(path, templateDirPath);
		wcscat(path, CUSTOM_BODY_HTML);
		addFile(ofs, path);
	}

	ofs << " </body>\n</html>" << endl;

	ofs.close();
}