include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Hazel"
	architecture "x86_64"
	startproject "Hazelnut"

	configurations
	{
		"Debug",
		"Profile",
		"Release"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	-- From VS2019 16.9.0 onwards, multiprocessor compile can cause
	-- error "C1041 cannot open program database if multiple CL.EXE write to the same .PDB file, please use /FS"
	-- There are two solutions:
	-- Either:  Add /FS, as I have done here (for VS builds only)
	-- Or:      Do not use multiprocessor build in conjuction with MTT (https://devblogs.microsoft.com/cppblog/improved-parallelism-in-msbuild/)
	--
	-- I have gone with the former because MTT is better, and I dont want to disable it.
	filter { "action:vs*" }
		buildoptions
		{
			"/FS"
		}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Hazel/vendor/GLFW"
	include "Hazel/vendor/Glad"
	include "Hazel/vendor/imgui"
	include "Hazel/vendor/yaml-cpp"
group ""
	include "Hazel"
	include "Hazelnut"
	include "Sandbox"
