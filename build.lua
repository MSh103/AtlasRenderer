project "AtlasRenderer"
        kind "StaticLib"
        language "C++"

        targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
        
        files
        {
                "source/**.h",
                "source/**.hpp",
                "source/**.cpp"
        }

        includedirs
        {
                "source",
                "%{IncludeDir.AtlasLib}",
                "%{IncludeDir.Glad}",
                "%{IncludeDir.glm}",
        }

        links
        {
                "Glad"
        }

        
        filter "system:windows"
                cppdialect "C++latest"
                staticruntime "off"
                systemversion "latest"

                defines 
                {
                    "AT_PLATFORM_WINDOWS",
                }

        filter "configurations:Debug"
                defines "AT_DEBUG"
                symbols "on"
                runtime "Debug"

        filter "configurations:Release"
                defines "AT_RELEASE"
                optimize "on"
                runtime "Release"