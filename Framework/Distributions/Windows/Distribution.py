import os, sys
import subprocess
import shutil

curent_dir = os.path.dirname(os.path.realpath(__file__))

def process(command,cwd=None):
    subprocess.Popen(command, shell=True, cwd=cwd).wait()

def install(base_path, build_path, output_path, args):
    print("Installing...")
    print("\033[92mAll the dependencies have already been installed.\033[0m")

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
    #copy SDL2 Folder
    shutil.copytree(os.path.join(curent_dir, "SDL2","SDL2_WIN_Include","include"), os.path.join(build_path, "includes","SDL2"), dirs_exist_ok=True)
    shutil.copytree(os.path.join(curent_dir, "SDL2","SDL2_WIN_Include","lib"), os.path.join(build_path, "lib","SDL2"), dirs_exist_ok=True)
    #copy Makefile
    shutil.copy(os.path.join(curent_dir, "MakefileBuild.mk"), os.path.join(build_path, "Makefile"))
    #make the project
    process("make", cwd=build_path)
    #############################################
    #copy the output files
    shutil.move(os.path.join(build_path, "lib"), os.path.join(output_path))
    os.makedirs(os.path.join(output_path, "lib","PARTICULE"), exist_ok=True)
    shutil.move(os.path.join(build_path, "particule.a"), os.path.join(output_path, "lib","PARTICULE", "particule.a"))
    shutil.move(os.path.join(build_path, "includes"), os.path.join(output_path))
    shutil.copytree(os.path.join(curent_dir, "SDL2","BIN_SDL"), os.path.join(output_path, "bin"), dirs_exist_ok=True)
    #print in green
    print("\033[92mBuild successful.\033[0m")

demos_path = os.path.join(curent_dir,"..","..", "Demos")

def MatchDemo(demo):
    lst = os.listdir(demos_path)
    for item in lst:
        if item.lower() == demo.lower():
            return item
    return None

def BuildTestDemo(output_path,demo_path):
    build_path = os.path.join(demo_path, "build")
    #clean the build folder
    shutil.rmtree(build_path, ignore_errors=True)
    os.makedirs(build_path)
    os.makedirs(os.path.join(demo_path, "build", "bin"), exist_ok=True)
    #copy the main folder
    shutil.copytree(os.path.join(curent_dir, "Demo"), build_path, dirs_exist_ok=True)
    #copy distribution files and overwrite existing files
    shutil.copytree(os.path.join(output_path, "bin"), os.path.join(demo_path, "build", "bin"), dirs_exist_ok=True)
    #make demo and send output in args
    output_path = output_path.replace("\\", "/")
    cmd=f"set LIBRARY_PATH={output_path}&& make"
    print(cmd)
    process(cmd, cwd=build_path)
    print("\033[92mDemo built.\033[0m")
    process(".\\main.exe", cwd=os.path.join(build_path, "bin"))


def demo(base_path, build_path, output_path, args):
    print("demo...")
    #check if the output folder exists and particule.a exists
    if not os.path.exists(os.path.join(output_path, "lib","PARTICULE", "particule.a")):
        print("\033[91mBuild the framework first.\033[0m")
        sys.exit(1)
    if len(args) != 0:
        if args[0] == "clean":
            for item in os.listdir(demos_path):
                shutil.rmtree(os.path.join(demos_path, item, "build"), ignore_errors=True)
        else:
            name = MatchDemo(args[0])
            if name == None:
                print("\033[91mDemo not found.\033[0m")
                sys.exit(1)
            BuildTestDemo(output_path,os.path.join(demos_path, name))
    else:
        if len(os.listdir(demos_path)) == 0:
            print("\033[91mNo demos found.\033[0m")
            sys.exit(1)
        else:
            print("Demos found: ")
            for item in os.listdir(demos_path):
                print(item)