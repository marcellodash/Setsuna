workspace "Kazusa"
	location "build"
   configurations { "Debug", "Release" }

project "Kazusa"
	kind "ConsoleApp"
	language "C"
	targetdir "."
	cdialect "C11"
	files { "src/**.h", "src/**.c" }

	includedirs{"src"}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
