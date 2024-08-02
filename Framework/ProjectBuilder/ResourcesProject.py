from ProjectEnv import *

def Resources(args):
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
    distribution = MatchDistribution(distribution)
    if distribution == None:
        ErrorMsg("La distribution spécifiée n'existe pas")
    try:
        distributions_path = os.path.join(framework_path,"Sources","Distributions", distribution, "ProjectBuilder")
        spec=importlib.util.spec_from_file_location("Build",os.path.join(distributions_path,"Resources.py"))
        resources_mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(resources_mod)
    except ModuleNotFoundError:
        ErrorMsg("Erreur lors de l'importation du Builder")
    resources_mod.edit_project(os.path.realpath(path), args[2:])
    