workspace "Broccoli"

	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	startproject "Sandbox"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"



project "Broccoli"

	location "Broccoli"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BRCL_PLATFORM_WINDOWS",
			"BRCL_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	
	filter "configurations:Debug"
		defines "BRCL_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "BRCL_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "BRCL_DIST"
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
		"Broccoli/vendor/spdlog/include",
		"Broccoli/src"
	}
	
	links
	{
		"Broccoli"
	}
	
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BRCL_PLATFORM_WINDOWS"
		}
		
	
	filter "configurations:Debug"
		defines "BRCL_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "BRCL_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "BRCL_DIST"
		optimize "On"