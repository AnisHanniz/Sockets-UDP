# Projet de Programmation de Sockets

Ce projet consiste en un programme en langage C permettant la communication via des sockets en mode UDP. Le programme permet d'envoyer un message spécifié en ligne de commande à une adresse de diffusion spécifique, puis d'attendre les réponses des clients écoutant sur cette adresse. Il affiche également les adresses IP des clients ayant répondu.

## Prérequis

- Système d'exploitation compatible avec les appels système de socket (testé sur Linux).
- Compilateur C (tel que gcc).

## Installation

1. Clonez ce dépôt sur votre machine locale :

   ```
   git clone https://github.com/AnisHanniz/Sockets-UDP.git
   ```

2. Accédez au répertoire du projet :

   ```
   cd ProjetSockets
   ```

3. Compilez le programme en utilisant le makefile fourni :

   ```
   make
   ```

## Utilisation

- Exécutez le programme en spécifiant le message à envoyer comme argument en ligne de commande :

   ```
   ./exec "votre_message"
   ```

   Assurez-vous d'avoir les privilèges nécessaires pour utiliser les sockets en mode de diffusion.

## Fonctionnalités

- Envoi d'un message spécifié à une adresse de diffusion.
- Réception des réponses des clients et affichage des messages reçus.
- Affichage des adresses IP des clients ayant répondu à intervalles réguliers.

## Auteurs

Ce programme a été réalisé par [AnisHanniz](https://github.com/AnisHanniz).
