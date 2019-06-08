function use_imgui()
    includedirs "3rd/imgui"
    links "ImGui"
end

project "ImGui"
    location "imgui"
    kind "StaticLib"
    language "C++"

    targetdir ("../bin/" .. outputdir)
    objdir ("../bin/obj/" .. outputdir)
    
    files
    {
        "%{prj.name}/imconfig.h",
        "%{prj.name}/imgui.h",
        "%{prj.name}/imgui.cpp",
        "%{prj.name}/imgui_draw.cpp",
        "%{prj.name}/imgui_internal.h",
        "%{prj.name}/imgui_widgets.cpp",
        "%{prj.name}/imstb_rectpack.h",
        "%{prj.name}/imstb_textedit.h",
        "%{prj.name}/imstb_truetype.h",
        "%{prj.name}/imgui_demo.cpp"
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"

    filter { "system:windows", "configurations:Release"}
        buildoptions "/MT"
