from PythonModules.BaseConfig import *
from PythonModules.MultiPlatform import *
from PythonModules.BaseInstaller import *
from .Config.vcvars import find_vcvars
import os, sys
import shutil
import subprocess
import json

local_path = os.path.dirname(os.path.realpath(__file__))

class Installer(BaseInstaller):
    def __init__(self):
        self.vcvars_list = find_vcvars()
    def install(self):
        print("Installing distribution...")
        if len(self.vcvars_list) == 0:
            raise ValueError("No Visual Studio installation found. Please install Visual Studio. (preferred 2022)")
        if self.is_installed():
            raise ValueError("The distribution is already installed.")
        zip_path = os.path.join(local_path, "Config", "SDL2_Project.zip")
        if not os.path.exists(zip_path):
            raise ValueError("SDL2_Project.zip not found.")
        shutil.unpack_archive(zip_path, os.path.join(local_path, "Config", "SDL2_Project"), "zip")
        self.configure()
        print("Installation completed successfully.")
    
    def is_installed(self):
        if len(self.vcvars_list) == 0:
            return False
        if not os.path.exists(os.path.join(local_path, "Config","SDL2_Project")):
            return False
        if not os.path.exists(os.path.join(local_path, "Config", "config.json")):
            return False
        return True
    
    def configure(self):
        choiceX64 = 0
        for idx, entry in enumerate(self.vcvars_list):
            print(f"[{idx+1}] Visual Studio {entry['version']} {entry['edition']} → {entry['path']}")
        choice = 0
        while choice < 1 or choice > len(self.vcvars_list):
            try:
                choice = int(input("Select the Visual Studio version to use for x64 (1-{}): ".format(len(self.vcvars_list))))
            except ValueError:
                print("Invalid choice. Please enter a number.")
        choiceX64 = self.vcvars_list[choice-1]
        choice = 0
        while choice < 1 or choice > len(self.vcvars_list):
            try:
                choice = int(input("Select the Visual Studio version to use for x86 (1-{}): ".format(len(self.vcvars_list))))
            except ValueError:
                print("Invalid choice. Please enter a number.")
        choiceX86 = self.vcvars_list[choice-1]
        with open(os.path.join(local_path, "Config", "config.json"), "w") as f:
            json.dump({
                "x64": choiceX64["path"],
                "x86": choiceX86["path"],
            }, f, indent=4)
    
    def update(self):
        print("No update available for this distribution.")

    def uninstall(self):
        raise NotImplementedError("Uninstall method not implemented.")