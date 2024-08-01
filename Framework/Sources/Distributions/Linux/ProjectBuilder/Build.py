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
    makefile_path = os.path.join(project_path, "Makefile")
    makefile = BuildMakefile(framework_out_path, project_path, project)
    with open(makefile_path, "w") as f:
        f.write(makefile)
    #build the project
    res = process("make", cwd=project_path)
    res.wait()
    #remove Makefile
    os.remove(makefile_path)
    return res


def BuildMakefile(framework_out_path, project_path, project):
    linux = project["distributions"]["Linux"]
    srcs = ""
    for src in project["sources"]:
        if os.path.isabs(src):
            src = os.path.relpath(src, project_path)
        src = str(src).replace("\\","/")
        srcs += src+ " "
    includes = ""
    for include in project["includes"]:
        if os.path.isabs(include):
            include = os.path.relpath(include, project_path)
        include = str(include).replace("\\","/")
        includes += "CPPFLAGS += -I "+include+"\n"
        includes += "LDLIBS += -L "+include+"\n"
    framework_out_path = getPath(os.path.abspath(framework_out_path))
    txt = f"""
LIBRARY_PATH = {framework_out_path}

CC = g++
CPPFLAGS = -MMD
CPPFLAGS += {project["flags"]} {linux["debug-flags"] if project["debug"] else ""}
LDLIBS = -lm

OUTPUT = {project["output"]}
BUILD_DIR = {project["build"]}/objs

EXEC = $(OUTPUT)/{linux["executable"]}

SRCS = {srcs}

SRCS_CPP = $(filter %.cpp, $(SRCS))
SRCS_C = $(filter %.c, $(SRCS))

OBJS = $(patsubst %, $(BUILD_DIR)/%, $(SRCS_CPP:.cpp=.o))
OBJS += $(patsubst %, $(BUILD_DIR)/%, $(SRCS_C:.c=.o))
DEPS = $(OBJS:.o=.d)

# Include paths
CFLAGS += -I $(LIBRARY_PATH)/includes

# Library paths and linking
LDLIBS += -L$(LIBRARY_PATH)/lib -L$(LIBRARY_PATH)/lib/PARTICULE -l:particule.a
CFLAGS += `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
LDLIBS += `pkg-config --libs sdl2 SDL2_image SDL2_ttf`

{includes}

all: $(EXEC)

$(EXEC): $(OBJS)
	mkdir -p $(OUTPUT)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)
	@echo "done !"

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c "$<" -o "$@"

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c "$<" -o "$@"


-include $(DEPS)

.PHONY: all
"""
    return txt