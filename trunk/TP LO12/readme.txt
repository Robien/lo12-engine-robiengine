======================
Contenu du r�pertoire
======================
- dll : contient les diff�rentes dll n�cessaires � l'ex�cution
- include : contient les diff�rentes d'en-t�tes n�cessaires � la compilation
- lib : contient les diff�rentes lib n�cessaires � la compilation
- models : contient les sc�nes et mod�les 3D (.dat ou .3ds)
- Read3dsFile : projet d'exemple pour la lecture de fichier .3ds (3dsMax)
- textures : contient les textures (images .png)
- TPx : code source de d�part pour les TP


================================
Biblioth�ques utilis�es en LO12
================================
- OpenGL (Open Graphics Library) : API 3D. Fournie avec Visual Studio et Windows.
- GLU (OpenGL Utility Library) : apporte des fonctions de haut-niveau � OpenGL. Fournie avec Visual Studio et Windows.
- GLUT (OpenGL Utility Toolkit) 3.7.6 : permet de g�rer des fen�tres OpenGL et les �v�nements souris/clavier. Disponible ici : http://www.xmission.com/~nate/glut.html
- lib3ds 2.0.0 RC1 : permet la lecture et l'�criture de fichiers .3ds (3dsMax). Disponible ici : http://code.google.com/p/lib3ds/
- libpng 1.5.4 : permet la lecture et l'�criture d'images au format .png. Disponible ici : http://www.libpng.org/pub/png/libpng.html
- zlib 1.2.5 : permet de compresser/d�compresser des fichiers et est utilis�e par libpng. Disponible ici : http://zlib.net/


======================================
Compilation des projets Visual Studio
======================================
Pour compiler les projets Visual Studio, il est n�cessaire de modifier les propri�t�s des projets (menu Projet\Propri�t�s) comme suit :
	- Propri�t�s de configuration\D�bogage\R�pertoire de travail = ..
	- Propri�t�s de configuration\D�bogage\Environnement = PATH=dll\%3b$(PATH)

La premi�re propri�t� permet de d�finir le r�pertoire parent au fichier projet comme r�pertoire racine pour les liens relatifs.
La seconde propri�t� permet d'ajouter temporairement le dossier dll � la variable d'environnement PATH. En effet, lors de l'ex�cution d'une application, les dll sont recherch�es dans l'ordre suivant (http://support.microsoft.com/kb/462977/fr) :
- la m�moire (si la dll est d�j� en cours d'utilisation) ;
- le r�pertoire de travail de l'application ;
- le r�pertoire Windows ;
- le r�pertoire System de Windows ;
- le r�pertoire de l'ex�cutable ;
- les r�pertoires d�finies par la variable d'environnement PATH.

Ces deux propri�t�s de projet sont enregistr�es dans un fichier nomm� monProjet.vcproj.nomOrdinateur.nomUtilisateur.user
Il est donc n�cessaire de les re-modifier � chaque changement d'utilisateur ou de machine.


======================================================
Ex�cution des applications en dehors de Visual Studio
======================================================
Pour ex�cuter vos applications en dehors de Visual Studio, vous devez cr�er une arborescence comme suit :
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
