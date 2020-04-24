project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
	    "../Hazel/src",
	    "../Hazel/vendor/glm",
	    "../Hazel/vendor",                      -- this one is actually for imgui (hazel code goes #include imgui/imgui.h)
	    "../Hazel/vendor/spdlog/include",
	}

	links
	{
		"Hazel"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
