from ProjectEnv import *

def Run(args):
    global framework_out_path
    if len(args) == 0:
        path = input("Veuillez entrer le chemin du projet :")
    elif len(args) == 1:
        path = args[0]
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
    #check if build_info.json exists
    if not os.path.exists(os.path.join(path,"build_info.json")):
        ErrorMsg("Le fichier build_info.json n'existe pas")
    #load project.json
    with open(os.path.join(path,"project.json")) as f:
        project = json.load(f)
    #load build_info.json
    with open(os.path.join(path,"build_info.json")) as f:
        build_info = json.load(f)
    output = build_info["output"]
    distribution = build_info["distribution"]
    try:
        distributions_path = os.path.join(framework_path,"Sources","Distributions", distribution, "ProjectBuilder")
        spec=importlib.util.spec_from_file_location("Run",os.path.join(distributions_path,"Run.py"))
        runner = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(runner)
    except ModuleNotFoundError:
        ErrorMsg("Erreur lors de l'importation du Runner")
    output = os.path.join(path,output)
    runner.run(output, project)
