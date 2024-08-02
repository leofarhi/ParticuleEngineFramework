import os, sys
import json
import shutil
import subprocess

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

profiles_image =[
       "rgb565_bopti-image",
       "rgb565a_bopti-image",
       "p8_rgb565_bopti-image",
       "p8_rgb565a_bopti-image",
       "p4_rgb565_bopti-image",
       "p4_rgb565a_bopti-image",

       "external_rgb565_bopti-image",
       "external_rgb565a_bopti-image",
       "external_p8_rgb565_bopti-image",
       "external_p8_rgb565a_bopti-image",
       "external_p4_rgb565_bopti-image",
       "external_p4_rgb565a_bopti-image",
       ]

temp = dict()
for i in profiles_image:
    temp[i] = ""
profiles_image = temp

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
            print("Veuillez entrer le chemin de destination virtuel (ex : assets/images/img.png) :")
            dest = input("Chemin de destination :")
            print("Veuillez selectionner le type de l'image :")
            PrintChoices(profiles_image)
            profile = GetRes(input("Type : "), list(profiles_image.keys()))
        else:
            if len(args) != 3:
                ErrorMsg("Nombre d'arguments invalide")
            path = args[0]
            if not os.path.exists(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'existe pas")
            if not os.path.isfile(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'est pas un fichier")
            dest = args[1]
            profile = GetRes(args[2], list(profiles_image.keys()))
        if profile == None:
            ErrorMsg("Type d'image invalide")
        project["distributions"]["CasioCg"]["resources"]["images"].append((path,dest, profile))
    elif res == "internal_fonts":
        ErrorMsg("Indisponible pour le moment")
    elif res == "fonts":
        if len(args) == 0:
            print("Veuillez entrer le chemin des polices de caractères à ajouter (ex : assets/WinLinux/fonts/font.ttf) :")
            path = input("Chemin relatif :")
            if not os.path.exists(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'existe pas")
            if not os.path.isfile(os.path.join(project_path, path)):
                ErrorMsg("Le chemin spécifié n'est pas un fichier")
            print("Veuillez entrer le chemin de destination virtuel (ex : assets/fonts/font.bin) :")
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
        project["distributions"]["CasioCg"]["resources"]["fonts"].append((path, dest, resolution))
    with open(os.path.join(project_path,"project.json"), "w") as f:
        json.dump(project, f, indent=4)

def clear_resources(project_path, project):
    resources = project["distributions"]["CasioCg"]["resources"]
    #remove all fxconv-metadata.txt
    dirs = set([os.path.dirname(file[0]) for file in resources["images"]])
    for d in dirs:
        p = os.path.join(project_path, d, "fxconv-metadata.txt")
        p = os.path.abspath(p)
        if os.path.exists(p):
            os.remove(p)

def build_resources(framework_out_path, project_path, projectbuilder_path):
    with open(os.path.join(project_path,"project.json")) as f:
        project = json.load(f)
    resources = project["distributions"]["CasioCg"]["resources"]
    output_path = os.path.join(project_path, project["output"])
    build_path = os.path.join(project_path, project["build"])
    resources_data = {
        "assets":{}
    }
    clear_resources(project_path, project)
    ID = 0
    for file in resources["images"]:
        if "external" in file[2]:
            continue
        filename = os.path.basename(file[0])
        file_id = ID
        profile = str(file[2]).replace("_bopti-image","")
        ID+=1
        txt = f"""
{filename}:
  name: IMG_ASSET_{file_id}
  type: bopti-image
  profile: {profile}
"""
        file_path = file[0]
        if os.path.isabs(file_path):
            file_path = os.path.relpath(file_path, project_path)
        file_path = file_path.replace("\\","/")
        resources_data["assets"][file_path] = {"id" : file_id, "name" : f"IMG_ASSET_{file_id}", "dest" : file[1]}
        #add in .txt
        p = os.path.join(project_path,os.path.dirname(file[0]), "fxconv-metadata.txt")
        p = os.path.abspath(p)
        if os.path.exists(p):
            with open(p, "a") as f:
                f.write(txt)
        else:
            with open(p, "w") as f:
                f.write(txt)

    return resources_data