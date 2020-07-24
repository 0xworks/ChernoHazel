project "Hazel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "src/hzpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor/Glad/include",
		"vendor/GLFW/include",
		"vendor/glm",
		"vendor/imgui",
		"vendor/spdlog/include",
		"vendor/stb_image",
		"vendor/entt/include"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Profile"
		files "../vendor/Tracy/TracyClient.cpp"
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

	filter "files:**/TracyClient.cpp"
		flags "NoPCH"
	