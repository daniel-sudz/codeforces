FROM ubuntu:latest
RUN apt-get update -y
RUN apt-get install -y vim git time nodejs build-essential
RUN gcc --version
RUN node --version
ENTRYPOINT /codeforces/entrypoint
