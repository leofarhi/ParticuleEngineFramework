ProjectBuilderPath = ""

import os, sys
import subprocess

dir_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(dir_path)

def PrintChoices(dico):
    txt =""
    i = 1
    for key, value in dico.items():
        txt += f"{i}. {key} : {value}\n"
        i+=1
    print(txt)

def ErrorMsg(msg):
    print("\033[91m"+msg+"\033[0m")
    sys.exit(1)

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

commandes_valid = {
    "build": "Construit le projet",
    "run": "Exécute le projet"
}

print("Sélectionnez la commande à exécuter:")
PrintChoices(commandes_valid)
commande = GetRes(input("Commande: "),list(commandes_valid.keys()))
if commande is None or commande not in commandes_valid.keys():
    ErrorMsg("Commande invalide")
if commande == "build":
    distribution = input("Veuillez entrer la distribution :")
    cmd = sys.executable + f" .{os.sep}ProjectBuilder.py build \"" + dir_path + "\" " + distribution
elif commande == "run":
    cmd = sys.executable + f" .{os.sep}ProjectBuilder.py run \"" + dir_path + '"'
print(cmd)
subprocess.Popen(cmd, shell=True, cwd=ProjectBuilderPath).wait()

