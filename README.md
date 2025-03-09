Système de Gestion de Produits en C++

Ce projet est une application de gestion de produits en C++, permettant d'ajouter, consulter et acheter des produits alimentaires et électroniques. Il repose sur un modèle orienté objet et une structure modulaire.
Fonctionnalités
Gestion des produits alimentaires

    Produits préemballés avec prix unitaire
    Produits frais vendus au poids

Gestion des produits électroniques

    Produits grand public avec gestion d'écran
    Produits industriels avec niveaux de protection
    Produits automobiles avec gestion de tension
    Produits médicaux certifiés

Autres fonctionnalités

    Gestion des stocks et des achats
    Recherche de produits par code-barres
    Affichage du catalogue des produits électroniques

Architecture du projet

Le projet repose sur la programmation orientée objet :

    Une classe Product sert de base commune
    Héritage multiple pour les produits électroniques
    Gestion polymorphique avec std::vector
