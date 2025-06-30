/***********************************************************************************************************************
*
* Copyright (c) 2010 - 2025 by Tech Soft 3D, Inc.
* The information contained herein is confidential and proprietary to Tech Soft 3D, Inc., and considered a trade secret
* as defined under civil and criminal statutes. Tech Soft 3D shall pursue its civil and criminal remedies in the event
* of unauthorized use or misappropriation of its trade secrets. Use of this information by anyone other than authorized
* employees of Tech Soft 3D, Inc. is granted only under a written non-disclosure agreement, expressly prescribing the
* scope and manner of such use.
*
***********************************************************************************************************************/

/*
 * This sample demonstrates how to load a model and export it as HTML or SCS format. The chosen
 * format is determined by the file extension of the output file name.
 * -- HTML Export:
 * . The HTML output file is self-contenant without external dependancies and can be read as-is in a web browser.
 * . The HTML is generated from a template HTML file provided as input. A template sample is provided in the package.
 * -- SCS Export:
 * . The SCS output file is a cache file to be reffered by a html file. The html file should typically be launched into
 * a web server.
 * . The package provides a sample HTTP server for that usage. See \samples\publish\publishhtml\htmlforserver\.
 */

#define INITIALIZE_A3D_API
#define HOOPS_PRODUCT_PUBLISH_ADVANCED
#include <A3DSDKIncludes.h>
#include <hoops_license.h>
#include "../common.hpp"
#include <iostream>
#include <sstream>
#include "HtmlTemplateBuilder.h"

//######################################################################################################################
// Usage: All parameters are defaultable.
// Export3DToHtml [INPUT] [HTML] [FORMAT] [OUTPUT] [LOG_FILE]
// - INPUT    : The path to the input CAD file. Defaults to IN_FILE
// - HTML     : The HTML template used by the exporter. Default to IN_FILE_HTMLTEMPLATE
// - FORMAT   : The export format. Must be either 'html' or 'scs'. Defaults to "html".
// - OUTPUT   : The path to output file.
//            : If FORMAT=html, defaults to OUT_FILE_HTML
//            : Else          , defaults to OUT_FILE_SCS
// - LOG_FILE : The output log file. If not specified, the program writes in:
//            : SAMPLES_PUBLISH_HTML_DIRECTORY/htmlsinglefile/Export3DToHtml.log.txt for html
//            : SAMPLES_PUBLISH_HTML_DIRECTORY/htmlforserver/export3dtohtml/Export3DToHtml.log.txt for scs
#ifdef _MSC_VER
#	define IN_FILE                _T(SAMPLES_DATA_DIRECTORY"\\prc\\helloworld.prc")
#	define IN_FILE_HTMLTEMPLATE   _T(SAMPLES_DATA_HTML_DIRECTORY"\\export3dtohtml_template.html")
#	define IN_EXPORTFORMAT        _T("html") // values are "html" or "scs"
#	define OUT_FILE_SCS           _T(SAMPLES_PUBLISH_HTML_DIRECTORY"\\htmlforserver\\export3dtohtml\\root\\helloworld.scs")
#	define OUT_FILE_HTML          _T(SAMPLES_PUBLISH_HTML_DIRECTORY"\\htmlsinglefile\\helloworld.html")
#else
#	define IN_FILE                SAMPLES_DATA_DIRECTORY"/prc/helloworld.prc"
#	define IN_FILE_HTMLTEMPLATE   SAMPLES_DATA_HTML_DIRECTORY"/export3dtohtml_template.html"
#	define IN_EXPORTFORMAT        "html" // values are "html" or "scs"
#	define OUT_FILE_SCS           SAMPLES_PUBLISH_HTML_DIRECTORY"/htmlforserver/export3dtohtml/root/helloworld.scs"
#	define OUT_FILE_HTML          SAMPLES_PUBLISH_HTML_DIRECTORY"/htmlsinglefile/helloworld.html"
#endif

bool ReadPdfFileWithPrcStream(A3DImport const& a_sImport, A3DAsmModelFile*& a_psModelFile);

