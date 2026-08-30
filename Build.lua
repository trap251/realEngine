workspace("realEngine")
    location("realEngine")
    architecture("x64")
    configurations({ "Debug", "Release" })
    startproject("realEngine")

    OutputDir = "%{cfg.buildcfg}_%{cfg.architecture}/"

project("realEngine")
    location("realEngine/realEngine")
    kind("ConsoleApp")
    language("C++")
    cppdialect("C++20")
    targetdir("realEngine/build/out/" .. OutputDir .. "")
    staticruntime("off")

    objdir("realEngine/build/inter/" .. OutputDir .. "")
    files({
    	"realEngine/realEngine/Source/**",
    	"realEngine/realEngine/Vendor/glad/src/glad.c",
    	"realEngine/realEngine/main.cpp"
    })

    includedirs({
    	"realEngine",
    	"realEngine/realEngine",
    	"realEngine/realEngine/Source",
    	"realEngine/realEngine/Vendor/include",
    })

    libdirs({
    	"realEngine/realEngine/Vendor/lib",
    })


    filter("system:windows")
        systemversion("latest")
        defines({ "WINDOWS" })
        links({
           	"glfw3",
           	"opengl32",
        })

    filter("system:linux")
        systemversion("latest")
        defines({ "LINUX" })
        links({
           	"glfw",
           	"GL",
           	"pthread",
           	"dl",
           	"X11",
        })
        postbuildcommands({
           	"{COPYDIR} realEngine/realEngine/Resources %{cfg.targetdir}",
        })

    filter("configurations:Debug")
        defines({ "DEBUG" })
        runtime("Debug")
        symbols("On")

    filter("configurations:Release")
        defines({ "RELEASE" })
        runtime("Release")
        optimize("On")
        symbols("On")
