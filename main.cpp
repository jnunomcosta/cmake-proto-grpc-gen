#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <file.grpc.pb.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class DummyServiceImpl : public DummyService::Service {
public:
    grpc::Status func(grpc::ServerContext* context, const Message1* request, Message2* response) override {
        std::cout << "Great success" << std::endl;
        return Status::OK;
    }
};

int main() {
    std::string server_address("0.0.0.0:50051");
    DummyServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "GRPC server listening on " << server_address << std::endl;

    server->Wait();

    return 0;
}
