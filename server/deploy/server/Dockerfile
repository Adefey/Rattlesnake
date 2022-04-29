FROM archlinux:latest

RUN y | pacman -Syyuu --noconfirm base base-devel python mariadb-clients mariadb-libs

COPY . /home

CMD [ "/bin/bash", "-l", "-c", "/home/RattlesnakeServer" ]

