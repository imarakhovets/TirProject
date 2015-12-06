#include "stdafx.h"
//#include "MyApplication.h"
#include "TestAppDelegate.h"

#define MYAPPLICATION_NAME "Test"

#define MYSETTINGS_REG_KEY "Software\\Playrix Entertainment\\EngineTest"
#define MYWINDOW_CLASS_NAME "ENGINETEST_CLASS"
#define MYAPPLICATION_NAME "Engine Test"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*
	bool fullscreen = false;

	Core::log.Init("log.htm", true);

	File::c_file settings("settings.ini");

	if (!settings.is_open())
		return -1;
	
	std::string str = settings.getline();
	while (!str.empty())
	{
		std::string name, value;
		if (utils::ReadNvp(str, name, value))
		{
			if (name == "path")
			{
				File::cd(value);
			}
			else if (name == "fullscreen")
			{
				fullscreen = utils::lexical_cast<bool>(value);
			}
		}
		
		str = settings.getline();
	}

	HWND hWnd = ::FindWindow(MYWINDOW_CLASS_NAME, MYAPPLICATION_NAME);
	if (hWnd == NULL)
	{
		if (CheckDXVersion())
		{
			MyApplication application(hInstance, nCmdShow, fullscreen);
			application.enableCustomCursor = false;
			application.showFps = true;
			application.maxFps = 0;
			application.SETTINGS_REG_KEY = MYSETTINGS_REG_KEY;
			application.APPLICATION_NAME = MYAPPLICATION_NAME;
			application.WINDOW_CLASS_NAME = MYWINDOW_CLASS_NAME;
			application.Init(true);
			application.Start();
			application.ShutDown();
		}
	}
	else
	{
		::SetForegroundWindow(hWnd);
		::SetFocus(hWnd);
		::UpdateWindow(hWnd);
	}
	
	return 0;
	*/

	ParticleSystem::SetTexturesPath("textures/Particles");

	Core::fileSystem.SetWriteDirectory("./write_directory");
	Core::fileSystem.MountDirectory("base_p");

	Log::log.AddSink(new Log::HtmlFileLogSink("log.htm", true));

	Core::Application::APPLICATION_NAME = MYAPPLICATION_NAME;

	Core::RunApplicationWithDelegate(new TestAppDelegate());

	return 0;
}
