from PythonModules.BaseConfig import *
from PythonModules.MultiPlatform import *
from .MakeVersions.MakeVisualStudio import MakeVisualStudio

class MakeAppConfig(BaseMakeConfig):
    def __init__(self):
        super().__init__("Windows", False)
        self.assets_files = VarDict({
            "textures": VarList(VarDict({
                "path": VarPath("","(*.png, *.jpg)"),
                "reference_path": VarString("","(*.*)"),
            }),[], "Texture files"),
            "fonts": VarList(VarDict({
                "path": VarPath("","(*.ttf)"),
                "reference_path": VarString("","(*.*)"),
                "resolution": VarInt(8, "Resolution of the font"),
            }),[], "Font files"),
            "audio": VarList(VarPath("","(*.wav, *.mp3)"),[], "Audio files"),
            "other": VarList(VarDict({
                "path": VarPath("","(*.*)"),
                "reference_path": VarString("","(*.*)"),
            }),[], "Other files"),
        }, None, "Assets files to be included in the build")
        self.inputs = VarFreeDict(VarString("","key name"),VarEnum(["KEY_EXE"], "KEY_EXE", "input key"),{}, "Input files to be included in the build")
        self.icon = VarPath("icons.ico", "Icon file for unselected application")
        self.console = VarBool(False, "Enable console window")
        self.architecture = VarEnum(["x86", "x64"], "x64", "Architecture of the application")
        self.lib_api = VarEnum(["SDL2"], "SDL2", "API used for the application")
        self.compiler = VarEnum(["MSVC"], "MSVC", "Compiler used for the application")

    def Make(self):
        path_build = os.path.join(self.cwd, self.build_dir.ToData())
        if self.clean.ToData():
            print(f"Cleaning...")
            if os.path.exists(path_build):
                shutil.rmtree(path_build)
        os.makedirs(path_build, exist_ok=True)
        if self.lib_api.ToData() != "SDL2":
            raise ValueError("Only SDL2 is supported for now.")
        if self.compiler.ToData() != "MSVC":
            raise ValueError("Only MSVC is supported for now.")
        maker = MakeVisualStudio(self, path_build)
        maker.Make()

class MakeLibConfig(BaseMakeConfig):
    def __init__(self):
        super().__init__("Windows", True)
        