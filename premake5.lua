workspace "Broccoli"

	architecture "x86_64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
	startproject "Sandbox"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Broccoli/vendor/glfw/include"
IncludeDir["Glad"] = "Broccoli/vendor/glad/include"
IncludeDir["ImGui"] = "Broccoli/vendor/imgui"
IncludeDir["Blaze"] = "Broccoli/vendor/blaze"
IncludeDir["Stb"] = "Broccoli/vendor/stb"
IncludeDir["EnTT"] = "Broccoli/vendor/entt/include"
IncludeDir["YAML"] = "Broccoli/vendor/yaml-cpp/include"


group "Dependencies"
	include "Broccoli/vendor/imgui"
	include "Broccoli/vendor/glfw"
	include "Broccoli/vendor/glad"
	include "Broccoli/vendor/yaml-cpp"

group ""
project "Broccoli"

	location "Broccoli"
	kind "StaticLib"
	staticruntime "On"
	language "C++"
	cppdialect "C++17"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "brclpch.h"
	pchsource "Broccoli/src/brclpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb/**.cpp",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/blaze/**.h",
		"%{prj.name}/vendor/entt/**.hpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.EnTT}",
		"%{IncludeDir.Blaze}",
		"%{IncludeDir.Stb}",
		"%{IncludeDir.YAML}"
	}

	links
	{
		"Glad",
		"GLFW",
		"ImGui",
		"opengl32.lib",
		"Broccoli/vendor/openblas/libopenblas.lib"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"BLAS_BLAS_IS_64BIT"
	}

	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"GLFW_INCLUDE_NONE",
			"BRCL_PLATFORM_WINDOWS"
		}
	
	
	filter "configurations:Debug"
		defines "BRCL_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "BRCL_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "BRCL_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"

	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "On"
	language "C++"
	cppdialect "C++17"
	
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
		"%{IncludeDir.Blaze}",
		"%{IncludeDir.EnTT}",
		"Broccoli/src",
		"Broccoli/vendor"
	}
	
	links
	{
		"Broccoli"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"BLAS_BLAS_IS_64BIT"
	}
	
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"BRCL_PLATFORM_WINDOWS"
		}
		
	
	filter "configurations:Debug"
		defines "BRCL_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "BRCL_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "BRCL_DIST"
		runtime "Release"
		optimize "on"


project "Harvest"

	location "Harvest"
	kind "ConsoleApp"
	staticruntime "On"
	language "C++"
	cppdialect "C++17"
	
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
		"%{IncludeDir.Blaze}",
		"%{IncludeDir.EnTT}",
		"Broccoli/src",
		"Broccoli/vendor"
	}
	
	links
	{
		"Broccoli"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"BLAS_BLAS_IS_64BIT"
	}
	
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"BRCL_PLATFORM_WINDOWS"
		}
		
	
	filter "configurations:Debug"
		defines "BRCL_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "BRCL_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "BRCL_DIST"
		runtime "Release"
		optimize "on"