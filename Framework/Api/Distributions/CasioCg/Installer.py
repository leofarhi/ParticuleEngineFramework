from PythonModules.BaseConfig import *
from PythonModules.MultiPlatform import *
from PythonModules.BaseInstaller import *
import os, sys
import shutil

# Liste des paquets apt à installer (regroupés)
PACKAGES = {
    "apt": [
        "curl", "git", "python3", "gcc", "g++", "build-essential", "cmake", "pkg-config"
    ],
    "pacman": [
        "curl", "git", "python3", "gcc", "g++", "make", "cmake", "pkgconf"
    ]
}

GITEAPC_PACKAGES = [
    "Lephenixnoir/fxsdk",
    "Lephenixnoir/sh-elf-binutils",
    "Lephenixnoir/sh-elf-gcc",
    "Lephenixnoir/sh-elf-gdb",
    "Lephenixnoir/OpenLibm",
    "Vhex-Kernel-Core/fxlibc",
    "Lephenixnoir/gint",
    "Lephenixnoir/libprof"
]

# Liste des paquets giteapc à installer
GITEAPC_PACKAGES = [
    "Lephenixnoir/fxsdk",
    "Lephenixnoir/sh-elf-binutils",
    "Lephenixnoir/sh-elf-gcc",
    "Lephenixnoir/sh-elf-gdb",
    "Lephenixnoir/OpenLibm",
    "Vhex-Kernel-Core/fxlibc",
    "Lephenixnoir/gint",
    "Lephenixnoir/libprof"
]

def detect_package_manager():
    if ProcessLinux("apt --version").wait() == 0:
        return "apt"
    elif ProcessLinux("pacman --version").wait() == 0:
        return "pacman"
    else:
        raise ValueError("Unsupported distribution (only apt or pacman supported)")

class Installer(BaseInstaller):
    def install(self):
        print("Installing distribution...")
        if self.is_installed():
            raise ValueError("The distribution is already installed.")
        manager = detect_package_manager()
        if manager == "apt":
            ProcessLinuxValue("sudo apt-get update")
            ProcessLinuxValue(f"sudo apt-get install -y {' '.join(PACKAGES['apt'])}")
        elif manager == "pacman":
            ProcessLinuxValue("sudo pacman -Sy --noconfirm")
            ProcessLinuxValue(f"sudo pacman -S --noconfirm {' '.join(PACKAGES['pacman'])}")
        if ProcessLinux("giteapc --version").wait() != 0:
            ProcessLinuxValue('curl "https://git.planet-casio.com/Lephenixnoir/GiteaPC/raw/branch/master/install.sh" -o /tmp/giteapc-install.sh')
            ProcessLinuxValue("bash /tmp/giteapc-install.sh")
        if ProcessLinux("giteapc --version").wait() != 0:
            raise ValueError("Giteapc installation failed.")
        for package in GITEAPC_PACKAGES:
            ProcessLinuxValue(f"giteapc install {package} -y")
        if not self.is_installed():
            raise ValueError("Installation failed.")
        print("Installation completed successfully.")
    
    def is_installed(self):
        if not ("wsl" in platform_available or "linux" in platform_available):
            raise ValueError("You must be in WSL or Linux to use this distribution.")
        missing = []
        manager = detect_package_manager()
        if manager == "apt":
            for pkg in PACKAGES['apt']:
                if ProcessLinux(f"dpkg -s {pkg}").wait() != 0:
                    missing.append(pkg)
        elif manager == "pacman":
            for pkg in PACKAGES['pacman']:
                if ProcessLinux(f"pacman -Qi {pkg}").wait() != 0:
                    missing.append(pkg)
        for cmd in ["giteapc", "sh-elf-gcc", "sh-elf-gdb"]:
            if ProcessLinux(cmd + " --version").wait() != 0:
                missing.append(cmd)
        lst = ProcessLinuxStdout("giteapc list")
        for package in GITEAPC_PACKAGES:
            if package not in lst:
                missing.append("giteapc:" + package)
        if missing:
            print("Missing packages:")
            for pkg in missing:
                print(f" - {pkg}")
            return False
        return True
    
    def configure(self):
        print("No configuration needed for this distribution.")
    
    def update(self):
        if not self.is_installed():
            raise ValueError("The distribution is not installed.")
        print("Updating distribution...")
        ret = ProcessLinuxValue("giteapc install -u -y")
        if ret != 0:
            raise ValueError("Update failed.")
        print("Update completed successfully.")

    def uninstall(self):
        raise NotImplementedError("Uninstall method not implemented.")