workspace "Clever"
	architecture "x64"
	startproject "Sandbox"
	
	
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
IncludeDir["Glad"] = "Clever/vendor/Glad/include"
IncludeDir["ImGui"] = "Clever/vendor/imgui"
IncludeDir["glm"] = "Clever/vendor/glm"
IncludeDir["assimp"] = "Clever/vendor/assimp"

include "Clever/vendor/GLFW"
include "Clever/vendor/Glad"
include "Clever/vendor/imgui"
include "Clever/vendor/assimp"

project "Clever"
	location "Clever"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/".. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/".. outputdir .. "/%{prj.name}")

	pchheader "cvpch.h"
	pchsource "Clever/src/cvpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.assimp}"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"assimp",
		"opengl32.lib"
	}
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CV_PLATFORM_WINDOWS",
			"CV_BUILD_DLL",
			"CV_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "CV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CV_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"
	
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
		"Clever/src",
		"Clever/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Clever"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CV_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CV_DIST"
		runtime "Release"
		optimize "on"