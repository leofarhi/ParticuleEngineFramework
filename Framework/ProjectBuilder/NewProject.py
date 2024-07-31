from ProjectEnv import *
import time

def DefaultConfig(name):
    return {
        "version_framework": "1.0",
        "version": "1.0",
        "name": name,
        "description": "Description du projet",
        "author": "Auteur du projet",
        "date": time.strftime("%d/%m/%Y"),
        "debug": False,
        "flags": "-Wall -Wextra -Werror",
        "sources": ["srcs/main.cpp"],
        "includes": ["includes"],
        "output":"bin",
        "build":"build",
        "packages": ["InterfaceSystem"],
        "distributions":
        {
            "Windows":
            {
                "debug-flags": "",
                "executable": name+".exe",
                "resources": {
                    "ico": "assets/WinLinux/icon.ico",
                    "icon": "assets/WinLinux/icon.png",
                    "asset_dir": "assets",
                    "images": [],#format : (path, dest_path) ex : ("assets/WinLinux/img.png", "assets/img.png")
                }
            },
            "Linux":
            {
                "debug-flags": "-fsanitize=address -g3 -std=c99 -O0",
                "executable": name,
                "resources": {
                    "icon": "assets/WinLinux/icon.png",
                    "asset_dir": "assets",
                    "images": [],#format : (path, dest_path)
                }
            },
            "CasioCg":
            {
                "debug-flags": "",
                "executable": name[:8]+".g3a",
                "resources": {
                    "icon-uns": "assets/CasioCg/icon-uns.png",
                    "icon-sel": "assets/CasioCg/icon-sel.png",
                    "images": [],
                }
            }
        }
    }

def CreateProject(args):
    print("Création d'un nouveau projet")
    if len(args) == 0:
        path = input("Veuillez entrer le chemin du projet :")
        name = input("Veuillez entrer le nom du projet :")
    elif len(args) == 2:
        path = args[0]
        name = args[1]
    else:
        ErrorMsg("Nombre d'arguments invalide")
    #check if path exists and is a directory
    if not os.path.exists(path):
        ErrorMsg("Le chemin spécifié n'existe pas")
    if not os.path.isdir(path):
        ErrorMsg("Le chemin spécifié n'est pas un dossier")
    #check name is valid (only contains letters, numbers and underscores)
    if not name.replace("_","").isalnum():
        ErrorMsg("Le nom du projet ne doit contenir que des lettres et des chiffres et des underscores")
    #check if project already exists
    projectpath = os.path.join(path,name)
    if os.path.exists(projectpath):
        ErrorMsg("Le projet existe déjà")
    #create project
    shutil.copytree(os.path.join(dir_path, "DefaultSources"), projectpath, dirs_exist_ok=True)
    config = DefaultConfig(name)
    #json dump
    with open(os.path.join(projectpath,"project.json"), "w") as f:
        json.dump(config, f, indent=4)
    