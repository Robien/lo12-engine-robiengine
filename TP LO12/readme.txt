======================
Contenu du répertoire
======================
- dll : contient les différentes dll nécessaires à l'exécution
- include : contient les différentes d'en-têtes nécessaires à la compilation
- lib : contient les différentes lib nécessaires à la compilation
- models : contient les scènes et modèles 3D (.dat ou .3ds)
- Read3dsFile : projet d'exemple pour la lecture de fichier .3ds (3dsMax)
- textures : contient les textures (images .png)
- TPx : code source de départ pour les TP


================================
Bibliothèques utilisées en LO12
================================
- OpenGL (Open Graphics Library) : API 3D. Fournie avec Visual Studio et Windows.
- GLU (OpenGL Utility Library) : apporte des fonctions de haut-niveau à OpenGL. Fournie avec Visual Studio et Windows.
- GLUT (OpenGL Utility Toolkit) 3.7.6 : permet de gérer des fenêtres OpenGL et les évènements souris/clavier. Disponible ici : http://www.xmission.com/~nate/glut.html
- lib3ds 2.0.0 RC1 : permet la lecture et l'écriture de fichiers .3ds (3dsMax). Disponible ici : http://code.google.com/p/lib3ds/
- libpng 1.5.4 : permet la lecture et l'écriture d'images au format .png. Disponible ici : http://www.libpng.org/pub/png/libpng.html
- zlib 1.2.5 : permet de compresser/décompresser des fichiers et est utilisée par libpng. Disponible ici : http://zlib.net/


======================================
Compilation des projets Visual Studio
======================================
Pour compiler les projets Visual Studio, il est nécessaire de modifier les propriétés des projets (menu Projet\Propriétés) comme suit :
	- Propriétés de configuration\Débogage\Répertoire de travail = ..
	- Propriétés de configuration\Débogage\Environnement = PATH=dll\%3b$(PATH)

La première propriété permet de définir le répertoire parent au fichier projet comme répertoire racine pour les liens relatifs.
La seconde propriété permet d'ajouter temporairement le dossier dll à la variable d'environnement PATH. En effet, lors de l'exécution d'une application, les dll sont recherchées dans l'ordre suivant (http://support.microsoft.com/kb/462977/fr) :
- la mémoire (si la dll est déjà en cours d'utilisation) ;
- le répertoire de travail de l'application ;
- le répertoire Windows ;
- le répertoire System de Windows ;
- le répertoire de l'exécutable ;
- les répertoires définies par la variable d'environnement PATH.

Ces deux propriétés de projet sont enregistrées dans un fichier nommé monProjet.vcproj.nomOrdinateur.nomUtilisateur.user
Il est donc nécessaire de les re-modifier à chaque changement d'utilisateur ou de machine.


======================================================
Exécution des applications en dehors de Visual Studio
======================================================
Pour exécuter vos applications en dehors de Visual Studio, vous devez créer une arborescence comme suit :
	monAppli.exe
	glut32.dll
	lib3ds-2_0.dll
	libpng15.dll
	zlib1.dll
	models\
		TP1.dat
		jeep.3ds
		...
	textures\
		bois.png
		...
