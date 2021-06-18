include "../Dependencies.lua"

project "Hazelnut"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"%{wks.location}/Hazel/src",
		"%{wks.location}/Hazel/vendor",   -- this one is actually for imgui (hazel code goes #include imgui/imgui.h)
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.spdlog}"
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


	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
