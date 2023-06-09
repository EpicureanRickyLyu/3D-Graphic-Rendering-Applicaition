-- premake5.lua -- only support 2019 currently
workspace "Hazel"
   architecture "x64"
   startproject "SandBox"
   configurations 
   { 
       "Debug", 
       "Release",
       "Dist"
   }



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include dependencies--

IncludeDir = {}

IncludeDir["GLFW"] = "Hazel/Vendor/GLFW/include"
IncludeDir["GLAD"] = "Hazel/Vendor/GLAD/include"
IncludeDir["ImGui"] = "Hazel/Vendor/imgui"

include "Hazel/Vendor/GLFW"
include "Hazel/Vendor/GLAD"
include "Hazel/Vendor/imgui"
-----------------------------Hazel--------------------------------------------

project "Hazel"
   location "Hazel"
   kind "SharedLib" -- dynamic library
   language "C++"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   pchheader "pch.h" -- equal use pch for solution
   pchsource "Hazel/src/pch.cpp" -- equal set pch.h to create pch

   -- files that want to be build
   files 
   { 
       "%{prj.name}/src/**.h", 
       "%{prj.name}/src/**.cpp", 
   }

   includedirs
   {
       "%{prj.name}/src",
       "%{prj.name}/Vendor/spdlog/include",
       "%{IncludeDir.GLFW}",
       "%{IncludeDir.GLAD}",
       "%{IncludeDir.ImGui}",
   }

   links
   {
       "GLFW",
       "GLAD",
       "ImGui",
       "opengl32.lib",
       "Dwmapi.lib"
   }

   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"

      defines 
      { 
          "HZ_PLATFORM_WINDOWS",
          "HZ_BUILD_DLL",
          "GLFW_INCLUDE_NONE",
          "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
      }

      postbuildcommands
      {
          --copy dll into sandbox
          ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
      }

   filter "configurations:Debug"
      defines "HZ_DEBUG"
      buildoptions "/MDd"
      symbols "On"
    
   filter "configurations:Release"
      defines "HZ_RELEASE"
      buildoptions "/MD"
      optimize "On"

   filter "configurations:Dist"
      defines "HZ_DIST"
      buildoptions "/MD"
      optimize "On"
   
      
------------------------------------SandBox---------------------------------

project "SandBox"
    location "SandBox"
    kind "ConsoleApp" -- App
    language "C++"
        
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")   
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp", 
    }

    includedirs
    {
        "Hazel/Vendor/spdlog/include";
        "Hazel/src"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        { 
            "HZ_PLATFORM_WINDOWS",
        }

        links
        {
            "Hazel"
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        buildoptions "/MDd"
        symbols "On"
    
    filter "configurations:Release"
        defines "HZ_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "HZ_DIST"
        buildoptions "/MD"
        optimize "On"



    