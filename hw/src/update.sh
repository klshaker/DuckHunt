#!/bin/bash
CL='\033[0;35m'
NC='\033[0m' # No Color

echo -e "${NC}"
echo -e "${CL}"
echo -e "Updating Design..."
echo -e "Cleaning old files..."
echo -e "${NC}"
make qsys-clean; make quartus-clean
echo -e "${NC}"
echo -e "${CL}"
echo -e "==========================="
echo -e "Running qsys..."
echo -e "============================${NC}"
make qsys
echo -e "${NC}"
echo -e "${CL}"
echo -e "==========================="
echo -e "Running Quartus..."
echo -e "============================${NC}"
make quartus
echo -e "${NC}"
echo -e "${CL}"
echo -e "==========================="
echo -e "Compiling rbf and dtb..."
echo -e "===========================${NC}"
make rbf
/bin/bash embedded_command_shell.sh
make dtb
echo -e "${NC}"
echo -e "${CL}"
echo -e "Done"
echo -e "${NC}"
