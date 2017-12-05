----------------------
	AUTEUR
----------------------
Equipe 08

Etudiants :
   - Tony Cazorla   (CAZT02069204)
   - Michael Nadeau (NADM28069300)


----------------------
PROJET - DESCRIPTION
----------------------
Ce projet porte sur le laboratoire 3 du cours LOG710.
Il se divise en 2 parties :
   1) Une premiere phase qui consiste à développer une structure de donnees pour implementer un gestionnaire de memoire avec une strategy first-fit
   2) Une seconde phase pour ajouter au gestionnaire de memoire precedent les strategies suivantes :
      a) best-fit
      b) worst-fit
      c) next-fit


----------------------
     PRE-REQUIS
----------------------
Le compilateur gcc est requis et doit donc etre installe sur le poste avant l'execution du script 
de compilation.

----------------------
     UTILISATION
----------------------
Ce laboratoire est constitue d'un projet situe dans le dossier suivant :
   - memoryManager/

Un script build.sh permet de compiler le projet et de produire un executable.
ATTENTION, pour executer ce fichier, gcc est requis et doit donc etre installe sur le poste avant 
l'execution du script.

Il faut ensuite ouvrir un terminal et se deplacer dans le repertoire remise.
Puis executer la commande ci-dessous
   ./build.sh

Un executable est disponible apres la compilation dans chacun des repertoires et peut etre executer 
de cette facon :
   1) ./memoryManager/memoryManager -> execute le main de l'application qui va lancer les cas de tests pour chacunes des strategies.
