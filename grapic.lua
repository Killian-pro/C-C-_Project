
solution "grapic"

	configurations { "debug", "release" }
	-- platforms { "native", "x32", "x64"  }
	-- platforms { "x64", "x32"  }
	-- platforms { "native" }

	--~ location ("build/" .. os.get() .. "/" .. _ACTION)
	location ("build/" .. os.get())

	objdir "./obj"
	includedirs { ".", "./src" }


	configuration { "linux" }
		includedirs { "/usr/include/SDL2" }
		buildoptions { "-std=c++11" }
		buildoptions { "-ggdb"}
		linkoptions { "-ggdb"}
		buildoptions { "-W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-unused-but-set-variable -Wno-narrowing" }
		links { "SDL2", "SDL2_image", "SDL2_ttf" }

		

	configuration { "windows" }
		defines { "WIN32", "NVWIDGETS_EXPORTS", "_USE_MATH_DEFINES", "_CRT_SECURE_NO_WARNINGS" }
		defines { "NOMINMAX" } -- allow std::min() and std::max() in vc++ :(((

	configuration { "windows", "gmake" }
		buildoptions { "-std=c++11" }
		buildoptions { "-W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-unused-but-set-variable -Wno-narrowing" }
		buildoptions { "-g"}
		linkoptions { "-g"}
		includedirs { "extern/mingw/include", "extern/mingw/include/SDL2" }
		libdirs { "extern/mingw/lib" }
		links { "mingw32", "SDL2main", "SDL2", "SDL2_image", "SDL2_ttf" }

	configuration { "windows", "codeblocks" }
		buildoptions { "-std=c++11" }
		buildoptions { "-g"}
		linkoptions { "-g"}
		buildoptions { "-W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-unused-but-set-variable -Wno-narrowing" }
		includedirs { "extern/mingw/include", "extern/mingw/include/SDL2" }
		libdirs { "extern/mingw/lib" }
		links { "mingw32", "SDL2main", "SDL2", "SDL2_image", "SDL2_ttf" }

	configuration { "windows", "vs2015"}
		if _PREMAKE_VERSION >="5.0" then
			system "Windows"
			architecture "x64"
		end
		buildoptions { "-g"}
		includedirs { "extern/visual2015/include", "extern/visual2015/include/SDL2" }
		libdirs { "extern/visual2015/lib" }
		links { "SDL2", "SDL2main", "SDL2_image", "SDL2_ttf"}

		
		
	configuration "macosx"
		buildoptions { "-W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-narrowing" }
		buildoptions { "-std=c++11" }
		includedirs {	"extern/macosx/SDL2.framework/Versions/A/Headers/",
						"extern/macosx/SDL2.framework/Versions/A/Headers/SDL2",
						"extern/macosx/SDL2_image.framework/Versions/A/Headers",
						"extern/macosx/SDL2_ttf.framework/Versions/A/Headers" }
		linkoptions {	"../../extern/macosx/SDL2.framework/Versions/A/SDL2",
						"../../extern/macosx/SDL2_image.framework/Versions/A/SDL2_image",
						"../../extern/macosx/SDL2_ttf.framework/Versions/A/SDL2_ttf",
						"-rpath @executable_path/../extern/macosx"
						}




-- description des fichiers communs
function make_project(name, filesToCompile)
	project(name)
		language "C++"
		kind "ConsoleApp"
		targetdir "bin"
		files { "src/Grapic.cpp", "src/Grapic.h",
				"src/Grapic_func.cpp", "src/Grapic_func.h",
			}
		files { filesToCompile }
end


-- description des projets
make_project( "Start", "apps/start/main_start.cpp" )





newoption {
   trigger     = "target",
   value       = "TGT",
   description = "Choose a particular sub-list of projects",
   allowed = {
      { "standard",	"All project except beta" },
      { "beta",  	"Future project" },
   }
}



if not _OPTIONS["target"] then
   _OPTIONS["target"] = "standard"
end

-- zzz (future projects)
if _OPTIONS["target"] == "beta" then
	make_project( "zzz_Fluid", 								"apps/zzz_fluid/main_fluid.cpp" )
	make_project( "zzz_particles", 							"apps/zzz_particles/main_particles.cpp" )
	make_project( "zzz_lifami_TD1_Complex",					"apps/zzz_lifami/T1_TD1-TP-TP_Complex.cpp" )
	make_project( "zzz_lifami_TD2_Interpolation",			"apps/zzz_lifami/T2_TD2-TP-TP_Interpolation.cpp" )
	make_project( "zzz_lifami_TD3_ParticlesBasic",			"apps/zzz_lifami/T3_TD3-TP-TP_ParticlesBasic.cpp" )
	make_project( "zzz_lifami_TD3_Particles",				"apps/zzz_lifami/T3_TD3-TP-TP_Particles.cpp" )
	make_project( "zzz_lifami_TD4_MassSpring",				"apps/zzz_lifami/T3_TD4-TP_MassSpring.cpp" )
	make_project( "zzz_lifami_TD4_Asteroid",				"apps/zzz_lifami/T3_TD4-TP_Particles.cpp" )
	make_project( "zzz_lifami_TD4-Fluid",					"apps/zzz_lifami/T3_TD4-TP_fluid.cpp" )
	make_project( "zzz_lifami_TD6_TP-TP_ProiesPredateurs",	"apps/zzz_lifami/T4_TD6_TP-TP_ProiesPredateurs.cpp" )
	make_project( "zzz_lifami_TD7-TP-TP_ColorInsects",		"apps/zzz_lifami/T4_TD7-TP-TP_ColorInsects.cpp" )
	make_project( "zzz_lifami_TD8-TP-TP_EcoIcecreamShop",	"apps/zzz_lifami/T5_TD8-TP-TP_EcoIcecreamShop.cpp" )
	make_project( "zzz_lifami_TPnote_Water",				"apps/zzz_lifami/T9_TPnote_Water.cpp" )
	make_project( "zzz_lifami_test",						"apps/zzz_lifami/test.cpp" )
end
