workspace "GameEngine"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist" --[ Distribution]
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	IncludeDir = {}
	IncludeDir["glad"] = "Engine/vendor/glad/include"
	IncludeDir["glfw"] = "Engine/vendor/glfw/include"
	IncludeDir["glm"] = "Engine/vendor/glm"
	IncludeDir["imgui"] = "Engine/vendor/imgui"

	group "Dependencies"
		include "Engine/vendor/glad"
		include "Engine/vendor/glfw"
		include "Engine/vendor/imgui"
	group ""
	
	project "Engine"
		location "Engine"
		kind "SharedLib"
		language "C++"
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		pchheader "EnginePCH.h"
		pchsource "Engine/src/EnginePCH.cpp"

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
		"%{IncludeDir.glad}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}"
	}
	
	links
	{
		"glad",
		"glfw",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"ENGINE_PLATFORM_WINDOWS",
		"ENGINE_BUILD_DLL"
		--"GLFW_INCLUDE_NONE" --This is causing errors in your case so leave it for now
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
	}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		staticruntime "off"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		staticruntime "off"
		optimize "On"

	filter "configurations:Dist"
		defines "ENGINE_DIST"--[ Distribution]
		staticruntime "off"
		optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/vendor/spdlog/include",
		"Engine/src",
		"Engine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Engine",
		"imgui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	defines
	{
		"ENGINE_PLATFORM_WINDOWS",
	}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		staticruntime "off"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		staticruntime "off"
		optimize "On"

	filter "configurations:Dist"
		defines "ENGINE_DIST" --[ Distribution]
		staticruntime "off"
		optimize "On"
