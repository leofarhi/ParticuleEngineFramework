import os, sys
import json
import shutil
import subprocess
import Resources

def ErrorMsg(msg):
    print("\033[91m"+msg+"\033[0m")
    sys.exit(1)

#check if windres est installé
def CheckWindres():
    try:
        res = subprocess.Popen("windres --version",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        res.wait()
        if res.returncode != 0:
            ErrorMsg("Windres n'est pas installé")
    except FileNotFoundError:
        ErrorMsg("Windres n'est pas installé")

def build(framework_out_path, project_path, projectbuilder_path):
    CheckWindres()
    with open(os.path.join(project_path,"project.json")) as f:
        project = json.load(f)
    output_path = os.path.join(project_path, project["output"])
    build_path = os.path.join(project_path, project["build"])
    windows = project["distributions"]["Windows"]
    #clean the build and output folder
    if os.path.exists(build_path):
        shutil.rmtree(build_path, ignore_errors=True)
    if os.path.exists(output_path):
        shutil.rmtree(output_path, ignore_errors=True)
    os.makedirs(build_path, exist_ok=True)
    os.makedirs(output_path, exist_ok=True)
    #copy the output lib bin folder
    shutil.copytree(os.path.join(framework_out_path, "bin"), os.path.join(output_path), dirs_exist_ok=True)
    if os.path.isabs(windows["resources"]["ico"]):
            windows["resources"]["ico"] = os.path.relpath(windows["resources"]["ico"], project_path)
    makefile_path = os.path.join(project_path, "Makefile")
    makefile = BuildMakefile(framework_out_path, project_path, project)
    with open(makefile_path, "w") as f:
        f.write(makefile)
    #make rc file
    rc_path = os.path.join(build_path, "resource.rc")
    with open(rc_path, "w") as f:
        f.write("1 ICON \"../"+windows["resources"]["ico"]+"\"")
    #build the project
    Resources.build_resources(framework_out_path, project_path, projectbuilder_path)
    res = subprocess.Popen("make", shell=True, cwd=project_path)
    res.wait()
    #remove Makefile
    os.remove(makefile_path)
    return res


def BuildMakefile(framework_out_path, project_path, project):
    windows = project["distributions"]["Windows"]
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
    framework_out_path = framework_out_path.replace("\\","/")
    txt = f"""
LIBRARY_PATH = {framework_out_path}

CC = g++
CPPFLAGS = -MMD
CPPFLAGS += {project["flags"]} {windows["debug-flags"] if project["debug"] else ""}
LDLIBS = -lm

OUTPUT = {project["output"]}
BUILD_DIR = {project["build"]}/objs
RES = {project["build"]}/resource.o

ICON = {windows["resources"]["ico"]}

EXEC = $(OUTPUT)/{windows["executable"]}

SRCS = {srcs}

SRCS_CPP = $(filter %.cpp, $(SRCS))
SRCS_C = $(filter %.c, $(SRCS))

OBJS = $(patsubst %, $(BUILD_DIR)/%, $(SRCS_CPP:.cpp=.o))
OBJS += $(patsubst %, $(BUILD_DIR)/%, $(SRCS_C:.c=.o))
DEPS = $(OBJS:.o=.d)

CPPFLAGS += -I $(LIBRARY_PATH)/includes
LDLIBS += -L$(LIBRARY_PATH)/lib -L$(LIBRARY_PATH)/lib/PARTICULE -l:particule.a -L $(LIBRARY_PATH)/includes

CPPFLAGS += -I $(LIBRARY_PATH)/includes/SDL2
LDLIBS += -L$(LIBRARY_PATH)/lib/SDL2 -lmingw32 -lSDL2 -lgdi32 -luser32 -lole32 -loleaut32 -lmingw32 -limm32 -lwinmm -lversion -lSetupAPI -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype -lcomdlg32

{includes}

all: $(EXEC)

$(EXEC): $(OBJS) $(RES)
	mkdir -p $(OUTPUT)
	$(CC) $(LDFLAGS) $(OBJS) $(RES) -o $(EXEC) $(LDLIBS)
	@echo "done !"

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c "$<" -o "$@"

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c "$<" -o "$@"

# Compilation de la ressource
{project["build"]}/resource.o: {project["build"]}/resource.rc $(ICON)
	windres $< -O coff -o $@


-include $(DEPS)

.PHONY: all
"""
    return txt