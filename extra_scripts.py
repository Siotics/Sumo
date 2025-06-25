import os
import shutil
from SCons.Script import Import

Import("env")

def copy_dist_to_data(source, target, env):
    dist_dir = os.path.join("web", "build")
    data_dir = os.path.join("data")

    if not os.path.exists(dist_dir):
        print("ERROR: build directory not found, please build the web first, you can see the manual at README.md file")
        return 1
    print("Copying frontend build to data/ folder")

    if os.path.exists(data_dir):
        shutil.rmtree(data_dir)

    shutil.copytree(dist_dir, data_dir)

    print("Done copying files to data/")

def upload_littlefs(source, target, env):
    dist_dir = os.path.join("web", "build")
    if not os.path.exists(dist_dir):
        print("ERROR: build directory not found, please build the web first, you can see the manual at README.md file")
        return 1
    env.Execute("pio run -t buildfs")
    env.Execute("pio run -t uploadfs")

env.AddPreAction("buildfs", copy_dist_to_data)
env.AddPreAction("upload", upload_littlefs)