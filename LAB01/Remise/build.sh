#!/bin/bash
varRemisePath=$(pwd)
varRunCmdFolder="./RunCmd"
varLog710ShellFolder="./Log710Shell"
varLog710Shell2Folder="./Log710Shell2"

clear

echo "----------------------------------------------"
echo "    Ecole de Technologie Superieures (ETS)"
echo "LOG710 - Principes des systemes d'exploitation"
echo "                Laboratoire 01"
echo "                  Equipe 08"
echo "-----------------------------------------------"
echo

# RunCmd project
echo "Building RunCmd project..."

if [[ -d ${varRunCmdFolder} ]]; then
	cd ${varRunCmdFolder}
	gcc -std=gnu99 runCmd.c -o RunCmd
	chmod 777 RunCmd
	echo "BUILD SUCCESS"
	echo "To run this project execute this command : ./RunCmd/RunCmd"
else
	echo "BUILD ERROR, cannot compile RunCmd, project doesn't exist"
fi
echo

cd ${varRemisePath}

# Log710Shell project
echo "Building Log710Shell project..."

if [[ -d ${varLog710ShellFolder} ]]; then
	cd ${varLog710ShellFolder}
	gcc -std=gnu99 Log710Shell.c -o Log710Shell
	chmod 777 Log710Shell
	echo "BUILD SUCCESS"
	echo "To run this project execute this command : ./Log710Shell/Log710Shell"
else
	echo "BUILD ERROR, cannot compile Log710Shell, project doesn't exist"
fi

echo

cd ${varRemisePath}

# Log710Shell2 project
echo "Building Log710Shell2 project..."

if [[ -d ${varLog710Shell2Folder} ]]; then
	cd ${varLog710Shell2Folder}
	gcc -std=gnu99 Log710Shell2.c -o Log710Shell2
	chmod 777 Log710Shell2
	echo "BUILD SUCCESS"
	echo "To run this project execute this command : ./Log710Shell2/Log710Shell2"
else
	echo "BUILD ERROR, cannot compile Log710Shell2, project doesn't exist"
fi

exit 0
