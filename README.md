# sockets-with-thread



Première créer un joueur qui peut envoyer un message et en recevoir 

Deuxième distribution des cartes (10 cartes) par le serveur pour les joueurs (affichage sur la console du joueur ses cartes) 

Troisième distribution des cartes sur le plateau (4 cartes) affichage sur le serveur 

Quatrième joueur dépose une carte & la carte déposé se met sur une ligne (Changement d'affichage sur le serveur et le joueur) 

Cinquième Mise en place de tour après que les carte soient déposé sur le plateau

 Sixième Mettre en place le système de points (sur les cartes et sur les joueurs au début 0) 

Septième Enlever une ligne et la remplacer par la 6ème carte de la ligne, le joueur prend les points si il a déposé la 6ème carte





REGLES :  10 cartes par joueur, 4 cartes au centre.  

Si il y a 6 cartes sur une des lignes au centre le dernier joueur à avoir posé  prend la ligne, si une carte est inférieur au 4 cartes du centre il doit choisir une des lignes et la prendre.  Il y a 104 cartes. Tous les joueurs prennent une carte de leur jeu pour la déposer face cachée devant eux sur la table.  Quand tout le monde a posé, on retourne les cartes. Celui qui a déposé la carte la plus faible est le premier à jouer.  La carte est déposé sur la rangé sur laquel le nombre et le plus proche de sa carte. Lors d'une ligne récupéré par un joueur la dernier carte posé passe en premier ---------------------------------------- 



Point vue algorithmique:  Liste de joueur et cartes (10 max)  Liste de carte (valeur min 1 max 104), point (1 à 5) Liste board/plateau (4 cartes en colonne, 6 cartes max en ligne)  A chaque fin de tour on enleve la carte qui a été déposé par le joueur Un joueur possède des points de base ils sont à 0 si sur un tour la ligne est au nombre de 6 ou qu'il prend une ligne car sa carte est inférieur au nombre sur la ligne il prend les points qui sont sur les cartes Debut de game : Envoie 10 cartes à chaque joueur Chaque tour : début -> pose une carte pour une ligne, fin -> prend une ligne ou continue sur le prochain tour 10 tour max Deux projets C++ Client (Front en web) | Serveur ( Comme API en web) Serveur : Gestion  tour, gestion des points, gestion des cartes, distrubution des cartes aux joueurs Client : Le joueur aura le droit que de poser la carte et de choisir une ligne que quand sa carte est inférieur aux celle de la rangé Toute l'affichage pour le moment sera en console