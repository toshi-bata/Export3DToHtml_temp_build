#pragma once
#include <A3DSDKTypes.h>

struct Options
{
	bool standardUI = false;
	bool toolBar = false;
	bool axisTriad = false;
	bool navCube = false;
	bool customScript = false;
	bool customScriptBeforeStartViewer = false;
	bool customBody = false;
};

class HtmlTemplateBuilder
{
public:
	HtmlTemplateBuilder();
	~HtmlTemplateBuilder();
	void Create(const A3DUniChar*path);

	Options options;
};

