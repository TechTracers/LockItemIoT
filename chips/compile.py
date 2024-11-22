import glob
import os
import pathlib

# wasi-sdk path
WASI_PATH = "C:/wasi-sdk-24.0-x86_64-windows"

TEMPLATE_CHIP_DATA = "/* NMEA_ARRAY_DATA */"
TEMPLATE_CHIP_PATH = "gps-neo6m.chip"
CONFIG_TEMPLATE_CHIP_PATH = "gps-neo6m.chip.json"
WOKWI_API_HEADER_PATH = "wokwi-api.h"

OUTPUT_FOLDER = "."
DATA_FOLDER = "data"

clang = pathlib.Path(WASI_PATH, "bin", "clang")
sysroot = pathlib.Path(WASI_PATH, "share", "wasi-sysroot")


def compileChip(source, target=None):
    if not target:
        target = pathlib.Path(source).with_suffix(".wasm")
    os.system(f"{clang} --target=wasm32-unknown-wasi --sysroot {sysroot} -nostartfiles -Wl,--import-memory -Wl,"
              f"--export-table -Wl,--no-entry -Werror -o {target} {source}")


def sentenceToString(sentence):
    return f'"{sentence.strip()}\\r\\n"'


# converts the nmea sentences to a c array (string representation)
def sentencesToCode(sentences):
    code = "\n const char gps_tx_data[][80] = { // "
    code += ",\n    ".join(map(sentenceToString, sentences))
    code += "\n  };"

    return code


out = pathlib.Path(OUTPUT_FOLDER)
template_name = os.path.splitext(CONFIG_TEMPLATE_CHIP_PATH)[0]

# reads the template file
with open(TEMPLATE_CHIP_PATH, encoding="utf-8") as fs:
    template = fs.read()

# reads the config template file
with open(CONFIG_TEMPLATE_CHIP_PATH, encoding="utf-8") as fs:
    config_template = fs.read()

with open(WOKWI_API_HEADER_PATH, encoding="utf-8") as fs:
    wokwi_api_header = fs.read()

c_suffix = ".c"
json_suffix = ".json"

# iterates over each .nmea file
for file in glob.glob(f"{DATA_FOLDER}/**/*.nmea", recursive=True):
    print("Compiling {}...".format(file))
    file = pathlib.Path(file)
    code = sentencesToCode(file.read_text(encoding="utf-8").splitlines())
    code = template.replace(TEMPLATE_CHIP_DATA, code, 1)
    filename = os.path.splitext(file.name)[0]

    chip_file = out.joinpath(filename, template_name + c_suffix)
    config_file = chip_file.with_suffix(json_suffix)
    header_file = chip_file.parent.joinpath("wokwi-api.h")

    store = chip_file.parent
    store.mkdir(parents=True, exist_ok=True)

    chip_file.write_text(code, encoding="utf-8")
    config_file.write_text(config_template, encoding="utf-8")
    header_file.write_text(wokwi_api_header, encoding="utf-8")

    compileChip(chip_file)

    # chip_file.unlink()
    header_file.unlink()
