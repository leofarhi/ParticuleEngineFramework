from PythonModules.BaseConfig import *
from PythonModules.MultiPlatform import *
import os, sys
import shutil


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
            "other": VarList(VarPath("","(*.*)"),[], "Other files")
        }, {}, "Assets files to be included in the build")
        self.inputs = VarFreeDict(VarString("","key name"),VarEnum(["KEY_EXE"], "KEY_EXE", "input key"),{}, "Input files to be included in the build")
        self.icon = VarPath("icons.ico", "Icon file for unselected application")

class MakeLibConfig(BaseMakeConfig):
    def __init__(self):
        super().__init__("Windows", True)
        