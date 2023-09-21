# Automatic protobuf and gRPC c++ code generation with CMake
Does what the title says, highly portable solution that in compile time generates the c++ code associated with a proto file and properly links with the project. 

It's done by fetching the gRPC library via CMake FetchContent and creating a cmake custom command that uses the generated protoc and grpc_cpp_plugin executables.

You can run this example on your machine by:
```shell
mdkir build
cd build
cmake ..
make -j8
./proto_grpc
```
