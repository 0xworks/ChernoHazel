project "Hazelnut"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	configuration "vs*"
		buildoptions { "/permissive-" }

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING"
	}

	includedirs
	{
		"../Hazel/src",
		"../Hazel/vendor/glm",
		"../Hazel/vendor",                      -- this one is actually for imgui (hazel code goes #include imgui/imgui.h)
		"../Hazel/vendor/spdlog/include",
		"../Hazel/vendor/entt/include"
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

	filter "configurations:Profile"
		defines
		{
			"HZ_PROFILE",
			"TRACY_ENABLE"
		}
		runtime "Release"
		optimize "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"
