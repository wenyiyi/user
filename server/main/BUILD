cc_binary(
    name = "user_server",
    srcs = ["user.server.hpp",
            "user_server.cpp",
            "user.grpc.pb.cc",
            "user.pb.cc",
            "user.grpc.pb.h",
            "user.pb.h"],
    deps = ["@com_github_grpc_grpc//:grpc++", 
			"@com_github_grpc_grpc//:grpc_plugin_support",
            "@mysql_connector//:mysql_connector"]
)

