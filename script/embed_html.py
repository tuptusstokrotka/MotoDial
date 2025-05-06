import os
import subprocess

from pathlib import Path

RED     = "\033[0;31m"
GREEN   = "\033[0;32m"

ROOT_DIR = os.path.abspath(os.curdir)

HTML_FILE = os.path.join(ROOT_DIR, 'data\\index.html')
HTML_HEADER_FILE = os.path.join(ROOT_DIR, 'data\\build\\html.h')

CSS_FILE = os.path.join(ROOT_DIR, 'data\\style.css')
CSS_HEADER_FILE = os.path.join(ROOT_DIR, 'data\\build\\css.h')

JS_FILE = os.path.join(ROOT_DIR, 'data\\script.js')
JS_HEADER_FILE = os.path.join(ROOT_DIR, 'data\\build\\js.h')


def open_or_create(source):
    try:
        file = open(source, 'w')
        file.close()
    except:
        output_file = Path(source)
        output_file.parent.mkdir(exist_ok=True, parents=True)
        output_file.write_text("")

def file_to_header(source, output, name):
    try:
        if not os.path.exists(source):
            raise FileNotFoundError(f"File does not exist: {source}")

        open_or_create(output)
        with open(source, 'rb') as f_in, open(output, 'w') as f_out:
            # Print Header
            f_out.write("const char " + name + "[] = {")
            byte = f_in.read(1)
            first_byte = True
            msg_len=0

            # Print content
            while byte:
                msg_len+=1
                if not first_byte:
                    f_out.write(", ")
                first_byte = False
                f_out.write(f"0x{byte.hex()}")
                byte = f_in.read(1)
            f_out.write("};\n")

            # Print Length
            f_out.write("unsigned int " + name + "_len = " + str(msg_len) + ";")
        print("Embedding " + name +":\t\t" + GREEN + "SUCCESS")

    except Exception as e:
        # By this way we can know about the type of error occurring
        print("Embedding " + name +":\t\t" + RED + "FAILED")
        print(RED + "Error:",e)


file_to_header(HTML_FILE,   HTML_HEADER_FILE,   "html")
file_to_header(CSS_FILE,    CSS_HEADER_FILE,    "css")
file_to_header(JS_FILE,     JS_HEADER_FILE,     "js")