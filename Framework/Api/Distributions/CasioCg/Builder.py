from PythonModules.BaseConfig import *
from PythonModules.MultiPlatform import *
from .Extra import *
import os, sys
import shutil


class MakeAppConfig(BaseMakeConfig):
    def __init__(self):
        super().__init__("CasioCg", False)
        self.libraries = VarList(VarString("","*.a"),[], "Libraries to link against")
        self.compile_flags = VarString("","Additional flags for the compiler")
        self.link_flags = VarString("","Additional flags for the linker")
        self.assets_files = VarDict({
            "textures": VarList(VarDict({
                "path": VarPath("","(*.png, *.jpg)"),
                "reference_path": VarString("","(*.*)"),
                "format": VarEnum(["rgb565", "p8", "p4"], "rgb565", "Texture format"),
                "alpha": VarBool(False, "Enable alpha channel"),
                "external": VarBool(False, "Use external texture"),
            }),[], "Texture files"),
            "fonts": VarList(VarDict({
                "path": VarPath("","(*.ttf)"),
                "reference_path": VarString("","(*.*)"),
                "resolution": VarInt(8, "Resolution of the font"),
            }),[], "Font files"),
            "other": VarList(VarDict({
                "path": VarPath("","(*.*)"),
                "reference_path": VarString("","(*.*)"),
            }),[], "Other files")
        }, None, "Assets files to be included in the build")
        self.inputs = VarFreeDict(VarString("","key name"),VarEnum(KEY_INPUTS, "KEY_EXE", "input key"),{}, "Input files to be included in the build")
        self.display_name = VarString("MyApp", "Display name of the application (8 characters max)")
        self.icon_uns = VarPath("icon-uns.png", "Icon file for unselected application")
        self.icon_sel = VarPath("icon-sel.png", "Icon file for selected application")

    def Load(self, config):
        super().Load(config)
        #check display name length
        if len(self.display_name.ToData()) > 8:
            raise ValueError("Display name must be 8 characters or less")
        
    def __CreateAssets__(self, path_build, asset_uuid):
        asset_build_path = os.path.join(path_build, "assets")
        os.makedirs(asset_build_path, exist_ok=True)
        assets_files = self.assets_files.ToData()
        #copy assets to build directory
        asset_added = ["fxconv-metadata.txt"]
        for texture in assets_files["textures"]:
            if not texture["external"]:
                src_path = texture["path"]
                if not os.path.exists(src_path):
                    raise ValueError(f"Texture file {src_path} does not exist")
                dst_path = os.path.join(asset_build_path, asset_uuid.GetUUID_file(src_path))
                asset_added.append(asset_uuid.GetUUID_file(src_path))
                copy = True
                if os.path.exists(dst_path):
                    if CheckIfBinFileIsSame(src_path, dst_path):
                        copy = False
                if copy:
                    print(f"Copying {src_path} to {dst_path}")
                    shutil.copy(src_path, dst_path)
        for asset in os.listdir(asset_build_path):
            if asset not in asset_added:
                os.remove(os.path.join(asset_build_path, asset))
        for texture in assets_files["textures"]:
            if not texture["external"]:
                uuid_file = asset_uuid.GetUUID_file(texture["path"])
                uuid_name = "___IMG_"+asset_uuid.GetUUID(texture["path"])
                format = texture["format"]
                if texture["alpha"] and format == "rgb565":
                    format += "a"
                dt = f"{uuid_file}:\n\tname: {uuid_name}\n\ttype: bopti-image\n\tformat: {format}\n"
        #create fxconv-metadata.txt
        #check if fxconv-metadata.txt exists and if it is the same
        metadata_path = os.path.join(asset_build_path, "fxconv-metadata.txt")
        if not CheckIfContentIsSame(metadata_path, dt):
            with open(metadata_path, "w") as f:
                f.write(dt)

    def __CreateRedefine__(self, path_build, asset_uuid):
        #create redefine.h
        redefine_path = os.path.join(path_build, "include", "ParticuleApi", "System", "Redefine.hpp")
        os.makedirs(os.path.dirname(redefine_path), exist_ok=True)
        PlayerInput = ""
        for key, value in self.inputs.ToData().items():
            PlayerInput += f'\n(__builtin_constant_p(str) && __builtin_strcmp(str, "{key}") == 0) ? Input(gint::{value}) : \\'
        Resources = {}
        References = {}
        for texture in self.assets_files.ToData()["textures"]:
            if not texture["external"]:
                uuid = asset_uuid.GetUUID(texture["path"])
                Resources[uuid] = texture["format"]
                References[uuid] = texture["reference_path"]
        Resources_ext_txt = ""
        for key, value in Resources.items():
            Resources_ext_txt +="extern gint::image_t ___IMG_"+key+";\n"
        Resources_txt =""
        idx_uuid = {}
        if "rgb565" in Resources.values():
            Resources_txt +="    const Texture imgsRGB565[] = {\n"
            idx = 0
            for key, value in Resources.items():
                if value == "rgb565":
                    Resources_txt +="        Texture(&___IMG_"+key+", false),\n"
                    idx_uuid[key] = idx
                    idx += 1
            Resources_txt +="    };\n"
        if "p8" in Resources.values():
            Resources_txt +="    const TextureP8 imgsP8[] = {\n"
            idx = 0
            for key, value in Resources.items():
                if value == "p8":
                    Resources_txt +="        TextureP8(&___IMG_"+key+"),\n"
                    idx_uuid[key] = idx
                    idx += 1
            Resources_txt +="    };\n"
        if "p4" in Resources.values():
            Resources_txt +="    const TextureP4 imgsP4[] = {\n"
            idx = 0
            for key, value in Resources.items():
                if value == "p4":
                    Resources_txt +="        TextureP4(&___IMG_"+key+"),\n"
                    idx_uuid[key] = idx
                    idx += 1
            Resources_txt +="    };\n"
        GetResource = ""
        for key, value in Resources.items():
            reference_path = References[key]
            if reference_path == "":
                reference_path = GetPathLinux(asset_uuid.GetPath(key),self.cwd)
            GetResource += f'\n(__builtin_constant_p(str) && __builtin_strcmp(str, "{reference_path}") == 0) ? Resource((void*)(&(Resources::imgs{value.upper()}[{idx_uuid[key]}]))) : \\'
        #for asset in self.assets_files.ToData():
        dt = """#ifndef REDEFINE_HPP
#define REDEFINE_HPP
#include <ParticuleApi/Graphics/Image/Texture.hpp>
#include <ParticuleApi/System/Resource.hpp>
#include <ParticuleApi/System/Input.hpp>
#include <ParticuleApi/System/gint.hpp>

"""+Resources_ext_txt+"""

namespace Particule::Api::Resources
{
    """+Resources_txt+"""
}

namespace Particule::Api
{
    #ifndef PlayerInput
    #define PlayerInput(str)(\\"""+PlayerInput+"""
    Input())
    #endif

    #ifndef GetResource
    #define GetResource(str)(\\"""+GetResource+"""
    Resource(str))
    #endif
}

#endif"""
        if not CheckIfContentIsSame(redefine_path, dt):
            with open(redefine_path, "w") as f:
                f.write(dt)


    def __BuildPreparation__(self):
        path_build = os.path.join(self.cwd, self.build_dir.ToData())
        if self.clean.ToData():
            print(f"Cleaning...")
            if os.path.exists(path_build):
                shutil.rmtree(path_build)
        os.makedirs(path_build, exist_ok=True)
        #check if asset_uuid.json exists in path_build
        asset_uuid_path = os.path.join(path_build, "asset_uuid.json")
        if not os.path.exists(asset_uuid_path):
            asset_uuid = StaticAssetConfg()
        else:
            asset_uuid = StaticAssetConfg()
            with open(asset_uuid_path, "r") as f:
                data = json.load(f)
                asset_uuid.Load(data)
        asset_uuid.Update(self.assets_files)
        asset_uuid.Save(asset_uuid_path)
        self.__CreateAssets__(path_build, asset_uuid)
        makefile_path = os.path.join(path_build, "CMakeLists.txt")
        self.__CreateRedefine__(path_build, asset_uuid)
        dt = self.__MakeFile__(asset_uuid)
        if not CheckIfContentIsSame(makefile_path, dt):
            with open(makefile_path, "w") as f:
                f.write(dt)
    def __MakeFile__(self,asset_uuid):
        path_build = os.path.join(self.cwd, self.build_dir.ToData())
        local_path_linux = GetPathLinux(local_path)
        project_name = self.project_name.ToData()
        source_files = "\n".join([GetPathLinux(path) for path in self.source_files.ToData()])
        include_paths = "\n".join([GetPathLinux(path) for path in self.include_paths.ToData()])
        library_paths = "\n".join([GetPathLinux(path) for path in self.library_paths.ToData()])
        libraries = " ".join(self.libraries.ToData())
        compile_flags = self.compile_flags.ToData()
        link_flags = self.link_flags.ToData()
        defines = ""
        for key, value in self.defines.ToData().items():
            defines += f"{key}={value} "
        defines = defines.strip()
        debug_text = ""
        if self.debug.ToData():
            defines += " DEBUG=1"
            debug_text ="""target_compile_options(myaddin PRIVATE
    -fno-builtin-malloc
    -fno-builtin-free
    -fno-builtin-realloc
    -fno-builtin-calloc
    -fno-builtin-new
    -fno-builtin-delete
    )
"""

        assets = self.assets_files.ToData()
        assets_cg = ""
        for asset in asset_uuid.assets.ToData():
            assets_cg += f'assets/{asset_uuid.GetUUID_file(asset["path"])}\n'
        return f"""cmake_minimum_required(VERSION 3.15)
project("{project_name}")

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.11 REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE API_SRCS
    {local_path_linux}/Sources/src/*.cpp
)
set(SOURCES
    ${{API_SRCS}}
    {source_files}
)

include_directories(
    ${{CMAKE_CURRENT_SOURCE_DIR}}/include
    {local_path_linux}/Sources/include
    {local_path_linux}/../../Interface/include
    {include_paths}
)

link_directories(
    {library_paths}
)
set(LIBRARIES
{libraries}
)

set(ASSETS_cg
{assets_cg}
)

fxconv_declare_assets(${{ASSETS}} ${{ASSETS_fx}} ${{ASSETS_cg}} WITH_METADATA)
add_executable({project_name} ${{SOURCES}} ${{ASSETS}} ${{ASSETS_${{FXSDK_PLATFORM}}}})
target_compile_options({project_name} PRIVATE -Os -std=c++20 -fno-freestanding {compile_flags})
target_compile_definitions({project_name} PRIVATE {defines})
{debug_text}
target_link_libraries({project_name} Gint::Gint ${{LIBRARIES}} -lsupc++ -lstdc++ {link_flags})

generate_g3a(TARGET {project_name} OUTPUT "{self.output_file.ToData()}.g3a"
    NAME "{self.display_name.ToData()}" ICONS "{GetPathLinux(self.icon_uns.ToData(),path_build)}" "{GetPathLinux(self.icon_sel.ToData(), path_build)}")
"""

    def Make(self):
        self.__BuildPreparation__()
        path_build = os.path.join(self.cwd, self.build_dir.ToData())
        ret = ProcessLinuxValue("fxsdk build-cg", path_build)
        if ret != 0:
            raise ValueError("\033[91mBuild failed !\033[0m")
        else:
            #copy assets to build directory
            bin_generated = os.path.join(path_build, self.output_file.ToData()+".g3a")
            dest = os.path.join(self.cwd, self.bin_dir.ToData(), self.output_file.ToData()+".g3a")
            os.makedirs(os.path.dirname(dest), exist_ok=True)
            shutil.copy(bin_generated, dest)
            print("\033[92mBuild finished successfully !\033[0m")

class MakeLibConfig(BaseMakeConfig):
    def __init__(self):
        super().__init__("CasioCg", True)
        self.libraries = VarList(VarString("","*.a"),[], "Libraries to link against")
        self.compile_flags = VarString("","Additional flags for the compiler")
        self.link_flags = VarString("","Additional flags for the linker")

    def Make(self):
        pass#todo: implement the build process