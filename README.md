This client app were developed in modern C++ 11 language and contains the following vulnerabilities protections:
1. Protection against buffer overflow. recieved user input into std::string type which has native bounds protection.
2. Communication with the server via encrypted SSL connection using TLSv1.3

Compilation Instructions:
1. in the secure-client project directory call make.

Usage Instructions:
1. After the compilation process end you will see a new directory created named bin.
2. cd bin
3. Run the binary inside using the following command: ./Client

