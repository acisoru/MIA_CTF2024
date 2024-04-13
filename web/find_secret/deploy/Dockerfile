FROM python:3.9

RUN apt update && \
    apt install -y supervisor && \
    apt clean

WORKDIR /app

COPY challenge /app

RUN pip install -r requirements.txt

COPY conf/supervisord.conf /etc/supervisord.conf

EXPOSE 3132

ENTRYPOINT ["/usr/bin/supervisord", "-c", "/etc/supervisord.conf"]
