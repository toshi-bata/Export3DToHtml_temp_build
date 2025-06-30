#pragma once

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
	void Create(const wchar_t *path);

	Options options;
};

