#include "Server.h"
#include "../services/JoueurService.h"
#include "../services/CardService.h"

#include "../utils/Utils.h"

Server* Server::create_server(int port) {
    Output::GetInstance()->print("[SERVER] ", "Trying to open connection socket on the port ", port, "...\n");

    Socket connection_socket;

    // Ouverture de la socket de connexion
    connection_socket = open_connection(port);
    if (!connection_socket) {
        Output::GetInstance()->print("[SERVER] ", "Connection socket failed !\n");
        return nullptr;
    }
    return new Server(connection_socket);
}

Server::Server(Socket socket) : ThreadedSocket(socket, true, MAXDATASIZE), is_running(false) {
    game = new Game();
    std::string prefix = "[SERVER] ";
    output_prefix = (char*)malloc(strlen(prefix.c_str()) + 1);
    if (!output_prefix) return;
    strcpy(output_prefix, prefix.c_str());
}

Server::~Server() {
    ThreadedSocket::~ThreadedSocket();
    free(output_prefix);
}

void Server::start() {
    start_thread();
}

void Server::execute_thread() {
    is_running = true;
    while (is_running && is_alive)
    {
        Output::GetInstance()->print_debug(output_prefix, "Waiting for client connection...\n");
        Socket client_socket;

        // Attente de la connexion client
        client_socket = accept_connection(socket_);
        if (client_socket == NULL)
            continue;

        // Démarrage du thread dédié au client
<<<<<<< HEAD
        auto player = std::unique_ptr<Joueur>(new Joueur());
        auto client = std::unique_ptr<Client>(new Client(clients.size(), client_socket, *this, *player));

        auto player_cards = CardService::get_instance().draw_cards(10);
        Output::GetInstance()->print_debug(output_prefix, "Player ",clients.size(), " cards:\n");
        CardService::get_instance().dispay_cards(player_cards);
        player->set_cards(player_cards);

        JoueurService::get_instance().add_joueur(std::move(player));

=======
        auto client = new Client(clients.size(), client_socket, *this, game);
>>>>>>> 4f943eb901d92a4b0ce4901128631ab040b5d263
        client->start_thread();

        clients.push_back(std::move(client));

        Output::GetInstance()->print_debug(output_prefix, "Number of clients ", clients.size(), "\n");
        Output::GetInstance()->print_debug(output_prefix, "Cards in the stack left:\n");
        CardService::get_instance().dispay_cards(CardService::get_instance().get_game_cards());
    }
    Output::GetInstance()->print_debug(output_prefix, "Server is not taking anymore client\n");
    while (is_running && is_alive && JoueurService::get_instance().get_nbr_players() >= 4) {
        sleep(1);
        continue;
    }
    is_running = false;
}

void Server::stop() {
    is_running = false;
}

void Server::client_disconnected(Client& client) {
    Output::GetInstance()->print(output_prefix, "Client ", client.get_id(), " is disconntecting\n");
    JoueurService::get_instance().remove_joueur(client.get_joueur());
    clients.remove_if([&](const std::unique_ptr<Client>& c) { return &client == c.get(); });
}

bool Server::get_is_running() {
    return is_running;
}


Socket Server::open_connection(int connection_port)
{
    Socket connection_socket;
    Address address;
    int yes = 1;

#ifdef _WIN32
    // Initialisation l'utilisation des WinSocks par un processus
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 0), &WSAData) == -1) {
        perror("Error while starting using WinSocks : ");
        return 0;
    }
#endif

    // Ouverture de la socket de connexion
    if ((connection_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error while creating connection socket : ");
        return 0;
    }

#ifndef _WIN32
    // Configuration de la socket de connexion
    if (setsockopt(connection_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("Error while configuring connection socket : ");
        exit(EXIT_FAILURE);
    }
#endif

    // Configuration de l'adresse de transport
    address.sin_addr.s_addr = INADDR_ANY;      // adresse, devrait être converti en reseau mais est egal à 0
    address.sin_family = AF_INET;              // type de la socket
    address.sin_port = htons(connection_port); // port, converti en reseau
#ifndef _WIN32
    bzero(&(address.sin_zero), 8);             // mise a zero du reste de la structure
#endif

    // Demarrage du point de connexion : on ajoute l'adresse de transport dans la socket
    if (bind(connection_socket, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("Error while binding connection socket : ");
        return 0;
    }

    // Attente sur le point de connexion
    if (listen(connection_socket, BACKLOG) == -1) {
        perror("Error while listening connection socket : ");
        return 0;
    }

    return connection_socket;
}

Socket Server::accept_connection(Socket connection_socket)
{
    Socket client_socket;
    Address caddress;
#ifdef _WIN32
    int sinsize = sizeof(caddress);
#else
    unsigned int sinsize = sizeof(struct sockaddr_in);
#endif

    // Acceptation de la connexion
    if ((client_socket = accept(connection_socket, (struct sockaddr*)&caddress, &sinsize)) == -1) {
        perror("Error while accepting client connection : ");
        return NULL;
    }

    // Affichage de la connexion
    Output::GetInstance()->print(output_prefix, "[+] New connection from ", inet_ntoa(caddress.sin_addr), "\n");

    return client_socket;
}