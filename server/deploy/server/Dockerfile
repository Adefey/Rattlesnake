FROM archlinux:latest
#FROM alpine:latest
RUN pacman -Syyuu --noconfirm base base-devel python mariadb-clients mariadb-libs neofetch
#RUN apk add --no-cache mysql-client python3 boost-dev bash gcompat gcc musl-dev mariadb-connector-c-dev neofetch

COPY . /home

CMD neofetch && \
    /home/RattlesnakeServer

