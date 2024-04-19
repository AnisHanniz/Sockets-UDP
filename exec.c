#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 6336
#define INTERVALLE_ENVOI 2 // Intervalle d'envoi
#define INTERVALLE_AFFICHAGE 10 // Intervalle d'affichage IP

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <message>\n", argv[0]);
        return 1;
    }

    const char* message = argv[1];
    int sockfd;
    struct sockaddr_in adresseServeur, adresseClient;
    socklen_t adresseClientLen = sizeof(adresseClient);
    char buffer[1024];
    char adressesIP[1024][INET_ADDRSTRLEN];
    int compteurIPs = 0;
    time_t dernierAffichage = 0;

    // Init socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Erreur de création du socket");
        return 1;
    }

    // Config adresse en mode : BROADCAST
    memset(&adresseServeur, 0, sizeof(adresseServeur));
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    adresseServeur.sin_port = htons(PORT);

    int broadcastPermission = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastPermission, sizeof(broadcastPermission)) < 0) {
        perror("Erreur lors de la configuration du socket pour le broadcast");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr *)&adresseServeur, sizeof(adresseServeur)) < 0) {
        perror("Erreur de liaison");
        return 1;
    }

    while (1) {
        // Envoi message
        if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&adresseServeur, sizeof(adresseServeur)) < 0) {
            perror("Erreur lors de l'envoi");
            return 1;
        }
        else{
                printf("Message envoyé : %s\n", message);
            }
        // Si le message est égal à celui que j'envoie (ou en fait partie) je ne l'affiche pas 
        // Réception messages
        if (recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&adresseClient, &adresseClientLen) >= 0) {
            buffer[sizeof(buffer) - 1] = '\0';
            if (strcmp(buffer, message) < 0) {
                printf("Message reçu : %s\n", buffer);
                // Ajout de l'adresse IP dans la liste
                inet_ntop(AF_INET, &adresseClient.sin_addr, adressesIP[compteurIPs], INET_ADDRSTRLEN);
                compteurIPs++;
            } else {
                // Renvoi si ce n'est pas le message attendu
                sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&adresseClient, adresseClientLen);
            }
        }

        // Affichage des adresses IP
        if (time(NULL) - dernierAffichage >= INTERVALLE_AFFICHAGE) {
            printf("Adresses IP ayant répondu :\n");
            for (int i = 0; i < compteurIPs; i++) {
                printf("%s\n", adressesIP[i]);
            }
            dernierAffichage = time(NULL);
            compteurIPs = 0;
        }

        sleep(INTERVALLE_ENVOI); // Pause
    }

    close(sockfd);
    return 0;
}