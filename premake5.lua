workspace "RiceCube"
    startproject "RiceCube"

    configurations
    {
        "Debug",
        "Release"
    }

    platforms
    {
        "Win32",
        "Win64"
    }

    filter "platforms:Win32"
        system "Windows"
        architecture "x32"

    filter "platforms:Win64"
        system "Windows"
        architecture "x86_64"

outputdir = "%{cfg.platform}%{cfg.buildcfg}/%{prj.name}"

include "3rd/spdlog.lua"
include "3rd/glm.lua"
include "3rd/glfw.lua"
include "3rd/imgui.lua"

project "RiceCube"
    location "RiceCube"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir)
	objdir ("bin/obj/" .. outputdir)

    use_spdlog()
    use_glm()
    use_glfw()
    use_imgui()

    pchheader "ricepch.h"
    pchsource "%{prj.name}/src/ricepch.cpp"

    includedirs
    {
        "%{prj.name}/src"
    }

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug*"
        symbols "On"

    filter "configurations:Release*"
        optimize "On"