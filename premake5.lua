imgui_params = {
    files = {
        "vendor/imgui/*.cpp",
        "vendor/imgui/*.h",
        "vendor/imgui/backends/imgui_impl_sdlrenderer2.*",
        "vendor/imgui/backends/imgui_impl_sdl2.*",
        "vendor/imgui/misc/cpp/imgui_stdlib.*"
    },
    includes = {
        "vendor/imgui/",
        "vendor/imgui/backends/",
        "vendor/imgui/misc/cpp/"
    }
}

workspace "rpipr"
    configurations { "Debug", "Release" }

project "rpipr"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"
    objdir "obj/%{cfg.buildcfg}"
    targetdir "build/%{cfg.buildcfg}"

files {
    imgui_params.files,
    "vendor/imfile_dialog/ImGuiFileDialog.cpp",
    "src/**.cpp"
}

includedirs {
    "include",
    "vendor/imfile_dialog",
    imgui_params.includes
}

links {
    "sqlite3"
}

buildoptions {
    "-Wall", "`pkg-config sdl2 --static --cflags`"
}

linkoptions {
    "`pkg-config sdl2 --static --libs`"
}

-- filters

filter "configurations:Debug"
    symbols "On"
    defines { "ROC_DEBUG" }
