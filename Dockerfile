FROM gcc:latest
RUN apt -y update
RUN apt -y install cmake libpq-dev libpqxx-dev
COPY ./library /usr/src/app
WORKDIR /usr/src/app
RUN cmake .
RUN make
RUN export .env
CMD ["./library"]
