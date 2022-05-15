FROM ubuntu:latest
#FROM alpine:latest

#RUN pacman -Syyuu --noconfirm \
#    base \
#    base-devel \
#    python \
#    mariadb-clients \
#    mariadb-libs \
#    neofetch \
#    docker

#RUN apk add --no-cache \
#    mysql-client \
#    python3 \
#    boost-dev \
#    bash gcompat \
#    gcc \
#    musl-dev \
#    mariadb-connector-c-dev \
#    neofetch

RUN apt update && apt install -y \
    mariadb-client \
    mariadb-server \
    python3 \
    docker \
    neofetch \
    systemd \
    docker.io \
    telnet


COPY . /home

CMD neofetch && \
    cd /home/ && \
    ./RattlesnakeServer

