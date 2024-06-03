FROM debian:latest as build
RUN	apt update && apt -y install build-essential && apt -y install valgrind vim libreadline-dev
WORKDIR /app
COPY . .
CMD ["sleep", "10000000000000000000000"]
