#!/bin/bash
varRemisePath=$(pwd)
varMemoryManager="./memoryManager"

clear

echo "-----------------------------------------------"
echo "    Ecole de Technologie Superieures (ETS)"
echo "LOG710 - Principes des systemes d'exploitation"
echo "                Laboratoire 03"
echo "                  Equipe 08"
echo "-----------------------------------------------"
echo

# RunCmd project
echo "Building Memory Manager project..."

if [[ -d ${varMemoryManager} ]]; then
	cd ${varMemoryManager}
	gcc -std=gnu99 -Wall -w main.c logger.c linkedList.c allocationStrategy.c allocationStrategyBestFitTest.c allocationStrategyFirstFitTest.c allocationStrategyNextFitTest.c allocationStrategyWorstFitTest.c -o memoryManager
	chmod 777 memoryManager
	echo "BUILD SUCCESS"
	echo "To run this project execute this command : ./memoryManager/memoryManager"
else
	echo "BUILD ERROR, cannot compile memoryManager, project doesn't exist"
fi
echo

cd ${varRemisePath}

exit 0

