#pragma once

#include "Core.h"

namespace Clever {
	
	class CLEVER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}