FROM archlinux:base

RUN pacman -Suy --noconfirm
RUN pacman -S socat --noconfirm

RUN useradd -m ctf
RUN mkdir /app
WORKDIR /app

COPY task /app
COPY flag /app

USER ctf

EXPOSE 37373
CMD socat tcp-listen:37373,reuseaddr,fork exec:"./task"
