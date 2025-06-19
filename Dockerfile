FROM archlinux:latest

RUN pacman -Syu --noconfirm base-devel cmake nano

WORKDIR /simulador

CMD ["bash"]
