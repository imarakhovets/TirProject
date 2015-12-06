#pragma once



#include "Gun.h"
#include "Target.h"
#include "PhysxSpace.h"
#include "TirSpace.h"

extern bool needLoadScreen;

///
/// ����� ���������� ����� �������, �� ������������ ��������� ���� ����.
///
class MyApplication : public Core::Application
{
public:
	MyApplication(HINSTANCE hInstance, int nCmdShow, bool fullscreen)
		: Application(hInstance, nCmdShow, fullscreen)
	{
		//
		// ����� ������� ������ �������� ������ � ���������� ��������.
		//
		// ��� ������, ��� � � �������, � � ������������� ������ ������ ������
		// ������ ����� ����� 1024x768 "��������".
		//
		GAME_CONTENT_WIDTH = 1024;
		GAME_CONTENT_HEIGHT = 768;
	}
	
	///
	/// ����� �������������� ���������������� ���� � Lua � �������.
	///
	void RegisterTypes() {
		Application::RegisterTypes();

		//
		// ����� ����� ���� ������������ ������������ ������ � xml �� �����,
		// ��� ���������� ���������������� ����� �������.
		//
		

		REGISTER_WIDGET_XML(TirSpace, "TirSpace");
		REGISTER_WIDGET_XML(Gun, "Gun");
	}
	
	///
	/// ����� LoadResources ���������� ����� ������� �������� �����.
	///
	void LoadResources()
	{
		//
		// ������ � ���� ������ ����������� ������, � ������� ������������,
		// ����� ������� ����� ��������� � ����� ������� ���� �������� �� �����.
		//
		Core::LuaDoFile("startup.lua");
	}

	///
	/// ����� DrawFps ���������� ����� ���� ������ ���������, ���� �����������
	/// �������� application.showFps = true.
	///
	void DrawFps()
	{
		if (!Render::isFontLoaded("default"))
		{
			return;
		}
		
		//
		// ����� ������� ������ Render::PrintString() ����� ��������� ������ �����
		//
		Render::BindFont("default");
		
		int dy = Render::getFontHeight();
		
		int x = Render::device.Width() - dy;
		int y = Render::device.Height() - 2 * dy;
		
		Render::PrintString(x, y, std::string("FPS: ") + utils::lexical_cast(currentFps), 1.0f, RightAlign);
		Render::PrintString(x, y - 1 * dy, std::string("Vm: ") + utils::lexical_cast(Render::device.GetVideoMemUsage()) + std::string("MB"), 1.0f, RightAlign);
		Render::PrintString(x, y - 2 * dy, std::string("Am: ") + utils::lexical_cast(MM::manager.GetMemUsage()) + std::string("KB"), 1.0f, RightAlign);
	}
};