import os, sys
import subprocess
import importlib

dir_path = os.path.dirname(os.path.realpath(__file__))

build_path = os.path.join(dir_path, "Build")
output_path = os.path.join(dir_path, "Output")
base_path = os.path.join(dir_path, "BaseFramework")
print(dir_path)

os.chdir(dir_path)

def print_error():
    print("Usage: [command] [distribution] or help for more information.")
    sys.exit(1)

def MatchDistribution(distribution):
    lst = os.listdir("Distributions")
    for item in lst:
        if item.lower() == distribution.lower():
            return item

args = sys.argv[1:]
if len(args) < 1:
    print_error()

cmd_available = ["install", "build", "demo"]

command = args[0].lower()
if command == "help":
    print("print : Print all the distributions available.")
    print("install [distribution] : Install the specified distribution.")
    print("build [distribution] : Build the specified distribution.")
    sys.exit(0)
elif command == "print":
    # Print all the distributions available
    distributions = os.listdir("Distributions")
    for dist in distributions:
        print(dist)
    sys.exit(0)
elif command == "clean":
    if os.path.exists(build_path):
        os.rmdir(build_path)
    if os.path.exists(output_path):
        os.rmdir(output_path)
    sys.exit(0)
elif command not in cmd_available:
    print_error()

distribution = MatchDistribution(args[1])

# Load the distribution
try:
    dist = importlib.import_module(f"Distributions.{distribution}.Distribution")
except ModuleNotFoundError:
    print("The distribution specified does not exist.")
    sys.exit(1)


#check if the dist has commands
if False in [hasattr(dist, cmd) for cmd in cmd_available]:
    print("The distribution specified does not have the command specified.")
    sys.exit(1)

command = getattr(dist, command)
command(base_path, build_path, output_path, args[2:])
sys.exit(0)