#define ASIO_STANDALONE
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>
#include <set>
#include <nlohmann/json.hpp>
#include <mutex>

typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::connection_hdl;
using json = nlohmann::json;

std::set<connection_hdl, std::owner_less<connection_hdl>> clients;
std::mutex mtx;

void on_open(server* s, connection_hdl hdl) {
    std::lock_guard<std::mutex> lock(mtx);
    clients.insert(hdl);
    std::cout << "Client connected\n";
}

void on_close(server* s, connection_hdl hdl) {
    std::lock_guard<std::mutex> lock(mtx);
    clients.erase(hdl);
    std::cout << "Client disconnected\n";
}

void on_message(server* s, connection_hdl hdl, server::message_ptr msg) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& c : clients) {
        if (c.lock().owner_before(hdl) || hdl.owner_before(c)) {
            try {
                s->send(c, msg->get_payload(), msg->get_opcode());
            } catch (...) {
                // Ignore broken connections
            }
        }
    }
}

int main() {
    server s;

    try {
        s.set_reuse_addr(true);
        s.init_asio();
        s.set_open_handler(std::bind(&on_open, &s, std::placeholders::_1));
        s.set_close_handler(std::bind(&on_close, &s, std::placeholders::_1));
        s.set_message_handler(std::bind(&on_message, &s, std::placeholders::_1, std::placeholders::_2));
        s.listen(9002);
        s.start_accept();

        std::cout << "Server started on port 9002\n";
        s.run();

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return 0;
}
