import os, sys
import json
import shutil
import subprocess

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
    #copy the output lib bin folder
    shutil.copytree(os.path.join(framework_out_path, "bin"), os.path.join(output_path), dirs_exist_ok=True)
    makefile_path = os.path.join(build_path, "Makefile")
    makefile = BuildMakefile(framework_out_path, project_path, project)
    with open(makefile_path, "w") as f:
        f.write(makefile)
    #build the project
    res = subprocess.Popen("make", shell=True, cwd=build_path)
    res.wait()
    return res


def BuildMakefile(framework_out_path, project_path, project):
    windows = project["distributions"]["Windows"]
    srcs = ""
    for src in project["sources"]:
        src = str(src).replace("\\","/")
        if os.path.isabs(src):
            src = os.path.relpath(src, project_path)
        src = "../"+src
        src = str(src).replace("\\","/")
        srcs += src+ " "
    includes = ""
    for include in project["includes"]:
        include = str(include).replace("\\","/")
        if os.path.isabs(include):
            include = os.path.relpath(include, project_path)
        include = "../"+include
        include = str(include).replace("\\","/")
        includes += "CPPFLAGS += -I "+include+"\n"
        includes += "LDLIBS += -L "+include+"\n"
    framework_out_path = framework_out_path.replace("\\","/")
    txt = f"""
LIBRARY_PATH = {framework_out_path}

CC = g++
CPPFLAGS = -MMD
CPPFLAGS += {project["flags"]} {windows["debug-flags"] if project["debug"] else ""}
LDLIBS = -lm

OUTPUT = ../{project["output"]}
BUILD_DIR = {project["build"]}

EXEC = $(OUTPUT)/{windows["executable"]}

SRCS = {srcs}

Scrs_dir = ..

OBJS = $(patsubst $(Scrs_dir)/%, $(BUILD_DIR)/%, $(SRCS:.cpp=.o))
OBJS := $(patsubst $(Scrs_dir)/%, $(BUILD_DIR)/%, $(OBJS:.c=.o))
DEPS = $(OBJS:.o=.d)

CPPFLAGS += -I $(LIBRARY_PATH)/includes
LDLIBS += -L$(LIBRARY_PATH)/lib -L$(LIBRARY_PATH)/lib/PARTICULE -l:particule.a -L $(LIBRARY_PATH)/includes

CPPFLAGS += -I $(LIBRARY_PATH)/includes/SDL2
LDLIBS += -L$(LIBRARY_PATH)/lib/SDL2 -lmingw32 -lSDL2 -lgdi32 -luser32 -lole32 -loleaut32 -lmingw32 -limm32 -lwinmm -lversion -lSetupAPI -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype -lcomdlg32

{includes}

all: $(EXEC)

$(EXEC): $(OBJS)
	mkdir -p $(OUTPUT)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)
	@echo "done !"

$(BUILD_DIR)/%.o: $(Scrs_dir)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c "$<" -o "$@"

$(BUILD_DIR)/%.o: $(Scrs_dir)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c "$<" -o "$@"


-include $(DEPS)

.PHONY: all
"""
    return txt