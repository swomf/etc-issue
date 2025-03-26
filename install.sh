#!/usr/bin/env bash

CDEF="\033[0m"      # default color
CCIN="\033[0;36m"   # info color
CGSC="\033[0;32m"   # success color
CRER="\033[0;31m"   # error color
CWAR="\033[0;33m"   # warning color
b_CDEF="\033[1;37m" # bold default color
b_CCIN="\033[1;36m" # bold info color
b_CGSC="\033[1;32m" # bold success color
b_CRER="\033[1;31m" # bold error color
b_CWAR="\033[1;33m" # bold warning color

if [ -z "$1" ]; then
  echo -e "${CRER}Error: No file specified.${CDEF}"
  exit 1
elif [ ! -f "$1" ]; then
  echo -e "${CRER}Error: File does not exist.${CDEF}"
  exit 1
fi

echo "Copy $1 to /etc/issue?"
read -n 1 -p "Continue? [y/N] " input
echo
if [ "$input" != "y" ] && [ "$input" != "Y" ]; then
  echo -e "${CRER}Error: Aborted by user.${CDEF}"
  exit 1
fi

set -x
sudo install "$1" -Dm644 /etc/issue
set +x

echo -e "${CGSC}Success.${CDEF} Installed $1 to /etc/issue."
