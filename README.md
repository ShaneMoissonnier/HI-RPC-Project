<div align="center">
	<br>
	<br>
	<img src="assets/images/process.png" width="200" height="200">
	<h1>HIRPC</h1>
	<p>
	<p>🗃️ A simple rpc stub generator made in c</p>
	</p>
	<br>
</div>

## Description

The goal of this project was to create a simple rpc generator inspired by the protobuf interface specification and allows user to make their own specificiation file to generate client/server stubs easily.

## Explanation

Here is a basic example of our interface description language:

```

message Request {
    int operation
    int operandA
    int operandB
}

message Response {
    int result
}

service Service {
    param Request
    reply Response
}
```

> `message` represents data structure to be send to the server
> `service` represents data structure to be send as a response to the client

## Instructions

1. Compile the source code with the following command:

    ```console
         make clean
         make all
    ```

    > At this point, client/server stubs are generated and client/server instances are compiled and could be launched. By default "make all" command use "specification.proto" file in directory.

2. Launch the server first with the following command:

    ```console
        ./server
    ```

3. Launch a client with this command:
    ```console
        ./client
    ```

> In case you would like to use your own specification file at step 1, use the following commands to generate client/server stubs:

```console
    make clean
    make
    ./generator <yourfile.proto>
    make instance
```

## Potential future improvements

-   Support more variable type in specification file.
-   Create a more complete IDL.
-   Add more unit tests.
