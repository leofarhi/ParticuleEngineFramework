import os, sys
import json
import shutil
import subprocess

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
    if wsl:
        cmd = f'wsl -e bash -lic "{cmd}"'
    return subprocess.Popen(cmd, shell=True, cwd=cwd)

def getPath(path):
    if wsl:
        cmd = f'wsl -e bash -lic "pwd"'
    else:
        cmd = "pwd"
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,cwd=path)
    return p.stdout.read().decode().strip()

def build(framework_out_path, project_path):
    with open(os.path.join(project_path,"project.json")) as f:
        project = json.load(f)
    output_path = os.path.join(project_path, project["output"])
    build_path = os.path.join(project_path, project["build"])
    #clean the build and output folder
    if os.path.exists(build_path):
        shutil.rmtree(build_path, ignore_errors=True)
    if os.path.exists(output_path):
        shutil.rmtree(output_path, ignore_errors=True)
    os.makedirs(build_path, exist_ok=True)
    os.makedirs(output_path, exist_ok=True)
    makefile_path = os.path.join(project_path, "CMakeLists.txt")
    makefile = BuildMakefile(framework_out_path, project_path, project)
    with open(makefile_path, "w") as f:
        f.write(makefile)
    #build the project
    res = process("fxsdk build-cg -c -B build;make -C build", cwd=project_path)
    res.wait()
    #remove Makefile
    os.remove(makefile_path)
    return res

def BuildMakefile(framework_out_path, project_path, project):
    casio = project["distributions"]["CasioCg"]
    srcs = ""
    for src in project["sources"]:
        if os.path.isabs(src):
            src = os.path.relpath(src, project_path)
        src = str(src).replace("\\","/")
        srcs += src+ " \n"
    includes = ""
    for include in project["includes"]:
        if os.path.isabs(include):
            include = os.path.relpath(include, project_path)
        include = str(include).replace("\\","/")
        includes += "include_directories("+include+")\n"
        includes += "link_directories("+include+")\n"
    framework_out_path = getPath(os.path.abspath(framework_out_path))
    txt = f"""
cmake_minimum_required(VERSION 3.15)
project({project["name"]})

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.11 REQUIRED)

set(LIBRARY_PATH "{framework_out_path}")

message(STATUS "Library path: ${{LIBRARY_PATH}}")

set(SOURCES
{srcs}
)

# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
)
set(ASSETS_fx
)
set(ASSETS_cg
)

include_directories(${{LIBRARY_PATH}}/includes)
link_directories(${{LIBRARY_PATH}}/includes)

include_directories(${{CMAKE_CURRENT_SOURCE_DIR}}/../includes)

{includes}

fxconv_declare_assets(${{ASSETS}} ${{ASSETS_fx}} ${{ASSETS_cg}} WITH_METADATA)

add_executable(myaddin ${{SOURCES}} ${{ASSETS}} ${{ASSETS_${{FXSDK_PLATFORM}}}})
target_compile_options(myaddin PRIVATE -Wall -Wextra -Os -std=c++20 -fno-freestanding)
target_link_libraries(myaddin Gint::Gint "${{LIBRARY_PATH}}/lib/libsupc++.a" "${{LIBRARY_PATH}}/lib/libparticule.a" stdc++) 

set(NAME_APP "{casio["executable"]}")

set(DIR_OUT "{project["output"]}")

generate_g3a(TARGET myaddin OUTPUT "${{DIR_OUT}}/${{NAME_APP}}"
    NAME "{casio["display_name"]}" ICONS {casio["resources"]["icon-uns"]} {casio["resources"]["icon-sel"]})

"""
    return txt