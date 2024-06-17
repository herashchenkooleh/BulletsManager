import os
import subprocess
import shutil

def copytree(src, dst, symlinks=False, ignore=None):
    if (not os.path.exists(dst)):
        os.mkdir(dst)
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        
        if os.path.isdir(s):
            shutil.copytree(s, d, symlinks, ignore, dirs_exist_ok=True)
        else:
            shutil.copy2(s, d)

current_path = os.path.abspath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
build_dir_path = os.path.abspath(os.path.join(current_path, '..', '.build'))
binaries_dir_path = os.path.abspath(os.path.join(current_path, '..', '.bin'))
src_assets_path = os.path.abspath(os.path.join(current_path, '..', 'assets'))
dst_assets_path = os.path.abspath(os.path.join(current_path, '..', '.bin/assets'))

subprocess.call(['cmake', '--build', build_dir_path, '--config', 'Release'])
copytree(src_assets_path, dst_assets_path)