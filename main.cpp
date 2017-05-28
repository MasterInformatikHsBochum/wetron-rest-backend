#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

class ApiEndpoint {
public:
    ApiEndpoint(Net::Address addr)
        : httpEndpoint(std::make_shared<Net::Http::Endpoint>(addr))
    { }

    void init(size_t thr = 1) {
        auto opts = Net::Http::Endpoint::options()
            .threads(thr)
            .flags(Net::Tcp::Options::InstallSignalHandler);
        httpEndpoint->init(opts);
        setupRoutes();
    }

    void start() {
        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serve();
    }

    void shutdown() {
        httpEndpoint->shutdown();
    }

private:
    void setupRoutes() {
        using namespace Net::Rest;

        // get list of available sessions
        Routes::Get(router, "/sessions", Routes::bind(&ApiEndpoint::getSessions, this));

        // create a new session
        Routes::Post(router, "/session", Routes::bind(&ApiEndpoint::createSession, this));
    }

    void getSessions(const Net::Rest::Request& request, Net::Http::ResponseWriter response) {
        response.send(Net::Http::Code::Ok, "{\"sessions\":[]}");
    }

    void createSession(const Net::Rest::Request& request, Net::Http::ResponseWriter response) {
        response.send(Net::Http::Code::Ok, "{\"session\":{\"uid\":\"68b329da9893e34099c7d8ad5cb9c940\",\"host\":\"127.0.0.1\",\"port\":1884,\"channel\":\"WeTron/sesion/68b329da9893e34099c7d8ad5cb9c940\"}}");
    }

    std::shared_ptr<Net::Http::Endpoint> httpEndpoint;
    Net::Rest::Router router;
};

int main(int argc, char *argv[]) {
    Net::Port port(8080);

    Net::Address addr(Net::Ipv4::any(), port);

    // Define number of threads = number of cores
    int threads = hardware_concurrency();

    ApiEndpoint api(addr);

    api.init(threads);
    api.start();

    api.shutdown();
}