from .System import *

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
    #make demo and send output in args
    output_path = output_path.replace("\\", "/")
    if wsl:
        output_path = getWslPath(output_path)
    cmd=f"fxsdk build-cg -c -DLIBRARY_PATH={output_path} -B build;make -C build"
    print(cmd)
    process(cmd,None, cwd=build_path)
    print("\033[92mDemo built.\033[0m")

def demo(base_path, build_path, output_path, args):
    print("demo...")
    #check if the output folder exists and particule.a exists
    if not os.path.exists(os.path.join(output_path, "lib", "libparticule.a")):
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