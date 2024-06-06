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
    cmd = f"sudo apt-get install -y libmpfr-dev libmpc-dev libgmp-dev libpng-dev libppl-dev flex g++ git texinfo make"
    process(cmd,cmd, cwd=curent_dir)
    cmd = f"sudo apt-get install -y curl git python3 build-essential cmake pkg-config"
    process(cmd,cmd, cwd=curent_dir)
    cmd = 'curl "https://git.planet-casio.com/Lephenixnoir/GiteaPC/raw/branch/master/install.sh" -o /tmp/giteapc-install.sh && bash /tmp/giteapc-install.sh'
    process(cmd,cmd, cwd=curent_dir)
    cmd = 'sudo apt install python3-pil libusb-1.0-0-dev libudev-dev libsdl2-dev libpng-dev libncurses-dev'
    process(cmd,cmd, cwd=curent_dir)
    cmd = 'sudo apt install libudisks2-dev libglib2.0-dev'
    process(cmd,cmd, cwd=curent_dir)
    cmd = 'giteapc install Lephenixnoir/fxsdk Lephenixnoir/sh-elf-binutils Lephenixnoir/sh-elf-gcc'
    process(cmd,cmd, cwd=curent_dir)
    cmd = 'giteapc install Lephenixnoir/sh-elf-gdb'
    process(cmd,cmd, cwd=curent_dir)
    cmd = 'giteapc install Lephenixnoir/OpenLibm Vhex-Kernel-Core/fxlibc'
    process(cmd,cmd, cwd=curent_dir)
    cmd = 'giteapc install Lephenixnoir/sh-elf-gcc'
    process(cmd,cmd, cwd=curent_dir)
    cmd = 'giteapc install Lephenixnoir/gint'
    process(cmd,cmd, cwd=curent_dir)
    cmd = 'giteapc install Lephenixnoir/libprof'
    process(cmd,cmd, cwd=curent_dir)
    print("\033[92mAll the dependencies have been installed.\033[0m")

def build(base_path, build_path, output_path, args):
    print("Building...")
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
    shutil.copytree(os.path.join(curent_dir, "Sources"), os.path.join(build_path), dirs_exist_ok=True)
    #copy Makefile
    shutil.copy(os.path.join(curent_dir, "CMakeLists.txt"), os.path.join(build_path, "CMakeLists.txt"))
    #copy lib
    os.makedirs(os.path.join(build_path, "lib"), exist_ok=True)
    shutil.copy(os.path.join(curent_dir, "libsupc++.a"), os.path.join(build_path, "lib","libsupc++.a"))
    #make the build folder
    os.makedirs(os.path.join(build_path, "build"), exist_ok=True)
    #make the project
    cmd = "fxsdk build-cg -c -B build;make -C build"
    process(cmd,cmd, cwd=build_path)
     #############################################
    #copy the output files
    shutil.move(os.path.join(build_path, "lib"), output_path)
    shutil.move(os.path.join(build_path, "build","libparticule.a"), os.path.join(output_path, "lib", "libparticule.a"))
    shutil.move(os.path.join(build_path, "includes"), os.path.join(output_path))

def demo(base_path, build_path, output_path, args):
    pass