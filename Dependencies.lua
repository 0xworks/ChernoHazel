-- Hazel Dependencies

function get_directory_name(path)
      return path:match("[^@].*[\\/]")
end

ROOT = get_directory_name(debug.getinfo(1,'S').source)

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["entt"]        = "%{ROOT}Hazel/vendor/entt/src/entt"
IncludeDir["Glad"]        = "%{ROOT}Hazel/vendor/Glad/include"
IncludeDir["GLFW"]        = "%{ROOT}Hazel/vendor/GLFW/include"
IncludeDir["glm"]         = "%{ROOT}Hazel/vendor/glm"
IncludeDir["ImGui"]       = "%{ROOT}Hazel/vendor/ImGui"
IncludeDir["ImGuizmo"]    = "%{ROOT}Hazel/vendor/ImGuizmo"
IncludeDir["shaderc"]     = "%{ROOT}Hazel/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{ROOT}Hazel/vendor/SPIRV-Cross"
IncludeDir["spdlog"]      = "%{ROOT}Hazel/vendor/spdlog/include"
IncludeDir["stb_image"]   = "%{ROOT}Hazel/vendor/stb_image"
IncludeDir["yaml_cpp"]    = "%{ROOT}Hazel/vendor/yaml-cpp/include"

IncludeDir["VulkanSDK"]   = "%{VULKAN_SDK}/Include"


LibraryDir = {}

LibraryDir["VulkanSDK"]             = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"]       = "%{ROOT}Hazel/vendor/VulkanSDK/Lib"

Library = {}
Library["Vulkan"]                   = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"]              = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"]            = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"]        = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"]   = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"]        = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"]          = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"]      = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