//######################################################################################################################
#ifdef _MSC_VER
int wmain(A3DInt32 iArgc, A3DUniChar** ppcArgv)
#else
int main(int iArgc, A3DUTF8Char** ppcArgv)
#endif
{
#ifndef _MSC_VER
	setenv("LC_NUMERIC", "en_US.UTF-8", 1); // Locally force locale
#endif

	if (iArgc > 6)
	{
		printf("Usage: Export3DToHtml [INPUT] [HTML] [FORMAT] [OUTPUT] [LOG_FILE]\nAll parameters are defaultable.\nSee source file for details.\n");
		return 0;
	}

	bool bExportAsHtml = false;
	if (iArgc > 3)
		bExportAsHtml = (MY_STRCMP(ppcArgv[3], "html") == 0);
	else
		bExportAsHtml = (MY_STRCMP(IN_EXPORTFORMAT, "html") == 0);

	if (!(iArgc >= 6 && stdout != GetLogFile(ppcArgv[5])))
	{
		// if no log file specified on command line or redirection failed, fall back to local file
#ifdef _MSC_VER
		if (bExportAsHtml)
			GetLogFile(_T(SAMPLES_PUBLISH_HTML_DIRECTORY"\\htmlsinglefile\\Export3DToHtml.log.txt"));
		else
			GetLogFile(_T(SAMPLES_PUBLISH_HTML_DIRECTORY"\\htmlforserver\\export3dtohtml\\Export3DToHtml.log.txt"));
#else
		if (bExportAsHtml)
			GetLogFile(SAMPLES_PUBLISH_HTML_DIRECTORY"/htmlsinglefile/Export3DToHtml.log.txt");
		else
			GetLogFile(SAMPLES_PUBLISH_HTML_DIRECTORY"/htmlforserver/export3dtohtml/Export3DToHtml.log.txt");
#endif
	}

	std::wstringstream bin_dir;
	std::wstring buffer;
	buffer.resize(MAX_PATH);
	if (GetEnvironmentVariable(L"HPUBLISH_INSTALL_DIR", &buffer[0], static_cast<DWORD>(buffer.size())))
		bin_dir << buffer.data() << L"/bin/win64_v142\0";
	else
		bin_dir << "\0";

	A3DSDKHOOPSExchangeLoader sHoopsExchangeLoader(bin_dir.str().data(), HOOPS_LICENSE);
	CHECK_RET(sHoopsExchangeLoader.m_eSDKStatus)
	CHECK_RET(A3DDllSetCallbacksMemory(CheckMalloc, CheckFree));
	CHECK_RET(A3DDllSetCallbacksReport(PrintLogMessage, PrintLogWarning, PrintLogError))

	// specify input file
	A3DImport sImport(iArgc > 1 ? ppcArgv[1] : IN_FILE);

	A3DAsmModelFile* psModelFile = nullptr;
	if(ReadPdfFileWithPrcStream(sImport, psModelFile) == false)
	{
		CHECK_RET(A3DAsmModelFileLoadFromFile(sImport.GetFilePath(), &sImport.m_sLoadData, &psModelFile));
	}

	if (psModelFile)
	{
		if (bExportAsHtml)
		{
			// specify output file
			A3DExport sExport(iArgc > 4 ? ppcArgv[4] : OUT_FILE_HTML);
			sExport.m_sExportHtmlData.m_bIncludeMeasurementInformation = true;

#if defined _MSC_VER && (defined _UNICODE || defined UNICODE)
			std::vector< A3DUTF8Char> acTempFilePathUTF8 ;
			A3DUniChar* acTempDirUni;
			A3DUniChar acTempFilePathUni[MAX_PATH];
			if (iArgc > 2)
			{
				acTempDirUni = ppcArgv[2];
				wcscpy(acTempFilePathUni, ppcArgv[2]);
				wcscat(acTempFilePathUni, _T("\\_htmltemplate.html"));
			}
			else
			{
				acTempDirUni = const_cast<A3DUniChar*>(IN_FILE_HTMLTEMPLATE);
				wcscpy(acTempFilePathUni, const_cast<A3DUniChar*>(IN_FILE_HTMLTEMPLATE));
				wcscat(acTempFilePathUni, _T("\\_htmltemplate.html"));
			}

			acTempFilePathUTF8.resize(wcslen(acTempFilePathUni) * sizeof(A3DUniChar));
			A3DMiscUTF16ToUTF8(acTempFilePathUni, acTempFilePathUTF8.data());
			sExport.m_sExportHtmlData.m_pcHtmlTemplateName = acTempFilePathUTF8.data();
#else
			sExport.m_sExportHtmlData.m_pcHtmlTemplateName = (A3DUTF8Char *)(iArgc > 2 ? ppcArgv[2] : IN_FILE_HTMLTEMPLATE);
#endif

			// create HTML template file
			HtmlTemplateBuilder createTemplate;
			createTemplate.options.standardUI = true;
			createTemplate.options.toolBar = false;
			createTemplate.options.axisTriad = true;
			createTemplate.options.navCube = true;
			createTemplate.options.customScript = false;
			createTemplate.options.customScriptBeforeStartViewer = false;
			createTemplate.options.customBody = false;
			createTemplate.Create(acTempDirUni);

			// conversion is performed
			CHECK_RET(A3DAsmModelFileExportToHTMLFile(psModelFile, &sExport.m_sExportHtmlData, sExport.GetFilePath()));
		}
		else
		{
			// specify output file
			A3DExport sExport(iArgc > 4 ? ppcArgv[4] : OUT_FILE_SCS);
			sExport.m_sExportScsData.m_bIncludeMeasurementInformation = true;

			// conversion is performed
			CHECK_RET(A3DAsmModelFileExportToSCSFile(psModelFile, &sExport.m_sExportScsData, sExport.GetFilePath()));
		}

		A3DAsmModelFileDelete(psModelFile);
	}

	// Check memory allocations
	return (int)ListLeaks();
}

bool ReadPdfFileWithPrcStream(A3DImport const& a_sImport, A3DAsmModelFile*& a_psModelFile)
{
	if (strstr(a_sImport.GetFilePath(), ".pdf") != nullptr)
	{
		A3DStream3DPDFData* pStream3DPDFData;
		A3DInt32 iNumStreams;
		A3DStatus iRet = A3DPDFGetStreams(a_sImport.GetFilePath(), kA3DPDFFilterNativeViews, &pStream3DPDFData, &iNumStreams);
		if (iRet != A3D_SUCCESS || iNumStreams == 0)
		{
			return false;
		}

		// a real use case might parse every streams in the input file. Here we just take the first one (pStream3DPDFData[0]).

		// even an input PRC file must be read in memory and mapped into modelfile data structures
		if (pStream3DPDFData[0].m_bIsPrc)
		{
			iRet = A3DAsmModelFileLoadFromPrcStream(pStream3DPDFData[0].m_acStream, pStream3DPDFData[0].m_uiStreamSize, NULL, &a_psModelFile);
		}

		A3DPDFGetStreams(nullptr, kA3DPDFFilterNativeViews, &pStream3DPDFData, &iNumStreams);	// to clean up the array of stream data
		return iRet == A3D_SUCCESS && a_psModelFile != nullptr;
	}
	else
	{
		return false;
	}
}