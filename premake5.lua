workspace "rpipr"
    configurations { "Debug", "Release" }

project "rpipr"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"
    objdir "obj/%{cfg.buildcfg}"
    targetdir "build/%{cfg.buildcfg}"

files {
    "src/**.cpp"
}

includedirs {
    "include"
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
