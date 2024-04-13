FROM python:3.8

RUN wget -qO - https://www.mongodb.org/static/pgp/server-6.0.asc |  gpg --dearmor | tee /usr/share/keyrings/mongodb.gpg > /dev/null
RUN echo "deb [ arch=amd64,arm64 signed-by=/usr/share/keyrings/mongodb.gpg ] https://repo.mongodb.org/apt/ubuntu jammy/mongodb-org/6.0 multiverse" | tee /etc/apt/sources.list.d/mongodb-org-6.0.list

RUN apt-get update && \
    apt-get install -y mongodb-org supervisor && \
    apt-get clean

RUN mkdir -p /data/db

RUN chown -R mongodb:mongodb /data/db

ENV MONGO_URI mongodb://127.0.0.1:27017/loginform

WORKDIR /app

COPY challenge /app

RUN pip install -r requirements.txt


COPY conf/supervisord.conf /etc/supervisord.conf

EXPOSE 1337

ENTRYPOINT ["/usr/bin/supervisord", "-c", "/etc/supervisord.conf"]