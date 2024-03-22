#!/bin/bash

GREY_COLOR="\033[0;90m"
RED_COLOR="\033[1;31m"
MAGENTA_COLOR="\033[1;35m"
GREEN_COLOR="\033[1;32m"
RESET_COLOR="\033[0m"

# Check if the correct number of arguments is provided
if [ "$#" -lt 1 ]; then
  echo -e "${RED_COLOR}Missing arguments${RESET_COLOR}"
  echo -e "${GREY_COLOR}╰┈➤ Usage example: $0 <program> [arguments...]${RESET_COLOR}\n"
  exit 1
fi

PROGRAM=$1
shift # Remove the first argument, which is the program name, the rest are the program's arguments

# Collect the remaining arguments. If none, set ARGUMENTS to "none"
if [ "$#" -eq 0 ]; then
  ARGUMENTS="none"
else
  ARGUMENTS="$@"
fi

LOGS_DIR="logs"
LOGS_FILE_NAME="valgrind_report.txt"

# Check if the logs directory and valgrind_report.txt file exists, create them if not
if [ ! -d $LOGS_DIR ]; then
  mkdir -p $LOGS_DIR
fi

if [ ! -f "${LOGS_DIR}/${LOGS_FILE_NAME}" ]; then
  touch "${LOGS_DIR}/${LOGS_FILE_NAME}"
fi

# Prepare suppression flags for each .supp file found
SUPPRESSION_FLAGS=""
SUPP_FILES_FOUND=()
for supp_file in *.supp; do
  if [ -f "$supp_file" ]; then # Check if the glob gets expanded to existing files.
    SUPPRESSION_FLAGS+="--suppressions=$supp_file "
    SUPP_FILES_FOUND+=("$supp_file")
  else
    break # If no .supp files found, break out of the loop.
  fi
done

# Remove trailing space
SUPPRESSION_FLAGS=${SUPPRESSION_FLAGS% }

OTHER_FLAGS="--leak-check=full --show-leak-kinds=all"

# Print details in dark green
echo -e "${GREY_COLOR}Program: ${PROGRAM} Arguments: ${ARGUMENTS}${RESET_COLOR}"
echo -e "${GREY_COLOR}Suppression Files: ${MAGENTA_COLOR}${SUPP_FILES_FOUND[*]}${RESET_COLOR}"
echo -e "${GREY_COLOR}Flags: ${OTHER_FLAGS}${RESET_COLOR}"
echo -e "${GREY_COLOR}Logs 🗁  ${LOGS_DIR}/${LOGS_FILE_NAME}${RESET_COLOR}\n"
echo -e "${GREEN_COLOR}Running Valgrind 🌪${RESET_COLOR}\n\n"

valgrind $SUPPRESSION_FLAGS $OTHER_FLAGS "--log-file=${LOGS_DIR}/${LOGS_FILE_NAME}" "${PROGRAM}" "$@"