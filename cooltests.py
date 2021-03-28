from pathlib import Path
import re
import subprocess
import sys
from typing import Optional

nm_line_regex = re.compile(
    r"(\w+) (\w) (.*)"
)


def extract_test_symbol(nm_line) -> Optional[str]:
    match = nm_line_regex.match(nm_line)

    if not match:
        return None
    
    _address, symbol_type, symbol = match.groups()

    if (
        symbol_type == "T" and
        symbol.startswith("test") and
        symbol.endswith("()")
    ):
        # remove the parenthesis
        return symbol[:-2]


def get_test_symbols(object_file):
    lines = subprocess.check_output(
        ['nm', '--defined-only', '--demangle', object_file],
        text=True
    ).split("\n")

    return [
        symbol
        for line in lines
        if (symbol := extract_test_symbol(line)) is not None
    ]


def generate_main_program(test_symbols):
    # I wish I could use jinja2 or some other templating
    # engine but want to keep python dependencies to the bare
    # minimum
    declarations = "\n".join([
        f'void {symbol}();'
        for symbol in test_symbols
    ])

    array_body = ",\n".join([
        '  {"%s", &%s}' % (symbol[4:], symbol)
        for symbol in test_symbols
    ])

    program = f"""
#include <cooltestslib_global.h>
{declarations}

namespace cooltestslib::global {{
  extern const int testNo = {len(test_symbols)};
  extern const Test tests[] = {{
    {array_body}
  }};
}}

"""

    return program


def compile_main_object_file(cxx_compiler, source, object_file, include_dir):
    dir = Path(object_file).parent
    source_file = dir / "main_source.cpp"
    source_file.write_text(source)

    subprocess.check_call(
        [
            cxx_compiler,
            "-g3",
            "-I", include_dir,
            "-c", source_file,
            "-o", object_file,
        ],
        text=True,
    )


def main():
    output_object_file_name = sys.argv[1]
    object_files = sys.argv[2].split(";")
    cooltestslib_includedir = sys.argv[3]
    cxx_compiler = sys.argv[4]

    test_symbols = sum([
        get_test_symbols(file)
        for file in object_files
    ], [])

    main_program_source = generate_main_program(test_symbols)

    compile_main_object_file(
        cxx_compiler,
        main_program_source,
        output_object_file_name,
        cooltestslib_includedir
    )


if __name__ == "__main__":
    main()
