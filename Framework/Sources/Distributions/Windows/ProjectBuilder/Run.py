import os, sys
import json
import shutil
import subprocess

def run(output, project):
    windows = project["distributions"]["Windows"]
    subprocess.Popen(".\\"+windows["executable"], shell=True, cwd=output).wait()