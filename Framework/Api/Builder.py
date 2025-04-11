from PythonModules.BaseConfig import *
import os, sys
import traceback
import subprocess
import importlib
import shutil
import argparse
import json

current_working_directory = os.getcwd()

local_path = os.path.dirname(os.path.realpath(__file__))
#set current working directory to local_path
os.chdir(local_path)
Distributions = {}
for dist_name in os.listdir(os.path.join(local_path, "Distributions")):
    #check if dir/Distribution.py exists
    file = os.path.join(local_path, "Distributions", dist_name, "Distribution.py")
    if os.path.exists(file):
        module_name = f"Distributions.{dist_name}.Distribution"
        module = importlib.import_module(module_name)
        class_names = ["MakeAppConfig", "MakeLibConfig"]
        attrs = {}
        for class_name in class_names:
            if hasattr(module, class_name):
                attrs[class_name] = getattr(module, class_name)
            else:
                print(f"Error: {class_name} not found in {module_name}")
        if len(attrs) == len(class_names):
            Distributions[dist_name] = attrs

os.chdir(current_working_directory)

class MakefileParser:
    def __init__(self, is_library):
        self.makefiles = {}
        self.is_library = is_library
        if is_library:
            self.common = BaseMakeConfig("common", True)
            for dist_name, classes in Distributions.items():
                self.makefiles[dist_name] = classes["MakeLibConfig"]()
        else:
            self.common = BaseMakeConfig("common", False)
            for dist_name, classes in Distributions.items():
                self.makefiles[dist_name] = classes["MakeAppConfig"]()

    def SetCwd(self, path):
        self.common.cwd = path
        for makefile in self.makefiles.values():
            makefile.cwd = path

    def ExportData(self):
        common_data = self.common.GetData(exclude_common=False)
        del common_data["distribution"]
        outs = {self.common.distribution.ToData(): common_data}
        for makefile in self.makefiles.values():
            data = makefile.GetData(exclude_common=True)
            del data["distribution"]
            outs[makefile.distribution.ToData()] = data
        return outs
    
    def ExportConfig(self):
        common_config = self.common.GetConfig(exclude_common=False)
        del common_config["distribution"]
        outs = {self.common.distribution.ToData(): common_config}
        for makefile in self.makefiles.values():
            config = makefile.GetConfig(exclude_common=True)
            del config["distribution"]
            outs[makefile.distribution.ToData()] = config
        return outs
    
    @staticmethod
    def LoadData(config):
        config = json.loads(json.dumps(config))
        is_library = config["common"]["is_library"]
        makefile = MakefileParser(is_library)
        makefile.makefiles = {}
        makefile.common.Load(config["common"])
        del config["common"]
        for dist_name, dist_config in config.items():
            if dist_name not in Distributions:
                raise ValueError(f"Error: Unknown distribution '{dist_name}'")
            baseData = makefile.common.GetData(exclude_common=False)
            baseData["distribution"] = dist_name
            baseData.update(dist_config)
            makef = Distributions[dist_name]["MakeLibConfig"]() if is_library else Distributions[dist_name]["MakeAppConfig"]()
            makef.Load(baseData)
            makefile.makefiles[dist_name] = makef
        return makefile

#test :
sys.argv.append('--build')
sys.argv.append('--debug')
sys.argv.append('--makefile=C:\\Users\\leo\\Desktop\\CASIO\\Projets\\UltimateParticuleEngine\\Framework\\Api\\TestSolo\\CasioCg\\Test2\\Make.json')
sys.argv.append('--target=CasioCg')
#############################

parser = argparse.ArgumentParser(description="Build a project")
parser.add_argument('--build', action='store_true', help='Build the project')
#parser.add_argument('--clean', action='store_true', help='Clean the project')
parser.add_argument('--create', action='store_true', help='Create a new project')
parser.add_argument('--library', action='store_true', help='Create a new library')
parser.add_argument('--config', action='store_true', help='Show the configuration')
parser.add_argument('--debug', action='store_true', help='Enable debug mode')
parser.add_argument('--makefile', type=str, help='Path to the makefile')
parser.add_argument('--target', type=str, help='Target to build')
args = parser.parse_args()


def exec():
    if args.build:
        if args.makefile and args.target:
            with open(args.makefile, 'r') as f:
                config = json.load(f)
            makefile = MakefileParser.LoadData(config)
            if not args.target in makefile.makefiles:
                raise ValueError(f"Error: Unknown target '{args.target}'")
            cwd = os.path.dirname(args.makefile)
            cwd = os.path.abspath(cwd)
            os.chdir(cwd)
            makefile.SetCwd(cwd)
            #if args.clean:
            #    print("Cleaning... TODO")
            #    #makefile.makefiles[args.target].Clean()
            #else:
            if True:
                print("Building...")
                makefile.makefiles[args.target].Make()
        else:
            raise ValueError("Error: --makefile and --target are required when using --build")
    elif args.create:
        if args.makefile:
            makefile = MakefileParser(args.library)
            with open(args.makefile, 'w') as f:
                f.write(json.dumps(makefile.ExportData(), indent=4))
            print(f"Makefile created at {args.makefile}")
        else:
            raise ValueError("Error: --makefile is required when using --create")
    elif args.config:
        makefile = MakefileParser(args.library)
        if args.target:
            if args.target in makefile.makefiles:
                print(json.dumps(makefile.makefiles[args.target].ExportConfig(), indent=4))
            else:
                raise ValueError(f"Error: Unknown target '{args.target}'")
        else:
            print(json.dumps(makefile.ExportConfig(), indent=4))
    else:
        raise ValueError("Error: --build or --create is required")
    
if __name__ == "__main__":
    exit_code = 0
    if args.debug:
        print("Debug mode enabled")
        try:
            exec()
        except Exception as e:
            print("Error: ", e)
            traceback.print_exc()
            exit_code = 1
    else:
        try:
            exec()
        except Exception as e:
            print("Error: ", e)
            exit_code = 1
    os.chdir(local_path)
    sys.exit(exit_code)