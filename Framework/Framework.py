import os, sys
import subprocess
import importlib
import shutil

dir_path = os.path.dirname(os.path.realpath(__file__))

build_path = os.path.join(dir_path, "Build")
output_path = os.path.join(dir_path, "Output")
base_path = os.path.join(dir_path, "Sources","BaseFramework")
print(dir_path)

os.chdir(dir_path)

def print_error():
    print("Usage: [command] [distribution] [args] or help for more information.")
    sys.exit(1)

def MatchDistribution(distribution):
    lst = os.listdir(os.path.join("Sources","Distributions"))
    for item in lst:
        if item.lower() == distribution.lower():
            return item

args = sys.argv[1:]
if len(args) < 1:
    print_error()

cmd_available = ["install", "build"]

command = args[0].lower()
if command == "help":
    print("print : Print all the distributions available.")
    print("install [distribution] : Install the specified distribution.")
    print("build [distribution] : Build the specified distribution.  ex: build Windows")
    print("build [distribution] [packages:list] ex: build Windows [\"package1\", \"package2\"]")
    sys.exit(0)
elif command == "print":
    # Print all the distributions available
    distributions = os.listdir(os.path.join("Sources","Distributions"))
    for dist in distributions:
        print(dist)
    sys.exit(0)
elif command == "clean" and len(args) == 1:
    if os.path.exists(build_path):
        shutil.rmtree(build_path)
    if os.path.exists(output_path):
        shutil.rmtree(output_path)
    sys.exit(0)
elif command not in cmd_available:
    print_error()

distribution = MatchDistribution(args[1])

# Load the distribution
try:
    dist = importlib.import_module(f"Sources.Distributions.{distribution}.Distribution")
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