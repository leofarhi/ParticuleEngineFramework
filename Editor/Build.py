import os, sys
import subprocess
import importlib
import shutil

dir_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(dir_path)

framework_path = os.path.join(dir_path,"..", "Framework")
framework_out_path = os.path.join(framework_path,"Output")
bin_path = os.path.join(dir_path, "bin")

if len(sys.argv) < 2:
    txt ="""
    Sélectionnez la distribution à installer:
    1. Windows
    2. Linux
    """
    print(txt)
    distribution = input("Distribution: ")
else:
    distribution = sys.argv[1]
if distribution == "1":
    distribution = "Windows"
elif distribution == "2":
    distribution = "Linux"
else:
    print("Distribution invalide")
    sys.exit(1)

def process(cmd,cwd=None):
    subprocess.Popen(cmd, shell=True, cwd=cwd).wait()

if distribution == "Windows":
    print("Building Windows Framework...")
    #process("python Framework.py build Windows",cwd=framework_path)
    #delete the old build folder
    shutil.rmtree(os.path.join(dir_path, "bin"), ignore_errors=True)
    os.makedirs(os.path.join(dir_path, "bin"), exist_ok=True)
    #copy the output bin folder
    shutil.copytree(os.path.join(framework_out_path, "bin"), os.path.join(bin_path), dirs_exist_ok=True)
    #make clean
    process("make -f MakefileWin.mk clean",cwd=dir_path)
    #build "MakefileWin.mk"
    process("make -f MakefileWin.mk",cwd=dir_path)
    process(".\\ParticuleEditor.exe",cwd=bin_path)

elif distribution == "Linux":
    print("Building Linux Framework...")
    process("python Framework.py build Linux",cwd=framework_path)
    #delete the old build folder
    shutil.rmtree(os.path.join(dir_path, "bin"), ignore_errors=True)
    os.makedirs(os.path.join(dir_path, "bin"), exist_ok=True)
    platform = sys.platform
    print(platform)
    wsl = False
    if platform == "win32":
        wsl = True
        #check if WSL is installed
        print("\033[92mChecking if WSL is installed...\033[0m")
        ret = subprocess.Popen("wsl -e echo wsl", shell=True).wait()
        if ret == 0:
            print("\033[92mWSL is installed.\033[0m")
        else:
            print("\033[91mWSL is not installed.\033[0m")
            sys.exit(1)
        def process(cmd,cwd=None):
            cmd = f'wsl -e bash -lic "{cmd}"'
            subprocess.Popen(cmd, shell=True, cwd=cwd).wait()
    process("make -f MakefileLinux.mk clean",cwd=dir_path)
    process("make -f MakefileLinux.mk",cwd=dir_path)