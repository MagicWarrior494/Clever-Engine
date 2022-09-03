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
IncludeDir["stb_image"] = "Clever/vendor/stb_image"
IncludeDir["Assimp"] = "Clever/vendor/Assimp/assimp/include"

include "Clever/vendor/GLFW"
include "Clever/vendor/Glad"
include "Clever/vendor/imgui"
include "Clever/vendor/Assimp/assimp"

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
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/Assimp/assimp/include/assimp/**.hpp",
		"%{prj.name}/vendor/Assimp/assimp/include/assimp/**.h"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.Assimp}"
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
		"opengl32.lib",
		"assimp"
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
		"%{IncludeDir.Assimp}",
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