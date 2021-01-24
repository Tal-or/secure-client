This client app were developed on Ubuntu 20.04.1 LTS in modern C++ 11 language and contains the following vulnerabilities protections:
1. Protection against buffer overflow. recieved user input into std::string type which has native bounds protection.
2. Communication with the server via encrypted SSL connection using TLSv1.3

Compilation Instructions:
1. This client using curl library for encryption via SSL protocol. install the library on your system:
   a. sudo apt install -y libcurlpp-dev
   b. sudo apt-get install -y libcurl4-openssl-dev
   c. sudo apt install -y libssl-dev 

2. Check that you got it installed properly:
   ldconfig -p | grep libcurl
3. Init the curlpp module: git submodule update --init

4. In the secure-client project directory call make.

Usage Instructions:
1. After the compilation process end you will see a new directory created named bin.
2. cd bin
3. Run the binary inside using the following command: ./Client

