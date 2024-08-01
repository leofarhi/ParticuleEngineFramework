import os, sys
import subprocess
import importlib
import importlib.util
import shutil
import json

dir_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(dir_path)

framework_path = os.path.join(dir_path,"..")
framework_out_path = os.path.join(framework_path,"Output")

def PrintChoices(dico):
    txt =""
    i = 1
    for key, value in dico.items():
        txt += f"{i}. {key} : {value[1]}\n"
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