import os
import glob
from pathlib import Path

def find_vcvars():
    results = []

    # Racines à explorer
    base_dirs = [
        os.environ.get("ProgramFiles", r"C:\Program Files"),
        os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)")
    ]

    for base_dir in base_dirs:
        vs_root = Path(base_dir) / "Microsoft Visual Studio"
        if not vs_root.exists():
            continue

        for version_dir in vs_root.iterdir():
            if not version_dir.is_dir():
                continue
            for edition_dir in version_dir.iterdir():  # Community, BuildTools, etc.
                if not edition_dir.is_dir():
                    continue
                vc_path = edition_dir / "VC" / "Auxiliary" / "Build"
                if vc_path.exists():
                    for vcvars in vc_path.glob("vcvars*.bat"):
                        results.append({
                            "path": str(vcvars.resolve()),
                            "version": version_dir.name,
                            "edition": edition_dir.name,
                            "arch": "x86" if "Program Files (x86)" in str(base_dir) else "x64"
                        })

    return results

# Exemple d'utilisation
if __name__ == "__main__":
    vcvars_list = find_vcvars()
    if not vcvars_list:
        print("Aucun vcvars*.bat trouvé.")
    else:
        for entry in vcvars_list:
            print(f"[{entry['arch']}] Visual Studio {entry['version']} {entry['edition']} → {entry['path']}")
