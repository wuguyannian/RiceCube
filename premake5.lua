workspace "RiceCube"
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

outputdir = "%{cfg.platform}%{cfg.buildcfg}"

include "3rd/spdlog.lua"

project "RiceCube"
    location "RiceCube"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin/int/"..outputdir.."/%{prj.name}")

    use_spdlog()

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