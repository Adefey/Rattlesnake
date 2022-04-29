FROM alpine:latest

RUN apk add --no-cache mysql-client python3 boost-dev

COPY . /home

CMD ls -la /home &&\
    /home/RattlesnakeServer
