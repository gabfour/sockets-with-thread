# sockets-with-thread

Fabien Saul

Ismail FOCHIVE

Gabriel Fourtoy

Alexandre DAVAULT



### Description du projet

- Jeu de société choisi : 6 qui prend
- 1à joueurs maximum, mais l'affichage est pour 4
- Architecture choisie : MVVM



### Lancer le projet

- Ouvrir la solution avec Visual Studio

- Définir le projet "Server" comme "Startup Project"

- Lancer le projet sans debugging

- Dans l'explorateur de fichier, aller à "sockets-with-thread\Client\bin\Debug\net6.0-windows" et lancer le Client.exe (10 clients possibles simultanément)

- Clicker sur "connect" pour chacun des clients

- Si des problèmes de librairies sont rencontrés, il faut ajouter dans les propriétés de Server:

  - c/c++, Additional include Directories : sockets-with-thread\Libs\json\single_include;

  - linker, Additional include Directories : \sockets-with-thread\Libs;
  - linker/input, Additional Dependencies : kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;




### Problèmes rencontrés

- Des personnes dans le groupe étaient cas contact ou avait le COVID durant vos séances, ceci nous a beaucoup ralenti 
- La mise en place de l'architecture et la compréhension du langage C++ et C#  
- La mise en place des messages en JSON, avec du recul je pense que ce n'était pas nécessaire de mettre en place des messages en JSON 
- La gestion de projet, et la répartition des tâches était mauvaise. Plus de point en groupe pour connaître l'avancement de chaque tâche aurait dû être mis en place, parfois une incompréhension concernant la partie Front 
- Langage méconnu par l'équipe et le développement d'un network et d'un front complexes ont nécessité un temps d'adaptation



### Lien GitHub

https://github.com/gabfour/sockets-with-thread



