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

