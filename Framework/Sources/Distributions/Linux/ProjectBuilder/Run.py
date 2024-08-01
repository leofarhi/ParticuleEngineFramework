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
        cmd = f'wsl {cmd}'
    subprocess.Popen(cmd, shell=True, cwd=cwd).wait()

def run(output, project):
    linux = project["distributions"]["Linux"]
    process("./"+linux["executable"], cwd=output)