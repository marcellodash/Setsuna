workspace "Setsuna"
	location "build"
   	configurations { "Debug", "Release" }

project "Setsuna"
	kind "ConsoleApp"
	language "C"
	targetdir "."
	cdialect "C11"
	files { "src/**.h", "src/**.c" }

	includedirs{"src","include"}
	includedirs{"external/victorique/include"}
	libdirs{"external/victorique/lib"}
	links{"victorique"}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

include "external/victorique"