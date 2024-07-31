from ProjectEnv import *

def Build(args):
    global framework_out_path
    if len(args) == 0:
        path = input("Veuillez entrer le chemin du projet :")
        distribution = input("Veuillez entrer la distribution :")
    elif len(args) == 2:
        path = args[0]
        distribution = args[1]
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
    res = subprocess.Popen(cmd, shell=True, cwd=framework_path)
    res.wait()
    #check if success
    if res.returncode != 0:
        ErrorMsg("Erreur lors de la construction du framework")
    #Build Project
    try:
        #builder = importlib.import_module(f"..Sources.Distributions.{distribution}.ProjectBuilder.Build")
        distributions_path = os.path.join(framework_path,"Sources","Distributions", distribution, "ProjectBuilder")
        spec=importlib.util.spec_from_file_location("Build",os.path.join(distributions_path,"Build.py"))
        builder = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(builder)
    except ModuleNotFoundError:
        ErrorMsg("Erreur lors de l'importation du Builder")
    #real path of path and framework_out_path
    framework_out_path = os.path.realpath(framework_out_path)
    path = os.path.realpath(path)
    res = builder.build(framework_out_path, path)
    if res.returncode != 0:
        ErrorMsg("Erreur lors de la construction du projet")