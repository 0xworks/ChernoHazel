project "Hazel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	configuration "vs*"
		buildoptions { "/permissive-" }

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
		"vendor/glm/glm/**.inl",
        "vendor/ImGuizmo/ImGuizmo.h",
        "vendor/ImGuizmo/ImGuizmo.cpp"
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
		"vendor/entt/include",
        "vendor/yamp-cpp/include",
        "vendor/ImGuizmo/include",
        "vulkanSDK goes here"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
        "yaml-cpp",
		"opengl32.lib"
	}

    filter "files:vendor/ImGuizmo/**.cpp"
    flags { "NoPCH" }

	filter "files:**/TracyClient.cpp"
		flags "NoPCH"

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

		links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

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

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}
	
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}