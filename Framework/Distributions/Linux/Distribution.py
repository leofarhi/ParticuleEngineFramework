import os, sys
import subprocess
import shutil

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

curent_dir = os.path.dirname(os.path.realpath(__file__))

def MatchDistribution(distribution):
    lst = os.listdir("Distributions")
    for item in lst:
        if item.lower() == distribution.lower():
            return item
        
win_dir = os.path.join(curent_dir, "..", MatchDistribution("Windows"))
win_dir = os.path.abspath(win_dir)
if not os.path.exists(win_dir):
    print(f"\033[91mThe Windows distribution is not found in {win_dir}.\033[0m")
    sys.exit(1)

def process(cmdLinux,cmdWSL,cwd=None):
    if cmdWSL == None:
        cmdWSL = cmdLinux
    if wsl:
        cmd = f'wsl -e bash -lic "{cmdWSL}"'
        subprocess.Popen(cmd, shell=True, cwd=cwd).wait()
    else:
        subprocess.Popen(cmdLinux, shell=True, cwd=cwd).wait()

def getWslPath(path):
    cmd = f'wsl -e bash -lic "pwd"'
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,cwd=path)
    return p.stdout.read().decode().strip()

def install(base_path, build_path, output_path, args):
    print("Installing...")
    os.makedirs(os.path.join(curent_dir, "packages"), exist_ok=True)
    package_dir = os.path.join(curent_dir, "packages")
    packages = ["libsdl2-dev", "libsdl2-image-dev", "libsdl2-ttf-dev", "libsdl2-mixer-dev"]
    cmd = f"sudo apt-get install -y {' '.join(packages)}"
    process(cmd,cmd, cwd=package_dir)
    print("\033[92mAll the dependencies have been installed.\033[0m")
    return

def build(base_path, build_path, output_path, args):
    print("Building...")
    if not os.path.exists(os.path.join(curent_dir, "packages")):
        print("\033[91mThe dependencies are not installed.\033[0m")
        sys.exit(1)
    #clean the build folder
    shutil.rmtree(build_path, ignore_errors=True)
    os.makedirs(build_path)
    #copy the main folder
    shutil.copytree(base_path, build_path, dirs_exist_ok=True)
    #clean and create the output folder
    shutil.rmtree(output_path, ignore_errors=True)
    os.makedirs(output_path)
    #############################################
    #copy distribution files and overwrite existing files
    shutil.copytree(os.path.join(win_dir, "Sources"), os.path.join(build_path), dirs_exist_ok=True)
    #copy SDL2 Folder
    try:
        shutil.copytree(os.path.join(curent_dir, "packages","usr","include"), os.path.join(build_path, "includes","SDL2"), dirs_exist_ok=True)
    except:
        pass
    try:
        shutil.copytree(os.path.join(curent_dir, "packages","usr","lib","x86_64-linux-gnu"), os.path.join(build_path, "lib","SDL2"), dirs_exist_ok=True)
    except:
        pass
    #copy Makefile
    shutil.copy(os.path.join(curent_dir, "MakefileBuild.mk"), os.path.join(build_path, "Makefile"))
    #make the project
    process("make","make", cwd=build_path)
    #############################################
    #copy the output files
    os.makedirs(os.path.join(output_path, "lib","PARTICULE"), exist_ok=True)
    shutil.move(os.path.join(build_path, "particule.a"), os.path.join(output_path, "lib","PARTICULE", "particule.a"))
    shutil.move(os.path.join(build_path, "includes"), os.path.join(output_path))
    #print in green
    print("\033[92mBuild successful.\033[0m")

def MatchDemo(demo):
    lst = os.listdir(os.path.join(curent_dir, "Demos"))
    for item in lst:
        if item.lower() == demo.lower():
            return item
    return None

def BuildTestDemo(output_path,demo_path):
    #make bin folder
    os.makedirs(os.path.join(demo_path, "bin"), exist_ok=True)
    #make demo and send output in args
    output_path = output_path.replace("\\", "/")
    if wsl:
        output_path = getWslPath(output_path)
    cmd=f"export LIBRARY_PATH={output_path}; make"
    print(cmd)
    process(cmd,None, cwd=demo_path)
    print("\033[92mDemo built.\033[0m")
    process("./bin/main",None, cwd=demo_path)

def demo(base_path, build_path, output_path, args):
    print("demo...")
    #check if the output folder exists and particule.a exists
    if not os.path.exists(os.path.join(output_path, "lib","PARTICULE", "particule.a")):
        print("\033[91mBuild the framework first.\033[0m")
        sys.exit(1)
    if len(args) != 0:
        if args[0] == "clean":
            for item in os.listdir(os.path.join(curent_dir, "Demos")):
                process("make clean",None, cwd=os.path.join(curent_dir, "Demos", item))
        else:
            demo = MatchDemo(args[0])
            if demo == None:
                print("\033[91mDemo not found.\033[0m")
                sys.exit(1)
            BuildTestDemo(output_path,os.path.join(curent_dir, "Demos", demo))
    else:
        BuildTestDemo(output_path,os.path.join(curent_dir, "Demos", "Demo1"))