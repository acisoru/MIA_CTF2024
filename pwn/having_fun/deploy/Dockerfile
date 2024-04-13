FROM archlinux:base

RUN pacman -Suy --noconfirm
RUN pacman -S socat --noconfirm

RUN useradd -m ctf
RUN mkdir /app
WORKDIR /app

COPY task /app
COPY flag /app

USER ctf

EXPOSE 17171
CMD socat tcp-listen:17171,reuseaddr,fork exec:"./task"
