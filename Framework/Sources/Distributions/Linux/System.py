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
    lst = os.listdir(os.path.join("Sources","Distributions"))
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

def process2(cmdLinux,cmdWSL,cwd=None):
    if cmdWSL == None:
        cmdWSL = cmdLinux
    if wsl:
        cmd = f'wsl "{cmdWSL}"'
        subprocess.Popen(cmd, shell=True, cwd=cwd).wait()
    else:
        subprocess.Popen(cmdLinux, shell=True, cwd=cwd).wait()

def getWslPath(path):
    cmd = f'wsl -e bash -lic "pwd"'
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,cwd=path)
    return p.stdout.read().decode().strip()

def install(base_path, build_path, output_path, args):
    print("Installing...")
    cmd = f"sudo apt-get install -y g++ make"
    process(cmd,cmd, cwd=curent_dir)
    packages = ["libsdl2-dev", "libsdl2-image-dev", "libsdl2-ttf-dev", "libsdl2-mixer-dev"]
    cmd = f"sudo apt-get install -y {' '.join(packages)}"
    process(cmd,cmd, cwd=curent_dir)
    print("\033[92mAll the dependencies have been installed.\033[0m")
    return

def update(base_path, build_path, output_path, args):
    pass

def build_packages(base_path, build_path, output_path, packages):
    package_dir = os.path.join(os.path.dirname(os.path.realpath(base_path)),"Packages")
    dispo = [i.lower() for i in os.listdir(package_dir)]
    for i in packages:
        if i.lower() not in dispo:
            print(f"\033[91mPackage \"{i}\" not found.\033[0m")
            exit(1)
        else:
            print("Add package: " + i)
            pack_dir = os.path.join(package_dir,i)
            for dirs in os.listdir(pack_dir):
                shutil.copytree(os.path.join(pack_dir,dirs), os.path.join(build_path,dirs), dirs_exist_ok=True)

def build(base_path, build_path, output_path, args):
    packages = []
    if len(args) > 0:
        if args[0][0] == "[" and args[0][-1] == "]":
            packages = args[0][1:-1].split(",")
            #remove spaces
            packages = [x.strip() for x in packages]
        else:
            print("\033[91mInvalid packages format.\033[0m")
            exit(1)
    print("Building...")
    #clean the build folder
    shutil.rmtree(build_path, ignore_errors=True)
    os.makedirs(build_path)
    #copy the main folder
    shutil.copytree(base_path, build_path, dirs_exist_ok=True)
    build_packages(base_path, build_path, output_path, packages)
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

