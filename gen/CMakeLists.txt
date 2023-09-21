project(protoGenerated)

file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)
set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(GENERATED_FILES)

foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_FILENAME ${PROTO_FILE} NAME_WE)

    add_custom_command(
        OUTPUT ${GENERATED_DIR}/${PROTO_FILENAME}.pb.cc ${GENERATED_DIR}/${PROTO_FILENAME}.pb.h ${GENERATED_DIR}/${PROTO_FILENAME}.grpc.pb.cc ${GENERATED_DIR}/${PROTO_FILENAME}.grpc.pb.h
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS -I${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${GENERATED_DIR} --grpc_out=${GENERATED_DIR} --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN_EXECUTABLE} ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Generating protobuf and gRPC C++ code"
        VERBATIM
    )

    list(APPEND GENERATED_FILES
        ${GENERATED_DIR}/${PROTO_FILENAME}.pb.cc
        ${GENERATED_DIR}/${PROTO_FILENAME}.grpc.pb.cc
    )
endforeach()

add_library(${PROJECT_NAME} STATIC ${GENERATED_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${GENERATED_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROTOBUF_LIBRARIES} grpc++)
