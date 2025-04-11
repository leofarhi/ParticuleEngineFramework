import os, sys
import json

local_path = os.path.dirname(os.path.abspath(__file__))

LIBS = ["SDL2.lib", "SDL2_image.lib", "SDL2_ttf.lib"]
DLLS = ["SDL2.dll", "SDL2_image.dll", "SDL2_ttf.dll", "libfreetype-6.dll", "libjpeg-9.dll", "libpng16-16.dll", "zlib1.dll", "libtiff-5.dll", "libwebp-7.dll"]

def normalize_path(path):
    path = os.path.normpath(path)  # Normalize the path
    path = os.path.abspath(path)  # Get absolute path
    path = path.replace("\\", "/")  # Replace backslashes with forward slashes
    return path

class MakeVisualStudio:
    def __init__(self, builder, path_build):
        self._builder = builder
        self.builder = builder.GetData()
        self.path_build = path_build
        self.config = self.GetConfig()
    @staticmethod
    def GetConfig():
        path = os.path.join(local_path,"..", "Config","config.json")
        if not os.path.exists(path):
            raise ValueError("Config file not found.")
        with open(path, "r") as f:
            config = json.load(f)
        return config
    
    def __Makefile__(self):
        path_lib = os.path.join(os.path.dirname(local_path),"Config","SDL2_Project","Lib",self.builder["architecture"])
        self.LIBS = ['"'+normalize_path(os.path.join(path_lib,lib))+'"' for lib in LIBS]
        self.DLLS = ['"'+normalize_path(os.path.join(path_lib,lib))+'"' for lib in DLLS]
        src_files = []
        source_dir = os.path.join(os.path.dirname(local_path), "Sources", "src")
        include_dirs = [normalize_path(os.path.join(os.path.dirname(local_path), "Sources", "Include")),
                        normalize_path(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(local_path))), "Interface", "include"))]
        for root, _, files in os.walk(source_dir):
            for f in files:
                if any(f.endswith(ext) for ext in [".cpp", ".c"]):
                    path = os.path.join(root, f)
                    src_files.append(normalize_path(path))
        for src_file in self.builder["source_files"]:
            if os.path.exists(src_file):
                src_files.append(normalize_path(src_file))
        for include_dir in self.builder["include_paths"]:
            if os.path.exists(include_dir):
                include_dirs.append(normalize_path(include_dir))
        SRC_FILES =""
        for idx, file in enumerate(src_files):
            if idx == len(src_files) - 1:
                SRC_FILES += f"  {file}\n"
            else:
                SRC_FILES += f"  {file} \\\n"
        icon_path = ""
        if self.builder["icon"] != "":
            icon_path = normalize_path(self.builder["icon"])
        if not os.path.isfile(icon_path):
            icon_path = ""
        makefile =f"""
SRC_FILES = \\\n{SRC_FILES}
INCLUDES = {" ".join(f"/I{d}" for d in include_dirs)}
LIBFLAGS = {" ".join(self.LIBS)}
ICON_PATH = "{icon_path}"

OUTPUT_NAME = MyApp
BUILD_DIR = Build
OUTPUT_DIR = Bin
# 1 = pas de console, 0 = console visible
NO_CONSOLE = {int(not self.builder["console"])}

# Fichiers objets dans BUILD_DIR
OBJ_FILES = $(SRC_FILES:.cpp=.obj)
OBJ_FILES = $(OBJ_FILES:.c=.obj)
OBJ_FILES = $(OBJ_FILES:Src\=$(BUILD_DIR)\)

# Icone .rc/.res
!if $(ICON_PATH) != ""
RES_FILE = $(BUILD_DIR)\icon.res
RES_RC = $(BUILD_DIR)\icon.rc
!endif

!if $(NO_CONSOLE)
SUBSYSTEM = /SUBSYSTEM:WINDOWS
!else
SUBSYSTEM = /SUBSYSTEM:CONSOLE
!endif

all: icon.res
	cl /nologo /std:c++20 /EHsc /Zi /MD $(INCLUDES) /Fo$(BUILD_DIR)\ /Fd$(BUILD_DIR)\$(OUTPUT_NAME).pdb $(SRC_FILES) \\
	/link $(LIBFLAGS) $(RES_FILE) $(SUBSYSTEM) /OUT:$(OUTPUT_DIR)\$(OUTPUT_NAME).exe

icon.res:
!if $(ICON_PATH) != ""
	@echo IDI_ICON1 ICON $(ICON_PATH) > $(RES_RC)
	rc /fo $(RES_FILE) $(RES_RC)
!endif
"""
        return makefile
    
    def __Buildfile__(self):
        VCVARS=self.config[self.builder["architecture"]]
        buildfile = f"""
@echo off
setlocal

mkdir Build 2>nul
mkdir Bin 2>nul

:: Définir le chemin vers vcvars
set VCVARS="{VCVARS}"

:: Vérifie si le fichier existe
if not exist %VCVARS% (
    echo Erreur : vcvars introuvable.
    pause
    exit /b 1
)

:: Appel de l'environnement de compilation Visual Studio
call %VCVARS%

nmake /f Makefile
pause
endlocal
"""
        return buildfile
    
    def Make(self):
        makefile = self.__Makefile__()
        buildfile = self.__Buildfile__()
        with open(os.path.join(self.path_build, "Makefile"), "w") as f:
            f.write(makefile)
        with open(os.path.join(self.path_build, "Build.bat"), "w") as f:
            f.write(buildfile)