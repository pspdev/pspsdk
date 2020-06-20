#!/usr/bin/env bash

# This is a hacky, makeshift script to automatically patch .S files for clang.
# It is by no means extensive or robust. Assumes you have ripgrep installed,
# and the GCC PSP toolchain installed to /usr/local/pspdev/

file="$1"

while IFS= read -r line; do
    if ! echo "$line" | rg '^\s+(clz|ins|movz|ext|mfic|mtic)' >/dev/null; then
        echo "$line" >> "$file".out
        continue
    fi

    asm=psptmp.S

    # Copy over defines and the assembly line in question
    rg '#define' "$file" > $asm
    echo "$line" >> $asm

    /usr/local/pspdev/bin/psp-gcc -c $asm
    hex=$(
        /usr/local/pspdev/bin/psp-objdump -d psptmp.o \
            | rg '\s+\w+:' | head -1 | awk '{ print "0x" $2 }'
    )

    echo Patching "$line" to $hex
    echo "    .word $hex // $line" >> "$file".out

    rm $asm psptmp.o
done < "$file"

mv "$file".out "$file"
