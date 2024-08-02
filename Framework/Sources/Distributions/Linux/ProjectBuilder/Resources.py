import os, sys
import json
import shutil
import subprocess
import json

def ErrorMsg(msg):
    print("\033[91m"+msg+"\033[0m")
    sys.exit(1)

def PrintChoices(dico):
    txt =""
    i = 1
    for key, value in dico.items():
        txt += f"{i}. {key} : {value}\n"
        i+=1
    print(txt)

def GetRes(vinput, lst):
    try:
        vinput = int(vinput)
        if vinput > len(lst) or vinput < 1:
            vinput = -1
    except:
        if vinput.lower() in lst:
            vinput = lst.index(vinput.lower())+1
        vinput = -1
    if vinput == -1:
        return None
    return lst[vinput-1]

ressources_types = {
    "images" : "Ajouter des images",
    "internal_fonts" : "Ajouter des polices de caractères spécifiques à la distribution",
    "fonts" : "Ajouter des polices de caractères pour ParticuleEngine",
}

def edit_project(project_path, args):
    #load project.json
    with open(os.path.join(project_path,"project.json")) as f:
        project = json.load(f)
    if len(args) == 0:
        print("Veuillez selectionner le type de ressources à ajouter :")
        PrintChoices(ressources_types)
        res = GetRes(input("Type :"), list(ressources_types.keys()))
    else:
        res = GetRes(args[0], list(ressources_types.keys()))
        args = args[1:]
    if res == None:
        ErrorMsg("Type de ressources invalide")
    if res == "images":
        if len(args) == 0:
            print("Veuillez entrer le chemin des images à ajouter (ex : assets/WinLinux/images/img.png) :")
            path = input("Chemin relatif :")
            if not os.path.exists(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'existe pas")
            if not os.path.isfile(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'est pas un fichier")
            print("Veuillez entrer le chemin de destination (ex : assets/images/img.png) :")
            dest = input("Chemin de destination :")
        else:
            if len(args) != 2:
                ErrorMsg("Nombre d'arguments invalide")
            path = args[0]
            if not os.path.exists(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'existe pas")
            if not os.path.isfile(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'est pas un fichier")
            dest = args[1]
        project["distributions"]["Linux"]["resources"]["images"].append((path, dest))
    elif res == "internal_fonts":
        if len(args) == 0:
            print("Veuillez entrer le chemin des polices de caractères à ajouter (ex : assets/WinLinux/fonts/font.ttf) :")
            path = input("Chemin relatif :")
            if not os.path.exists(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'existe pas")
            if not os.path.isfile(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'est pas un fichier")
            print("Veuillez entrer le chemin de destination (ex : assets/fonts/font.ttf) :")
            dest = input("Chemin de destination :")
        else:
            if len(args) != 2:
                ErrorMsg("Nombre d'arguments invalide")
            path = args[0]
            if not os.path.exists(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'existe pas")
            if not os.path.isfile(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'est pas un fichier")
            dest = args[1]
        project["distributions"]["Linux"]["resources"]["internal_fonts"].append((path, dest))
    elif res == "fonts":
        if len(args) == 0:
            print("Veuillez entrer le chemin des polices de caractères à ajouter (ex : assets/WinLinux/fonts/font.ttf) :")
            path = input("Chemin relatif :")
            if not os.path.exists(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'existe pas")
            if not os.path.isfile(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'est pas un fichier")
            print("Veuillez entrer le chemin de destination (ex : assets/fonts/font.bin) :")
            dest = input("Chemin de destination :")
            print("Veuillez entrer le la resolution maximale de la police :")
            try:
                resolution = int(input("Resolution :"))
            except:
                ErrorMsg("Résolution invalide")
        else:
            if len(args) != 3:
                ErrorMsg("Nombre d'arguments invalide")
            path = args[0]
            if not os.path.exists(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'existe pas")
            if not os.path.isfile(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'est pas un fichier")
            dest = args[1]
            try:
                resolution = int(args[2])
            except:
                ErrorMsg("Résolution invalide")
        project["distributions"]["Linux"]["resources"]["fonts"].append((path, dest, resolution))
    with open(os.path.join(project_path,"project.json"), "w") as f:
        json.dump(project, f, indent=4)

def build_resources(framework_out_path, project_path, projectbuilder_path):
    with open(os.path.join(project_path,"project.json")) as f:
        project = json.load(f)
    resources = project["distributions"]["Linux"]["resources"]
    output_path = os.path.join(project_path, project["output"])
    build_path = os.path.join(project_path, project["build"])
    for file in resources["images"] + resources["internal_fonts"]:
        src = os.path.join(project_path, file[0])
        dest = os.path.join(output_path, file[1])
        #make folders
        os.makedirs(os.path.dirname(dest), exist_ok=True)
        shutil.copy(src, dest)