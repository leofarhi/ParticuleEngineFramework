import os, sys
import shutil
import subprocess

platform = sys.platform
platform_available = []
if platform == "win32":
    platform_available.append("windows")
    print("\033[92mChecking if WSL is installed...\033[0m")
    if subprocess.Popen("wsl -e echo wsl", shell=True, stdout=subprocess.PIPE).wait() == 0:
        print("\033[92mWSL is installed.\033[0m")
        platform_available.append("wsl")
    else:
        print("\033[91mWSL is not installed.\033[0m")

    def GetPathLinux(path, relative=None):
        path = os.path.normpath(path)
        path = os.path.abspath(path)
        cmd = f'wsl -e bash -lic "pwd"'
        file = None
        if os.path.isdir(path):
            path_dir = path
        else:
            path_dir = os.path.dirname(path)
            file = os.path.basename(path)
        path = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, cwd=path_dir).stdout.read().decode().strip()
        if file is not None:
            path = path + "/" + file
        if relative is not None:
            relative = GetPathLinux(relative)
            cmd = f'wsl -e bash -lic "realpath --relative-to={relative} {path}"'
            path = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE).stdout.read().decode().strip()
        return path
    
    def ProcessLinuxStdout(cmd,cwd=None):
        cmd = f'wsl -e bash -lic "{cmd}"'
        p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,cwd=cwd)
        return p.stdout.read().decode().strip()
    
    def ProcessLinuxValue(cmd,cwd=None):
        cmd = f'wsl -e bash -lic "{cmd}"'
        ret = subprocess.Popen(cmd, shell=True, cwd=cwd).wait()
        return ret
elif platform == "linux":
    platform_available.append("linux")
    def GetPathLinux(path, relative=None):
        if relative is not None:
            path = os.path.relpath(path, relative)
        return path
    
    def ProcessLinuxStdout(cmd,cwd=None):
        p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,cwd=cwd)
        return p.stdout.read().decode().strip()
    
    def ProcessLinuxValue(cmd,cwd=None):
        ret = subprocess.Popen(cmd, shell=True, cwd=cwd).wait()
        return ret
else:
    raise ValueError("Unsupported platform: " + platform)