import subprocess
import os
import shutil
import sys

ROOT_DIR = os.path.abspath(os.curdir)
TARGET_FILE = os.path.join(ROOT_DIR, 'include/version.h')

def find_git_path():
    # Attempt to locate via system PATH
    git_path = shutil.which("git")
    if git_path:
        print(f"Found git in PATH: {git_path}")
        return git_path

    # Fallback to common Windows install paths
    fallback_paths = [
        os.path.expandvars(r"%ProgramFiles%\Git\cmd\git.exe"),
        os.path.expandvars(r"%ProgramFiles(x86)%\Git\cmd\git.exe"),
        os.path.expandvars(r"%LocalAppData%\Programs\Git\cmd\git.exe"),
    ]

    for path in fallback_paths:
        if os.path.exists(path):
            print(f"Found git at fallback location: {path}")
            return path

    print("Error: Git executable not found. Please ensure Git is installed and added to the system PATH.", file=sys.stderr)
    sys.exit(1)

GIT_PATH = find_git_path()

def run_git_command(command):
    """ Run a git command and return its output. """
    try:
        result = subprocess.run(
            [GIT_PATH] + command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=True,
            text=True
        )
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        return None

def get_commit_hash():
    """ Get the current commit hash. """
    result = run_git_command(['rev-parse', 'HEAD'])

    if(result != None):
        print(f"Git hash:\t\t\033[0;32m{result[:7]}\033[0m")
        return result[:7]

    print("Git hash:\t\t\033[0;33mNone\033[0m")
    return result

def get_build_tag():
    """ Get the build tag if available (assuming it is stored as a Git tag). """
    result = run_git_command(['describe', '--tags', '--abbrev=0'])

    if(result != None):
        print(f"Git tag:\t\t\033[0;32m{result}\033[0m")
        return result

    print("Git tag:\t\t\033[0;33mNone\033[0m")
    return result

def write_version_file(version_data):
    """ Write the version data to the target file. """
    with open(TARGET_FILE, 'w') as file:
        file.write(f'#ifndef VERSION_H_\n#define VERSION_H_\n\n')
        file.write(f'#define BUILD_TAG "{version_data["build_tag"]}"\n')
        file.write(f'#define COMMIT_HASH "{version_data["commit_hash"]}"\n')
        file.write(f'\n#endif')

version_data = {
    "build_tag": get_build_tag(),
    "commit_hash": get_commit_hash(),
}

write_version_file(version_data)