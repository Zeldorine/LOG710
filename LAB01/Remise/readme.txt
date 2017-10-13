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
Ce projet porte sur le laboratoire 1 du cours LOG710.
Il se divise en 3 parties :
   1) Execution d'une commande - RunCmd
   2) Interpreteur de commandes de bases - Log710Shell
   3) Interpreteur de commandes de bases avec commande en arriere plan - Log710Shell2


La premiere partie porte sur la conception et l'implementation d'un programme qui prends
en entree une commande UNIX comme argument et execute l'action associee a cette commande
et ensuite affiche des statistiques relatives a l'execution de cette commande.

La seconde partie etend le le programme RunCmd pour en faire un interpreteur de commandes (shell).

La derniere partie a pour objectif d'ameliorer l'interpreteur de commandes en traitant des taches 
en arriere-plan.

----------------------
     PRE-REQUIS
----------------------
le compilateur gcc est requis et doit donc etre installe sur le poste avant l'execution du script 
de compilation.

----------------------
     UTILISATION
----------------------
Ce laboratoire est constitue de 3 projets situe dans les 3 dossiers suivant :
   - RunCmd
   - Log710Shell
   - Log710Shell2

Un script build.sh permet de compiler chacun de ces projets et produit un executable pour chacun d'eux.
ATTENTION, pour executer ce fichier, gcc est requis et doit donc etre installe sur le poste avant 
l'execution du script.

Il faut ensuite ouvrir un terminal et se deplacer dans le repertoire remise.
Puis executer la commande ci-dessous
   ./build.sh

Un executable est disponible apres la compilation dans chacun des repertoires et peut etre executer 
de cette facon :
   1) Pour la partie 1 : ./RunCmd/RunCmd <commande>
   2) Pour la partie 2 : ./Log710Shell/Log710Shell
   3) Pour la partie 3 : ./Log710Shell2/Log710Shell2
