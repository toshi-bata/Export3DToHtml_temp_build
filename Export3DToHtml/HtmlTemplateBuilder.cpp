#include "HtmlTemplateBuilder.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>

#ifdef _MSC_VER
#include <tchar.h>
#define MY_TEXT(x) _T(x)
#else
#include <string.h>
#define TCHAR char
#define MY_TEXT(x) x
#define _tcscpy strcpy
#define _tcscat strcat
#define _stprintf sprintf
#endif

using namespace std;
#define TEMP_FILE_NAME						MY_TEXT("_htmltemplate.html")
#define HEAD_HTML							MY_TEXT("01_head.html")
#define SCRIPT_JQUERY_HTML					MY_TEXT("02_script_jquery.html")
#define SCRIPT_UI_HTML						MY_TEXT("03_script_UI_interaction.html")
#define SCRIPT_HWV_HTML						MY_TEXT("04_script_HWV.html")
#define SCRIPT_JQUERY_MINICOLORS_HTML		MY_TEXT("05_script_jquery_minicolors.html")
#define SCRIPT_HWV_SERVER_HTML				MY_TEXT("06_script_HWV_server.html")
#define SCRIPT_HWV_SAMPLE_HTML				MY_TEXT("07_script_HWV_sample.html")
#define STYLE_MODELTREE_HTML				MY_TEXT("08_style_modelTree.html")
#define STYLE_TOOLBAR_HTML					MY_TEXT("09_style_toolBar.html")
#define STYLE_COMMON_HTML					MY_TEXT("10_style_common.html")
#define STYLE_JQUERY_HTML					MY_TEXT("11_style_jquery.html")
#define STYLE_VIEWER_DIALOGS_HTML			MY_TEXT("12_style_viewer_dialogs.html")
#define STYLE_JQUERY_MINICOLORS_HTML		MY_TEXT("13_style_jquery_minicolors.html")
#define STYLE_RELATIONSHIPA_HTML			MY_TEXT("14_style_relationships.html")
#define CUSTOM_STYLE_SCRIPT_HTML			MY_TEXT("15_custom_style_script.html")
#define SCRIPT_START_VIEWER_HTML			MY_TEXT("16_script_start_viewer.html")
#define CUSTOM_SCRIPT_BEFORE_START_VIEWER	MY_TEXT("17_custom_script_before_start_viewer.js")
#define BODY_TOOLBAR_HTML					MY_TEXT("18_body_toolbar.html")
#define BODY_VIEWERSETTINGS_HTML			MY_TEXT("19_body_viewerSettings.html")
#define BODY_SNAPSHOT_DIALOG_HTML			MY_TEXT("20_body_snapshot_dialog.html")
#define CUSTOM_BODY_HTML					MY_TEXT("21_custom_body.html")

void strmarge(const A3DUniChar*in_str1, const A3DUniChar*in_str2, A3DUniChar* out_str)
{
	_tcscpy(out_str, in_str1);
	_tcscat(out_str, in_str2);
}

void addFile(ofstream &ofs, const A3DUniChar*inFile)
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

void HtmlTemplateBuilder::Create(const A3DUniChar*templateDirPath)
{
	ofstream ofs;
	ifstream ifs;
	string str;
	A3DUniChar path[2048];
	
	strmarge(templateDirPath, TEMP_FILE_NAME, path);
	ofs.open(path, ios::out | ios::trunc);
	
	strmarge(templateDirPath, HEAD_HTML, path);
	addFile(ofs, path);

	strmarge(templateDirPath, SCRIPT_JQUERY_HTML, path);
	addFile(ofs, path);

	strmarge(templateDirPath, SCRIPT_UI_HTML, path);
	addFile(ofs, path);

	strmarge(templateDirPath, SCRIPT_HWV_HTML, path);
	addFile(ofs, path);

	strmarge(templateDirPath, SCRIPT_JQUERY_MINICOLORS_HTML, path);
	addFile(ofs, path);

	strmarge(templateDirPath, SCRIPT_HWV_SERVER_HTML, path);
	addFile(ofs, path);

	strmarge(templateDirPath, SCRIPT_HWV_SAMPLE_HTML, path);
	addFile(ofs, path);

	if (options.standardUI) {
		strmarge(templateDirPath, STYLE_MODELTREE_HTML, path);
		addFile(ofs, path);
	}

	if (options.standardUI || options.toolBar) {
		strmarge(templateDirPath, STYLE_TOOLBAR_HTML, path);
		addFile(ofs, path);
	}

	strmarge(templateDirPath, STYLE_COMMON_HTML, path);
	addFile(ofs, path);

	strmarge(templateDirPath, STYLE_JQUERY_HTML, path);
	addFile(ofs, path);

	if (options.standardUI || options.toolBar) {
		strmarge(templateDirPath, STYLE_VIEWER_DIALOGS_HTML, path);
		addFile(ofs, path);
	}

	strmarge(templateDirPath, STYLE_JQUERY_MINICOLORS_HTML, path);
	addFile(ofs, path);

	strmarge(templateDirPath, STYLE_RELATIONSHIPA_HTML, path);
	addFile(ofs, path);

	if (options.customScript) {
		strmarge(templateDirPath, CUSTOM_STYLE_SCRIPT_HTML, path);
		addFile(ofs, path);
	}

	strmarge(templateDirPath, SCRIPT_START_VIEWER_HTML, path);
	ifs.open(path);
	while (getline(ifs, str)) 
	{
		if (0 == strncmp(str.data(), "//BEFORE_START_VIEWER", 21))
		{
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
				strmarge(templateDirPath, CUSTOM_SCRIPT_BEFORE_START_VIEWER, path);
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
		strmarge(templateDirPath, BODY_TOOLBAR_HTML, path);
		addFile(ofs, path);

		strmarge(templateDirPath, BODY_VIEWERSETTINGS_HTML, path);
		addFile(ofs, path);
	}

	if (options.standardUI) {
		strmarge(templateDirPath, BODY_SNAPSHOT_DIALOG_HTML, path);
		addFile(ofs, path);
	}

	if (options.customBody) {
		strmarge(templateDirPath, CUSTOM_BODY_HTML, path);
		addFile(ofs, path);
	}

	ofs << " </body>\n</html>" << endl;

	ofs.close();
}