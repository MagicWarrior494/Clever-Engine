workspace "Clever"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Includes directoies relative to root folder (solution directory)

IncludeDir = {}
IncludeDir["GLFW"] = "Clever/vendor/GLFW/include"

include "Clever/vendor/GLFW"

project "Clever"
	location "Clever"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/".. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/".. outputdir .. "/%{prj.name}")

	pchheader "cvpch.h"
	pchsource "Clever/src/cvpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}
	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CV_PLATFORM_WINDOWS",
			"CV_BUILD_DLL",
			"CV_ENABLE_ASSERTS";
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CV_DIST"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/".. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/".. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Clever/vendor/spdlog/include",
		"Clever/src"
	}

	links
	{
		"Clever"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CV_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CV_DIST"
		optimize "On"