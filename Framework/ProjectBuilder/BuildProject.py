from ProjectEnv import *
import time

def BuildInfo(path, distribution, project):
    dico = {
        "distribution": distribution,
        "date": time.strftime("%d/%m/%Y"),
        "output": project["output"]
    }
    with open(os.path.join(path,"build_info.json"),"w") as f:
        json.dump(dico,f)
def Build(args):
    global framework_out_path
    if len(args) == 0:
        path = input("Veuillez entrer le chemin du projet :")
        distribution = input("Veuillez entrer la distribution :")
        rebuildFramework = input("Voulez-vous reconstruire le framework ? (y/n) :")
        if rebuildFramework.lower() in ["y","yes","oui"]:
            rebuildFramework = True
        elif rebuildFramework.lower() in ["n","no","non"]:
            rebuildFramework = False
        else:
            ErrorMsg("Réponse invalide")

    elif len(args) == 2:
        path = args[0]
        distribution = args[1]
        rebuildFramework = True
    elif len(args) == 3:
        path = args[0]
        distribution = args[1]
        if args[2].lower() in ["y","yes","oui"]:
            rebuildFramework = True
        elif args[2].lower() in ["n","no","non"]:
            rebuildFramework = False
        else:
            ErrorMsg("Réponse invalide")
    else:
        ErrorMsg("Nombre d'arguments invalide")
    #check if path exists and is a directory
    if not os.path.exists(path):
        ErrorMsg("Le chemin spécifié n'existe pas")
    if not os.path.isdir(path):
        ErrorMsg("Le chemin spécifié n'est pas un dossier")
    #check if project.json exists
    if not os.path.exists(os.path.join(path,"project.json")):
        ErrorMsg("Le fichier project.json n'existe pas")
    #load project.json
    with open(os.path.join(path,"project.json")) as f:
        project = json.load(f)
    #check if project.json is valid
    #check if framework version is compatible
    if not "version_framework" in project:
        ErrorMsg("Le fichier project.json est invalide")
    #Build Framework
    packages = project["packages"]
    packages_arg = '"['
    for i in packages:
        packages_arg += i + ","
    packages_arg = packages_arg[:-1] + ']"'
    file = "."+os.sep+"Framework.py"
    cmd = sys.executable +" "+file+" build "+distribution+" "+packages_arg
    print(cmd)
    if rebuildFramework:
        res = subprocess.Popen(cmd, shell=True, cwd=framework_path)
        res.wait()
        #check if success
        if res.returncode != 0:
            ErrorMsg("Erreur lors de la construction du framework")
    #Build Project
    distribution = MatchDistribution(distribution)
    if distribution == None:
        ErrorMsg("La distribution spécifiée n'existe pas")
    try:
        #builder = importlib.import_module(f"..Sources.Distributions.{distribution}.ProjectBuilder.Build")
        distributions_path = os.path.join(framework_path,"Sources","Distributions", distribution, "ProjectBuilder")
        spec=importlib.util.spec_from_file_location("Build",os.path.join(distributions_path,"Build.py"))
        builder = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(builder)
    except ModuleNotFoundError:
        ErrorMsg("Erreur lors de l'importation du Builder")
    BuildInfo(path, distribution, project)
    #real path of path and framework_out_path
    framework_out_path = os.path.realpath(framework_out_path)
    path = os.path.realpath(path)
    res = builder.build(framework_out_path, path)
    if res.returncode != 0:
        ErrorMsg("Erreur lors de la construction du projet")