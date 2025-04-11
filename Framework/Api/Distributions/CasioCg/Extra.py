from PythonModules.BaseConfig import *
from PythonModules.MultiPlatform import *
import os
import uuid
local_path = os.path.dirname(os.path.abspath(__file__))

KEY_INPUTS = [
"KEY_F1",
"KEY_F2",
"KEY_F3",
"KEY_F4",
"KEY_F5",
"KEY_F6",
"KEY_SHIFT",
"KEY_OPTN",
"KEY_VARS",
"KEY_MENU",
"KEY_LEFT",
"KEY_UP",
"KEY_ALPHA",
"KEY_SQUARE",
"KEY_POWER",
"KEY_EXIT",
"KEY_DOWN",
"KEY_RIGHT",
"KEY_XOT",
"KEY_LOG",
"KEY_LN",
"KEY_SIN",
"KEY_COS",
"KEY_TAN",
"KEY_FRAC",
"KEY_FD",
"KEY_LEFTP",
"KEY_RIGHTP",
"KEY_COMMA",
"KEY_ARROW",
"KEY_7",
"KEY_8",
"KEY_9",
"KEY_DEL",
"KEY_4",
"KEY_5",
"KEY_6",
"KEY_MUL",
"KEY_DIV",
"KEY_1",
"KEY_2",
"KEY_3",
"KEY_ADD",
"KEY_SUB",
"KEY_0",
"KEY_DOT",
"KEY_EXP",
"KEY_NEG",
"KEY_EXE",
"KEY_ACON",
"KEY_HELP",
"KEY_LIGHT",
"KEY_KBD",
"KEY_X",
"KEY_Y",
"KEY_Z",
"KEY_EQUALS",
"KEY_CLEAR",
"KEY_X2",
"KEY_CARET",
"KEY_SWITCH",
"KEY_LEFTPAR",
"KEY_RIGHTPAR",
"KEY_STORE",
"KEY_TIMES",
"KEY_PLUS",
"KEY_MINUS",
]

def uuid4():
    """Generate a random UUID4 string."""
    return str(uuid.uuid4()).replace("-", "_")

def CheckIfBinFileIsSame(path1, path2):
    """Check if binary files are the same."""
    if os.path.exists(path1) and os.path.exists(path2):
        with open(path1, "rb") as f1, open(path2, "rb") as f2:
            return f1.read() == f2.read()
    return False

def CheckIfContentIsSame(file_path, new_content):
    """Check if file content is the same."""
    if os.path.exists(file_path):
        with open(file_path, "r") as f:
            return f.read() == new_content
    return False

class StaticAssetConfg(BaseConfig):
    def __init__(self):
        super().__init__()
        self.assets = VarList(VarDict({
                "path": VarPath("","(*.*)"),
                "uuid": VarString(uuid4(), "UUID of the asset"),
            }),[], "Assets in the build")

    def AddAsset(self, path):
        #check if path is already in the list
        for asset in self.assets.ToData():
            if asset["path"] == path:
                return
        #add Asset to the list
        data = self.assets.type_instance.Clone()
        data.Load({
            "path": path,
            "uuid": uuid4()
        })
        self.assets.value.append(data)

    def RemoveAsset(self, path):
        #remove Asset from the list
        for idx, asset in enumerate(self.assets.ToData()):
            if asset["path"] == path:
                self.assets.value.pop(idx)
                return
    
    def GetUUID(self, path):
        #get the UUID of the asset
        for asset in self.assets.ToData():
            if asset["path"] == path:
                return asset["uuid"]
        return None
    
    def GetUUID_file(self, path):
        #get the UUID of the asset
        for asset in self.assets.ToData():
            if asset["path"] == path:
                ext = os.path.splitext(path)[1]
                return asset["uuid"]+ext
        return None
    
    def GetPath(self, uuid):
        #get the path of the asset
        for asset in self.assets.ToData():
            if asset["uuid"] == uuid:
                return asset["path"]
        return None
    
    def Update(self, assets_files):
        assets_files = assets_files.ToData()
        all_paths = []
        for texture in assets_files["textures"]:
            if not texture["external"]:
                self.AddAsset(texture["path"])
                all_paths.append(texture["path"])
        for font in assets_files["fonts"]:
            self.AddAsset(font["path"])
            all_paths.append(font["path"])
        #remove assets not in the list
        for asset in self.assets.ToData():
            if asset["path"] not in all_paths:
                self.RemoveAsset(asset["path"])

    def Save(self, path):
        with open(path, "w") as f:
            json.dump(self.GetData(), f, indent=4)