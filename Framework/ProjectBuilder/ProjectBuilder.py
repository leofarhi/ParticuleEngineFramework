from ProjectEnv import *
import NewProject
import BuildProject
import RunProject

commandes_valid = {
    "new": ((NewProject.CreateProject),"Crée un nouveau projet"),
    "build": ((BuildProject.Build),"Construit le projet"),
    "run": ((RunProject.Run),"Exécute le projet")
}

if len(sys.argv) <= 1:
    print("Sélectionnez la commande à exécuter:")
    PrintChoices(commandes_valid)
    commande = GetRes(input("Commande: "),list(commandes_valid.keys()))
else:
    commande = sys.argv[1].lower()
if commande is None or commande not in commandes_valid.keys():
    ErrorMsg("Commande invalide")

args = sys.argv[2:]
commandes_valid[commande][0](args)